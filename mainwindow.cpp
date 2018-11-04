#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "iostream"
#include <stdio.h>
#include <QTextStream>
#include <QFileInfo>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialise_enviroment();
    initialise_database();

    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(ok_funkcija()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_reset, SIGNAL(clicked()), this, SLOT(reset_usluge()));
    connect(ui->btn_reset1, SIGNAL(clicked()), this, SLOT(reset_odeljenja()));
    connect(ui->btn_izvestaj, SIGNAL(clicked()), this, SLOT(izvestaj_funkcija()));

}

void MainWindow::initialise_database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/aleksandra/Usluzni_program_zdr_usluga/database");

    qDebug() << "start";

    if(!db.open())
    {
        qDebug() << "problem opening database";
    }
    qDebug() << "end";
}

void MainWindow::initialise_enviroment()
{
    QString line;
    QFile usluge("zdravstvene_usluge.txt");
    QFile odeljenja("zdravstvena_odeljenja.txt");

    ui->jmbg->setFocus();

    ui->cb_zaposlen->addItem("Doktor");
    ui->cb_zaposlen->addItem("Medicniska sestra/tehnicar");

    if(usluge.open(QIODevice::ReadOnly))
    {
        QTextStream us(&usluge);
        line = us.readLine();
        while(!line.isNull())
        {
            ui->zdr_usluge->addItem(line);
            line = us.readLine();
        }
        usluge.close();
    }

    if(odeljenja.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&odeljenja);
        line = in.readLine();
        while(!line.isNull())
        {

            ui->cb_zdr_odeljenje->addItem(line);
            line = in.readLine();
        }
        odeljenja.close();
    }
}


void MainWindow::promena()
{
    m_ui = new Dialog(this);
    m_ui->show();
    connect(m_ui, SIGNAL(sendChange(QList<QString>, QList<QString>)),
            this, SLOT(receiveFromDialog(QList<QString>, QList<QString>)));
    ui->jmbg->setFocus();
}

void MainWindow::receiveFromDialog(QList<QString> usluge, QList<QString> odeljenja)
{
    ui->cb_zdr_odeljenje->addItems(odeljenja);
    ui->zdr_usluge->addItems(usluge);
}

void MainWindow::dodajZdrUslugu(QSqlQuery &q, const QString &usluga)
{
    q.addBindValue(usluga);
    q.exec();
}

void MainWindow::dodajZdrRadnika(QSqlQuery &q, const QString &radnik, int jmbg, int id_usl, int broj)
{
    q.addBindValue(radnik);
    q.addBindValue(jmbg);
    q.addBindValue(id_usl);
    q.addBindValue(broj);
    q.exec();
}

void MainWindow::ok_funkcija()
{
    QString zdr_usl = ui->zdr_usluge->currentText();
    QString jmbg_str = ui->jmbg->text();
    QString zdr_rad = ui->lE_zdr_rad->text();
    QString vrsta = ui->cb_zaposlen->currentText();
    QString vreme = ui->ed_vreme_brisanja->text();

    if(zdr_usl != " ") {
        ui->lbl_zdr->setText(zdr_usl);
        QSqlQuery query(db);
        if(!query.prepare(QLatin1String("insert into ZdravstvenaUsluga(naziv_usluge) values(?)")))
        {
            qDebug() << "zdr_usl PROBLEM!!!";
            return;
        }
        dodajZdrUslugu(query, zdr_usl);
    }

    if (jmbg_str != " ") {
        QSqlQuery query(db);
//        ui->lbl_zdr->setText(jmbg_str);
        if(!query.prepare(QLatin1String("SELECT jmbg from ZdravstveniRadnik where jmbg like ?")))
            return;
        query.addBindValue(jmbg_str.toInt());
        query.first();
        if (query.value(1).toString() != "")
        {
            ui->lbl_zdr->setText("aaaaaaaaaaa");
            query.prepare("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?");
            query.addBindValue(zdr_usl);
            query.exec();
            int id_usl = query.value("id_usluge").toInt();
            if(!query.prepare(QLatin1String("insert into ZdravstveniRadnik(imePrezime, jmbg, id_usluge, broj_usluge)"
                                          "values(?,?,?,?)")))
            {
                qDebug() << "JMBG PROBLEM!!!";
                return;
            }
            dodajZdrRadnika(query, zdr_rad, jmbg_str.toInt(), id_usl, 1);
        }
//            ui->lbl_zdr->setText(query.value("jmbg").toString());
//            qDebug() << query.value("jmbg").toString();

    }

    ui->jmbg->setText("");
    ui->lE_zdr_rad->setText("");
    ui->jmbg->setFocus();
}

void MainWindow::reset_usluge()
{
    ui->zdr_usluge->clear();
    QFile file("zdravstvene_usluge.txt");
    file.resize(0);
    ui->jmbg->setFocus();
}

void MainWindow::reset_odeljenja()
{
    ui->cb_zdr_odeljenje->clear();
    QFile file("zdravstvena_odeljenja.txt");
    file.resize(0);
    ui->jmbg->setFocus();
}

void MainWindow::izvestaj_funkcija()
{
    ui->jmbg->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}

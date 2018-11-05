#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "iostream"
#include <stdio.h>
#include <QTextStream>
#include <QSqlQuery>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialise_database();
    initialise_enviroment();

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
//    db.setDatabaseName("/home/aleksandra/Usluzni_program_zdr_usluga/database");
    db.setDatabaseName("/home/aleksandra/proba1/database");


    if(!db.open())
    {
        qDebug() << "problem opening database";
    }
}

void MainWindow::initialise_enviroment()
{
    QSqlQuery query(db);

    query.exec("select naziv_usluge from ZdravstvenaUsluga");
    query.first();
    if(query.value(0).toString() != "") {
        ui->zdr_usluge->addItem(query.value(0).toString());
        while (query.next())
        {
            ui->zdr_usluge->addItem(query.value(0).toString());
            qDebug() << query.value(0).toString();
        }
    }

    ui->jmbg->setFocus();

    ui->cb_zaposlen->addItem("Doktor");
    ui->cb_zaposlen->addItem("Medicniska sestra/tehnicar");

    query.exec("select naziv from ZdravstvenaOdeljenja");
    query.first();

    while (query.next())
    {
        ui->cb_zdr_odeljenje->addItem(query.value(0).toString());
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

void MainWindow::pripremiZdrUslugu(QSqlQuery &q, const QString &usluga)
{
    q.addBindValue(usluga);
    q.exec();
}

void MainWindow::dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int broj, QString vreme)
{
    q.addBindValue(radnik);
    q.addBindValue(zanimanje);
    q.addBindValue(jmbg);
    q.addBindValue(id_usl);
    q.addBindValue(broj);
    q.addBindValue(vreme);
    q.exec();
}

void MainWindow::zdrUslugaFunkcija(QString zdrU, QSqlQuery &query)
{
    ui->lbl_zdr->setText(zdrU);

    if(!query.prepare("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?"))
    {
        qDebug() << "zdr_usl PROBLEM!!!";
        return;
    }
    pripremiZdrUslugu(query, zdrU);
    query.first();
    qDebug() << query.value(0).toInt();

    if(query.value(0).toInt() == 0)
    {
        if(!query.prepare(QLatin1String("insert into ZdravstvenaUsluga(naziv_usluge) values(?)")))
        {
            qDebug() << "zdr_usl PROBLEM!!!";
            return;
        }
        pripremiZdrUslugu(query, zdrU);
    }
}

void MainWindow::zdrRadFunkcija(QSqlQuery &query, QString zdr_rad, QString zanimanje, QString jmbg, QString zdr_usl, QString vreme)
{
    if(!query.prepare("SELECT jmbg from ZdravstveniRadnik where jmbg like ?"))
        return;
    query.addBindValue(jmbg);
    query.exec();
    query.first();

    if (query.value(0).toString() == "")
    {
        ui->lbl_zdr->setText("Pacijent sa maticnim brojem " + jmbg + " je unet u bazu");
        query.prepare(QLatin1String("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?"));
        query.addBindValue(zdr_usl);
        query.exec();
        query.first();
        int id_usl = query.value(0).toInt();
        if(!query.prepare(QLatin1String("insert into ZdravstveniRadnik(imePrezime, zanimanje, jmbg, id_usluge, broj_usluge, vreme_brisanja)"
                                      "values(?,?,?,?, ?, ?)")))
        {
            qDebug() << "JMBG PROBLEM!!!";
            return;
        }
        dodajZdrRadnika(query, zdr_rad, zanimanje, jmbg, id_usl, 1, vreme);
    }
    else {
        ui->lbl_zdr->setText("Pacijent sa maticnim brojem " + jmbg + " je vec u bazi");
    }
}

void MainWindow::zdrOdeljenjeFunkcija(QSqlQuery &query, QString odeljenje, QString zdr_rad, QString zdr_usl)
{
    if (!query.prepare("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?"))
        return;
    query.addBindValue(zdr_usl);
    query.exec();
    query.first();
    int idUsluge= query.value(0).toInt();

    if (!query.prepare("select id_radnika from ZdravstveniRadnik where imePrezime like ?"))
        return;
    query.addBindValue(zdr_rad);
    query.exec();
    query.first();
    int idRadnika = query.value(0).toInt();

    if (!query.prepare("select id_radnika from ZdravstvenaOdeljenja where id_radnika like ?"))
        return;
    query.addBindValue(idRadnika);
    query.exec();
    query.first();

    qDebug() << query.value(0).toInt();

    if(query.value(0).toInt() == 0) {
        if (!query.prepare("insert into ZdravstvenaOdeljenja(naziv, id_radnika, id_usluge) values(?, ?, ?)"))
            return;
        query.addBindValue(odeljenje);
        query.addBindValue(idRadnika);
        query.addBindValue(idUsluge);
        query.exec();
    }

}



void MainWindow::ok_funkcija()
{
    QString zdr_usl = ui->zdr_usluge->currentText();
    QString jmbg_str = ui->jmbg->text();
    QString zdr_rad = ui->lE_zdr_rad->text();
    QString vrsta = ui->cb_zaposlen->currentText();
    QString odeljenje = ui->cb_zdr_odeljenje->currentText();
    QString vreme = ui->ed_vreme_brisanja->text();
    QSqlQuery query(db);

    if (zdr_rad == "") {
        qDebug() << "Unesi ime i prezime radnika";
        QMessageBox msgBox;
        msgBox.setText("unesite ime zdravstvenog radnika");
        msgBox.setWindowTitle("Zdravstveni radnik");
        msgBox.exec();
    }
    else {
        if (zdr_usl != "") {
            zdrUslugaFunkcija(zdr_usl, query);
        }

        if (jmbg_str != "") {
            zdrRadFunkcija(query, zdr_rad, vrsta, jmbg_str, zdr_usl, vreme);
        }

        if (odeljenje != "") {
            zdrOdeljenjeFunkcija(query, odeljenje, zdr_rad, zdr_usl);
        }
    }

    ui->jmbg->setText("");
    ui->lE_zdr_rad->setText("");
    ui->ed_vreme_brisanja->setText("");
    ui->jmbg->setFocus();
}

void MainWindow::reset_usluge()
{
    ui->zdr_usluge->clear();
//    QFile file("zdravstvene_usluge.txt");
//    file.resize(0);
    QSqlQuery query(db);
    query.prepare("delete from ZdravstvenaUsluge");
    query.exec();
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

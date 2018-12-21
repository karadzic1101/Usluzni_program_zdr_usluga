#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "calendarform.h"
#include "database.h"
#include "iostream"


#include <stdio.h>
#include <QTextStream>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>


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
    connect(ui->btn_brisanje, SIGNAL(clicked()), this, SLOT(vreme_brisanja()));

}

void MainWindow::initialise_database()
{
    QSqlQuery query(db);

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
    QString date = QString("25.12.18");

    QSqlQuery query(db);
    deletePatients(query, date);

    query.exec("select naziv_usluge from ZdravstvenaUsluga");
    query.first();
    if(query.value(0).toString() != "") {
        ui->zdr_usluge->addItem(query.value(0).toString());
        while (query.next())
        {
            ui->zdr_usluge->addItem(query.value(0).toString());
        }
    }

    ui->jmbg->setFocus();

    ui->cb_zaposlen->addItem("Doktor");
    ui->cb_zaposlen->addItem("Medicniska sestra/tehnicar");

    query.exec("select naziv from ZdravstvenaOdeljenja");
    query.first();
    if(query.value(0).toString() != "") {
        ui->cb_zdr_odeljenje->addItem(query.value(0).toString());
        while (query.next())
        {
            ui->cb_zdr_odeljenje->addItem(query.value(0).toString());
        }
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

void MainWindow::zdrUslugaFunkcija(QString zdrU, QSqlQuery &query)
{
    int idUsluge = nadjiIDusluge(query, zdrU);

    if(idUsluge == 0)
    {
        dodajZdrUslugu(query, zdrU, 1);
    }
    else
    {
       int brojIzvrsenihUsluga = brojZdrUsluga(query, idUsluge);
       updateZdrUslugu(query, idUsluge, brojIzvrsenihUsluga+1);
    }
}

void MainWindow::zdrRadFunkcija(QSqlQuery &query, QString zdr_rad, QString zanimanje, QString jmbg,
                                QString zdr_usl)
{
    QString new_jmbg = dodajJmbg(query, jmbg);
    qDebug() << new_jmbg;

    if (new_jmbg == "")
    {
        ui->lbl_zdr->setText("Pacijent sa maticnim brojem " + jmbg + " je unet u bazu");
        int id_usl = nadjiIDusluge(query, zdr_usl);
        qDebug() << id_usl;

        dodajZdrRadnika(query, zdr_rad, zanimanje, jmbg, id_usl, mesec_unosa, datum_brisanja);
    }
    else {
        ui->lbl_zdr->setText("Pacijent sa maticnim brojem " + jmbg + " je vec u bazi i vreme brisanja je promenjeno na " +
                             datum_brisanja);
        qDebug() << datum_brisanja;
        updateVremeBrisanje(query, jmbg, datum_brisanja);
    }
}

void MainWindow::zdrOdeljenjeFunkcija(QSqlQuery &query, QString odeljenje)
{
     QString new_odeljenje =  nadjiOdeljenje(query, odeljenje);

     if(new_odeljenje == "") {
       dodajZdravstvenoOdeljenje(query, odeljenje);
    }
}



void MainWindow::ok_funkcija()
{
    QString zdr_usl = ui->zdr_usluge->currentText();
    QString jmbg_str = ui->jmbg->text();
    QString zdr_rad = ui->lE_zdr_rad->text();
    QString vrsta = ui->cb_zaposlen->currentText();
    QString odeljenje = ui->cb_zdr_odeljenje->currentText();
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
            if (jmbg_str.length() != 13) {
                QMessageBox msgBox;
                msgBox.setText("Maticni broj je pogresna, nema 13 karaktera");
                msgBox.setWindowTitle("Maticni broj");
                msgBox.exec();
            }
            else
                zdrRadFunkcija(query, zdr_rad, vrsta, jmbg_str, zdr_usl);
        }
        if (odeljenje != "") {
            zdrOdeljenjeFunkcija(query, odeljenje);
        }
    }

    ui->jmbg->setText("");
    ui->lE_zdr_rad->setText("");
    ui->jmbg->setFocus();
}

void MainWindow::reset_usluge()
{
    QSqlQuery query(db);
    query.exec("delete from ZdravstvenaUsluga");
    query.exec("UPDATE sqlite_sequence set seq=0 where name='ZdravstvenaUsluga'");

    ui->zdr_usluge->clear();
    ui->jmbg->setFocus();
}

void MainWindow::reset_odeljenja()
{
    QSqlQuery query(db);
    query.exec("delete from ZdravstvenaOdeljenja");
    query.exec("UPDATE sqlite_sequence set seq=0 where name='ZdravstvenaOdeljenja'");

    ui->cb_zdr_odeljenje->clear();
    ui->jmbg->setFocus();
}

void MainWindow::izvestaj_funkcija()
{
    QString usluga = ui->zdr_usluge->currentText();
    QString radnik = ui->lE_zdr_rad->text();
    QSqlQuery query(db);
    int idUsluge = nadjiIDusluge(query, usluga);
    int ukupnoUsluga =  brojZdrUsluga(query, idUsluge);

    int mesec = QDate::currentDate().month();
    int uslugaPoRadniku = brUslugaPoRadniku(query, idUsluge, mesec);
    float procenat = ((float)uslugaPoRadniku/ukupnoUsluga)*100;
    qDebug() << ukupnoUsluga;
    qDebug() << uslugaPoRadniku;
    qDebug() << procenat;

    ui->lbl_zdr->setText("Radnik "+radnik+" je pregledao " + QString::number(uslugaPoRadniku) + " sto je "
                         + QString::number(procenat, 'f', 3) +"%");


    ui->jmbg->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}

void MainWindow::vreme_brisanja()
{
    c_ui = new CalendarForm(this);
    c_ui->show();
    connect(c_ui, SIGNAL(sendDate(QString)),
            this, SLOT(receveDate(QString)));
}

void MainWindow::receveDate(QString date)
{
    datum_brisanja = date;
    mesec_unosa = QDate::currentDate().month();
    qDebug() << "Main Window " << datum_brisanja << " mesec = " << mesec_unosa;
}

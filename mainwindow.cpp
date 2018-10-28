#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cb_zaposlen->addItem("Doktor");
    ui->cb_zaposlen->addItem("Medicniska sestra/tehnicar");

    QFile file("zdravstvene_usluge.txt");
    QStringList stringList;
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while(!file.atEnd())
        {
            stringList.append(file.readLine());
        }
    }

    file.close();

//    ui->zdr_usluge->addItem("Zdravstvena usluga 1");
//    ui->zdr_usluge->addItem("Zdravstvena usluga 2");
//    ui->zdr_usluge->addItem("Zdravstvena usluga 3");

    ui->zdr_usluge->addItems(stringList);

    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(ok_funkcija()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close_and_save()));
    connect(ui->btn_reset, SIGNAL(clicked()), this, SLOT(reset_funkcija()));
    connect(ui->btn_reset1, SIGNAL(clicked()), this, SLOT(reset_odeljenja()));
}


void MainWindow::promena()
{
    m_ui = new Dialog(this);
    m_ui->show();
    connect(m_ui, SIGNAL(sendChange(QList<QString>, QList<QString>)),
            this, SLOT(receiveFromDialog(QList<QString>, QList<QString>)));
}

void MainWindow::receiveFromDialog(QList<QString> usluge, QList<QString> odeljenja)
{
    ui->cb_zdr_odeljenje->addItems(odeljenja);
    ui->zdr_usluge->addItems(usluge);
}

void MainWindow::ok_funkcija()
{
    QString zdr_usl = ui->zdr_usluge->currentText();
    QString jmbg_str = ui->jmbg->text();
    QString zdr_rad = ui->lE_zdr_rad->text();
    QString vrsta = ui->cb_zaposlen->currentText();
    QString vreme = ui->ed_vreme_brisanja->text();
    int vreme_int = vreme.toInt();
    ui->lbl_zdr->setText(zdr_usl + " " + jmbg_str + " " + zdr_rad +
                         " " + vrsta + " " + vreme);
    ui->jmbg->setText("");
    ui->lE_zdr_rad->setText("");
}

void MainWindow::reset_funkcija()
{
    ui->zdr_usluge->clear();
}

void MainWindow::reset_odeljenja()
{
    ui->cb_zdr_odeljenje->clear();
}

void MainWindow::close_and_save()
{
    QString zdravstvene_usluge_file = "zdravstvene_usluge.txt";
    QFile file(zdravstvene_usluge_file);
    int broj_usluga = ui->zdr_usluge->count();
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for(int i=0; i<broj_usluga; i++) {
            cout << ui->zdr_usluge->itemText(i) << endl;
            if(ui->zdr_usluge->itemText(i) != " ")
                stream << ui->zdr_usluge->itemText(i) << endl;
        }
    }

    file.close();
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}

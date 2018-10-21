#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cb_zaposlen->addItem("Doktor");
    ui->cb_zaposlen->addItem("Medicniska sestra/tehnicar");

    ui->zdr_usluge->addItem("Zdravstvena usluga 1");
    ui->zdr_usluge->addItem("Zdravstvena usluga 2");
    ui->zdr_usluge->addItem("Zdravstvena usluga 3");

    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(ok_funkcija()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
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
    ui->lbl_zdr->setText(zdr_usl + " " + jmbg_str + " " + zdr_rad + " " + vrsta);
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

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}

#include "izvestajdialog.h"
#include "ui_izvestajdialog.h"
//#include "mainwindow.h"

#include <QDebug>

IzvestajDialog::IzvestajDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IzvestajDialog)
{
    ui->setupUi(this);
//    MainWindow m;

//    zdravstvena_usluga = m.zdravstvna_usluga_izvestaj;
//    qDebug() << zdravstvena_usluga;
}

IzvestajDialog::~IzvestajDialog()
{
    delete ui;
}

#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QFile>
#include "iostream"
#include <stdio.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(sendToMainWindow()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(closeAndSend()));

    m_ui->el_usluga->setFocus();

}

void Dialog::sendToMainWindow()
{
    QString usluga = m_ui->el_usluga->text();
    QString odeljenje = m_ui->el_odeljenje->text();

    if(usluga != "")
    {
        lista_usluga.append(usluga);
    }

    if(odeljenje != "")
    {
        lista_odeljenja.append(odeljenje);
    }

    m_ui->el_usluga->setText("");
    m_ui->el_odeljenje->setText("");
    m_ui->el_usluga->setFocus();
}

void Dialog::closeAndSend()
{
    emit sendChange(lista_usluga, lista_odeljenja);
    close();
}


Dialog::~Dialog()
{
    delete m_ui;
}

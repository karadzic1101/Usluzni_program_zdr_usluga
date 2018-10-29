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

}

void Dialog::sendToMainWindow()
{
    QString usluga = m_ui->el_usluga->text();
    QString odeljenje = m_ui->el_odeljenje->text();

    QString zdravstvene_usluge_file = "zdravstvene_usluge.txt";
    QFile file_usluge(zdravstvene_usluge_file);

    QString zdravstvene_odeljenja_file = "zdravstvena_odeljenja.txt";
    QFile file_odeljenja(zdravstvene_odeljenja_file);

    if(file_usluge.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream_usluge(&file_usluge);
        if(usluga != "")
        {
            lista_usluga.append(usluga);
            stream_usluge << usluga << endl;
            stream_usluge.flush();
        }
    }

    if(file_odeljenja.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream_odeljenja(&file_odeljenja);
        if(odeljenje != "")
        {
            lista_odeljenja.append(odeljenje);
            stream_odeljenja << odeljenje << endl;
            stream_odeljenja.flush();
        }
    }

    file_usluge.close();
    file_odeljenja.close();
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

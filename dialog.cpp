#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);

    connect(m_ui->btn_pr1, SIGNAL(clicked()), this, SLOT(sendToMainWindow1()));
    connect(m_ui->btn_pr2, SIGNAL(clicked()), this, SLOT(sendToMainWindow2()));
    connect(m_ui->btn_pr3, SIGNAL(clicked()), this, SLOT(sendToMainWindow3()));
    connect(m_ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));

}

void Dialog::sendToMainWindow1()
{
    QString tmp = m_ui->zdr_usl1->text();
    emit sendChange(tmp, 1);
    QTextStream(stdout) << tmp << endl;
}

void Dialog::sendToMainWindow2()
{
    QString tmp = m_ui->zdr_usl2->text();
    emit sendChange(tmp, 2);
    QTextStream(stdout) << tmp << endl;
}

void Dialog::sendToMainWindow3()
{
    QString tmp = m_ui->zdr_usl3->text();
    emit sendChange(tmp, 3);
    QTextStream(stdout) << tmp << endl;
}

Dialog::~Dialog()
{
    delete m_ui;
}

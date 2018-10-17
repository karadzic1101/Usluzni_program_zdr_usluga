#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);

    connect(m_ui->btn_ok, SIGNAL(clicked()), this, SLOT(sendToMainWindow()));
    connect(m_ui->btn_close, SIGNAL(clicked()), this, SLOT(closeAndSend()));

}

void Dialog::sendToMainWindow()
{
    QString tmp = m_ui->zdr_usl->text();
    list.append(tmp);
}

void Dialog::closeAndSend()
{
    emit sendChange(list);
    close();
}


Dialog::~Dialog()
{
    delete m_ui;
}

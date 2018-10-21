#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include <QTextStream>

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
    QString tmp_u = m_ui->zdr_usl->text();
    QString tmp_o = m_ui->le_odeljenje->text();
    if(tmp_o != "")
        odeljenje.append(tmp_o);
    if(tmp_u != "")
        list.append(tmp_u);
    m_ui->zdr_usl->setText("");
    m_ui->le_odeljenje->setText("");
}

void Dialog::closeAndSend()
{
    emit sendChange(list, odeljenje);
    close();
}


Dialog::~Dialog()
{
    delete m_ui;
}

#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);

//    QString promena = m_ui->ln_promena->text();
    connect(m_ui->btn_ok, SIGNAL(clicked()), this, SLOT(sendToMainWindow(QString)));
//    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
}

void Dialog::sendToMainWindow()
{
    promena = m_ui->ln_promena->text();
    emit sentToMainWindow(promena);
}

Dialog::~Dialog()
{
    delete m_ui;
}

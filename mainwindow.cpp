#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(ok_funkcija()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_reset, SIGNAL(clicked()), this, SLOT(reset_funkcija()));
}


void MainWindow::promena()
{
    m_ui = new Dialog(this);
    m_ui->show();
    connect(m_ui, SIGNAL(sendChange(QList<QString>)), this, SLOT(receiveFromDialog(QList<QString>)));
}

void MainWindow::receiveFromDialog(QList<QString> pr)
{
    ui->zdr_usluge->addItems(pr);
}

void MainWindow::ok_funkcija()
{
    QString zdr_usl = ui->zdr_usluge->currentText();
    QString jmbg_str = ui->jmbg->text();
    ui->lbl_zdr->setText(zdr_usl + " " + jmbg_str);
}

void MainWindow::reset_funkcija()
{
    ui->zdr_usluge->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}

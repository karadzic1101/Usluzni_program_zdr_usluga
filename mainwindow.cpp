#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->zdr_usl1, SIGNAL(clicked()), this, SLOT(zdr_usluga1()));
    connect(ui->zdr_usl2, SIGNAL(clicked()), this, SLOT(zdr_usluga2()));
    connect(ui->zdr_usl3, SIGNAL(clicked()), this, SLOT(zdr_usluga3()));
    connect(ui->btn_promena, SIGNAL(clicked()), this, SLOT(promena()));
    connect(m_ui->promena, SIGNAL(sentToMainWindow(QString)), ui, SLOT(receiveChange(QString)));
}

void MainWindow::zdr_usluga1()
{
    QString jmbg_string =ui->jmbg->text();
    ui->lbl_zdr1->setText(jmbg_string);
    ui->lbl_zdr2->setText("");
    ui->lbl_zdr3->setText("");
}

void MainWindow::zdr_usluga2()
{
    QString jmbg_string =ui->jmbg->text();
    ui->lbl_zdr2->setText(jmbg_string);
    ui->lbl_zdr1->setText("");
    ui->lbl_zdr3->setText("");

}

void MainWindow::zdr_usluga3()
{
    QString jmbg_string =ui->jmbg->text();
    ui->lbl_zdr3->setText(jmbg_string);
    ui->lbl_zdr1->setText("");
    ui->lbl_zdr2->setText("");
}

void MainWindow::promena()
{
    m_ui = new Dialog(this);
    m_ui->show();
}

void MainWindow::receiveChange(QString pr)
{
    ui->zdr_usl1->setText(pr);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ui;
}
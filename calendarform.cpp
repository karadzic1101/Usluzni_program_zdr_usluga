#include "calendarform.h"
#include "ui_calendarform.h"
#include <QDebug>

CalendarForm::CalendarForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarForm)
{
    ui->setupUi(this);

    ui->label->setText("Selektujte datum kada zelite da pacijent bude obrisan iz baze");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(funkcija_datum()));

    ui->calendar->setFocus();
}

void CalendarForm::preuzmiJmbg(QString jmbg)
{
    ui->label->setText("Za pacijenta sa maticnim brojem " + jmbg + " nije uneto vreme brisanja. Selektujte datum kada zelite da pacijent bude obrisan iz baze");
}

CalendarForm::~CalendarForm()
{
    delete ui;
}

void CalendarForm::on_buttonBox_rejected()
{
    close();
}


void CalendarForm::funkcija_datum()
{
    QString date = ui->calendar->selectedDate().toString("dd.MM.yy");
    qDebug() << date;
    emit sendDate(date);
}

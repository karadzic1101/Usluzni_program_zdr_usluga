#include "calendarform.h"
#include "ui_calendarform.h"
#include <QDebug>

CalendarForm::CalendarForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarForm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(funkcija_datum()));

    ui->calendar->setFocus();
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

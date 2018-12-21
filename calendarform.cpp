#include "calendarform.h"
#include "ui_calendarform.h"
#include <QDebug>

CalendarForm::CalendarForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarForm)
{
    ui->setupUi(this);
}

CalendarForm::~CalendarForm()
{
    delete ui;
}

void CalendarForm::on_buttonBox_rejected()
{
    close();
}


void CalendarForm::on_buttonBox_accepted()
{
    QString date = ui->calendar->selectedDate().toString("dd.MM.yy");
    qDebug() << date;
    emit sendDate(date);
    close();
}

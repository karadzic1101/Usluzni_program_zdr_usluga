#ifndef CALENDARFORM_H
#define CALENDARFORM_H

#include <QDialog>

namespace Ui {
class CalendarForm;
}

class CalendarForm : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarForm(QWidget *parent = 0);
    ~CalendarForm();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::CalendarForm *ui;
signals:
    void sendDate(QString date);
};

#endif // CALENDARFORM_H

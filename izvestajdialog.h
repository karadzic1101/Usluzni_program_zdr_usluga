#ifndef IZVESTAJDIALOG_H
#define IZVESTAJDIALOG_H

#include <QDialog>

namespace Ui {
class IzvestajDialog;
}

class IzvestajDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IzvestajDialog(QWidget *parent = 0);
    ~IzvestajDialog();

private:
    Ui::IzvestajDialog *ui;
    QString zdravstvena_usluga;
};

#endif // IZVESTAJDIALOG_H

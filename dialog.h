#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *m_ui;

private slots:
    void sendToMainWindow1();
    void sendToMainWindow2();
    void sendToMainWindow3();

signals:
    void sendChange(QString, int);
};

#endif // DIALOG_H

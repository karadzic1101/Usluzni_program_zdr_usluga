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
    QList<QString> lista_usluga;
    QList<QString> lista_odeljenja;

private slots:
    void sendToMainWindow();
    void closeAndSend();

signals:
    void sendChange(QList<QString>, QList<QString>);
    void odeljenjeIusluga(QString odeljenje, QString usluga);
};

#endif // DIALOG_H

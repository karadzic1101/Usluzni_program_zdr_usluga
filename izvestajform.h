#ifndef IZVESTAJFORM_H
#define IZVESTAJFORM_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class IzvestajForm;
}

class IzvestajForm : public QDialog
{
    Q_OBJECT

public:
    explicit IzvestajForm(QWidget *parent = 0);
    ~IzvestajForm();

    void zdravstveneUsluge(const QList<QString> &usluga);
    void posaljiQuery(const QSqlQuery &q);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::IzvestajForm *ui;

    void ispisiMesecniIzvestaj();
    void ispisiGodisnjiIzvestaj();
    void procitajMesecniIzvestaj();
    void imenaRadnika(QList<int> id_radnika);
    void procitajGodisnjiIzvestaj();

    QSqlQuery query;
    QList<QString> radnici;
    QList<int> id_radnika;
    QList<int> kolicina_usluga;
    QList<int> januar;
    QList<int> februar;
    QList<int> mart;
    QList<int> april;
    QList<int> maj;
    QList<int> jun;
    QList<int> jul;
    QList<int> avgust;
    QList<int> septembar;
    QList<int> oktobar;
    QList<int> novembar;
    QList<int> decembar;

    int ukupno_usluge;
    int broj_radnika;

};

#endif // IZVESTAJFORM_H

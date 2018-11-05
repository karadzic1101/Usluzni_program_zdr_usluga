#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

#include <QSql>
#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void initialise_enviroment();
    void initialise_database();
    void pripremiZdrUslugu(QSqlQuery &q, const QString &usluga);
    void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int broj, QString vreme);
    void zdrUslugaFunkcija(QString zdrU, QSqlQuery &q);
    void zdrRadFunkcija(QSqlQuery &query, QString zdr_rad, QString zanimanje, QString jmbg, QString zdr_usl, QString vreme);
    void zdrOdeljenjeFunkcija(QSqlQuery &query, QString odeljenje, QString zdr_rad, QString zdr_usl);
    QSqlDatabase db;
public:
    Ui::MainWindow *ui;
    Dialog *m_ui;
private slots:
   void promena();
   void ok_funkcija();
   void reset_usluge();
   void reset_odeljenja();
   void receiveFromDialog(QList<QString>, QList<QString>);
   void izvestaj_funkcija();
};

#endif // MAINWINDOW_H

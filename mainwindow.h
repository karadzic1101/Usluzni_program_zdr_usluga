#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "calendarform.h"
#include "izvestajform.h"

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

    void zdrUslugaFunkcija(QSqlQuery &q, QString usluga, QString odeljenje);
    void zdrOdeljenjeFunkcija(QSqlQuery &query, QString odeljenje);
    void pruzenaUsluga(QSqlQuery &query, QString jmbg, QString radnik, QString usluga);
    void mesecni_godisnji_izvestaj(QSqlQuery &query, QString radnik, QString usluga);

    QSqlDatabase db;

public:
    Ui::MainWindow *ui;
    Dialog *m_ui;
    CalendarForm *c_ui;
    IzvestajForm *if_ui;

    QString datum_brisanja;
    QList<QString> zdravstvene_usluge;
    int mesec_unosa;
    int trenutna_godina;

private slots:
   void promena();
   void ok_funkcija();
   void reset_usluge();
   void reset_odeljenja();
   void receiveFromDialog(QList<QString>, QList<QString>);
   void receveDate(QString date);
   void izvestaj_funkcija();
   void vreme_brisanja();

signals:
   void sendUsluga(QString);
};

#endif // MAINWINDOW_H

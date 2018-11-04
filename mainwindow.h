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
    void dodajZdrUslugu(QSqlQuery &q, const QString &usluga);
    void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, int jmbg, int id_usl, int broj);
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
    Dialog *m_ui;
private slots:
   void zdr_usluga1();
   void zdr_usluga2();
   void zdr_usluga3();
   void promena();
   void receiveChange(QString pr);
};

#endif // MAINWINDOW_H

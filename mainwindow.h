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
private:
    void initialise_enviroment();
public:
    Ui::MainWindow *ui;
    Dialog *m_ui;
private slots:
   void promena();
   void ok_funkcija();
   void reset_funkcija();
   void reset_odeljenja();
   void receiveFromDialog(QList<QString>, QList<QString>);
};

#endif // MAINWINDOW_H

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
   void promena();
   void ok_funkcija();
   void reset_funkcija();
   void receiveFromDialog(QList<QString>);
};

#endif // MAINWINDOW_H

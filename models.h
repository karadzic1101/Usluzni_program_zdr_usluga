#ifndef MODELS_H
#define MODELS_H

#include <QSqlTableModel>
#include <QSqlQueryModel>

class Database {
public:
    static bool init();
};

class ZdravstvenoOdeljene : public QSqlTableModel
{
public:
    static ZdravstvenoOdeljene * instance();
private:
    ZdravstvenoOdeljene();

    static ZdravstvenoOdeljene * s_instance;
};

class ZdravstveniRadnik : public QSqlQueryModel
{
public:
    static ZdravstveniRadnik * instance();

private:
    static ZdravstveniRadnik * s_instance;
};

class ZdravstvenaUsluga : public QSqlQueryModel
{
public:
    static ZdravstvenaUsluga * instance();
private:
    static ZdravstvenaUsluga * s_instance;
};

#endif // MODELS_H

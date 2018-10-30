#include "models.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#define DATABASE_SQLITE

bool Database::init()
{
#ifdef DATABASE_SQLITE
    // SQLITE
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zdravstvo.db");
#endif
}

ZdravstvenoOdeljene * ZdravstvenoOdeljene::s_instance = 0;

ZdravstvenoOdeljene * ZdravstvenoOdeljene::instance()
{
    if (!s_instance)
        s_instance = new ZdravstvenoOdeljene();

    s_instance->select();
    return s_instance;
}

ZdravstvenoOdeljene::ZdravstvenoOdeljene()
{
    setTable("ZdravstvenoOdeljenje");
}

ZdravstveniRadnik * ZdravstveniRadnik::s_instance = 0;

ZdravstveniRadnik * ZdravstveniRadnik::instance()
{
    if (!s_instance)
        s_instance = new ZdravstveniRadnik();

    return s_instance;
}

ZdravstvenaUsluga * ZdravstvenaUsluga::s_instance = 0;

ZdravstvenaUsluga * ZdravstvenaUsluga::instance()
{
    if (!s_instance)
        s_instance = new ZdravstvenaUsluga();

    return s_instance;
}

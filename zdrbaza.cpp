#include "zdrbaza.h"
#include <QDir>
#include <QMessageBox>

//ZdrBaza::ZdrBaza(QObject *parent)
//{

//}

bool ZdrBaza::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mozart.konkordia.edu");
    db.setDatabaseName("musicdb");
    db.setUserName("gbatstone");
    db.setPassword("T17aV44");
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return false;
    }
    return true;
}
QSqlError ZdrBaza::lastError()

{
// If opening database has failed user can ask
// error description by QSqlError::text()
return db.lastError();
}


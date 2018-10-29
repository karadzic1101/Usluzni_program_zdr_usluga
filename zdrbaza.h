#ifndef ZDRBAZA_H
#define ZDRBAZA_H

#include <QObject>

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

class ZdrBaza : public QObject
{
public:
   ZdrBaza(QObject *parent = 0);
   ~ZdrBaza();

public:
   bool createConnection();
   QSqlError lastError();
private:
   QSqlDatabase db;
};

#endif // ZDRBAZA_H

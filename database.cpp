
#include "database.h"
#include <QDebug>

void pripremiZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int broj, QString vreme)
{
    if(!q.prepare(QLatin1String("insert into ZdravstveniRadnik(imePrezime, zanimanje, jmbg, id_usluge, broj_usluge, vreme_brisanja)"
                                  "values(?,?,?,?, ?, ?)")))
    {
        qDebug() << "JMBG PROBLEM!!!";
        return;
    }
    q.addBindValue(radnik);
    q.addBindValue(zanimanje);
    q.addBindValue(jmbg);
    q.addBindValue(id_usl);
    q.addBindValue(broj);
    q.addBindValue(vreme);
    q.exec();
}

void dodajZdrUslugu(QSqlQuery &q, const QString &usluga)
{
    if(!q.prepare(QLatin1String("insert into ZdravstvenaUsluga(naziv_usluge) values(?)")))
    {
        qDebug() << "zdr_usl PROBLEM!!!";
        return;
    }
    q.addBindValue(usluga);
    q.exec();
}

void pripremiZdrUslugu(QSqlQuery &q, const QString &usluga)
{
    if(!q.prepare("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?"))
    {
        qDebug() << "zdr_usl PROBLEM!!!";
        return;
    }
    q.addBindValue(usluga);
    q.exec();
    q.first();
}

void dodajJmbg(QSqlQuery &q, QString jmbg)
{
    if(!q.prepare("SELECT jmbg from ZdravstveniRadnik where jmbg like ?"))
        return;
    q.addBindValue(jmbg);
    q.exec();
    q.first();
}

void nadjiIDusluge(QSqlQuery &q, QString zdr_usl)
{
    if(!q.prepare(QLatin1String("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?")))
        return;
    q.addBindValue(zdr_usl);
    q.exec();
    q.first();
}

void nadjiIDRadnika(QSqlQuery &q, QString zdr_rad)
{
    if (!q.prepare("select id_radnika from ZdravstveniRadnik where imePrezime like ?"))
        return;
    q.addBindValue(zdr_rad);
    q.exec();
    q.first();
}

void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje, int idRadnika, int idUsluge)
{
    if (!q.prepare("insert into ZdravstvenaOdeljenja(naziv, id_radnika, id_usluge) values(?, ?, ?)"))
        return;
    q.addBindValue(odeljenje);
    q.addBindValue(idRadnika);
    q.addBindValue(idUsluge);
    q.exec();
}


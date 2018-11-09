
#include "database.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int broj, QString vreme)
{
    q.exec("select date('now')");
//    int trenutno_vreme = q.value(0).toInt();
    qDebug() << q.value(0).toDate();
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

//void updateZdrUslugu(QSqlQuery &q, QString zdr_usl)
//{
//    pripremiZdrUslugu(q, zdr_usl);
//    int id_usl = q.value(0).toInt();
//    if (!q.prepare("select count(imePrezime) from ZdravstveniRadnik where id_usluge like ?"))
//        return;
//    q.addBindValue(id_usl);
//    q.exec();
//    q.first();
//    int count_idUsl = q.value(0).toInt();
//    if (!q.prepare("update ZdravstvenaUsluga set ukupnoUsluga like ? where naziv_usluge like ?"))
//        return;
//    q.addBindValue(count_idUsl);
//    qDebug() << count_idUsl;
//    q.addBindValue(zdr_usl);
//    q.exec();
//}


QString dodajJmbg(QSqlQuery &q, QString jmbg)
{
    if(!q.prepare("SELECT jmbg from ZdravstveniRadnik where jmbg like ?"))
        return NULL;
    q.addBindValue(jmbg);
    q.exec();
    q.first();
    return q.value(0).toString();
}

int nadjiIDusluge(QSqlQuery &q, QString zdr_usl)
{
    if(!q.prepare(QLatin1String("select id_usluge from ZdravstvenaUsluga where naziv_usluge like ?")))
        return -1;
    q.addBindValue(zdr_usl);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

QString nadjiOdeljenje(QSqlQuery &q, QString odeljenje)
{
    if(!q.prepare(QLatin1String("select naziv from ZdravstvenaOdeljenja where naziv like ?")))
        return NULL;
    q.addBindValue(odeljenje);
    q.exec();
    q.first();
    return q.value(0).toString();
}

void nadjiIDRadnika(QSqlQuery &q, QString zdr_rad)
{
    if (!q.prepare("select id_radnika from ZdravstveniRadnik where imePrezime like ?"))
        return;
    q.addBindValue(zdr_rad);
    q.exec();
    q.first();
    qDebug() << q.value(0).toInt();
    return;
}

void nadjiIdRadUsl(QSqlQuery &q, int idRad, int idUsl)
{
    if(!q.prepare("select naziv from ZdravstvenaOdeljenja where id_radnika like ? and id_usluge like ?"))
        return;
    q.addBindValue(idRad);
    q.addBindValue(idUsl);
    q.exec();
    q.first();
    return;
}

void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje)
{
    if (!q.prepare("insert into ZdravstvenaOdeljenja(naziv) values(?)"))
        return;
    q.addBindValue(odeljenje);
    q.exec();
    return;
}

int brojUsluga(QSqlQuery &query, int idUsluge)
{
    if (!query.prepare("select count(imePrezime) from ZdravstveniRadnik where id_usluge like ?"))
        return -1;
    query.addBindValue(idUsluge);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

int brUslugaPoRadniku(QSqlQuery &q, QString radnik, int idUsluge)
{
    if(!q.prepare("select " + radnik + " from ZdravstvenaUsluga where id_usluge like ?"))
        qDebug() << "brUslugaPoRadniku!!!!!!!!!!!";
    q.addBindValue(idUsluge);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

void dodajNovogRadnika(QSqlQuery &q, QString zdr_rad)
{
    bool ok = 1;
    if(!q.prepare("pragma table_info(ZdravstvenaUsluga)")) {
        qDebug() << "PRAGMA PROBLEM!!!";
        return;
    }
    q.exec();
    q.first();

    while(q.next()) {
        if (q.value(1).toString() == zdr_rad) {
            qDebug() << q.value(1).toString();
            ok = 0;
        }
        qDebug() << "ok =" << ok;
    }

    if (ok)
        q.exec("alter table ZdravstvenaUsluga add " + zdr_rad + " integer");
}

void updateBrojUsluga(QSqlQuery &q, QString radnik, QString usluga)
{
    int idU = nadjiIDusluge(q, usluga);
    if(!q.prepare("select count(imePrezime) from ZdravstveniRadnik where id_usluge like ? and imePrezime like ?")) {
        qDebug() << "broj usluga po doktoru PROBLEM";
        return;
    }
    q.addBindValue(idU);
    q.addBindValue(radnik);
    q.exec();
    q.first();
    int brUsluga = q.value(0).toInt();
    q.prepare("update ZdravstvenaUsluga set " + radnik + "=" + QString::number(brUsluga) + " where id_usluge like " + QString::number(idU));
    if(!q.exec())
         qDebug() << "FAILED!!!!!!!!!" << q.lastError();
    else
        qDebug() << "dobro je";
    return;
}

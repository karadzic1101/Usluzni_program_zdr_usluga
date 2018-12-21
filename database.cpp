#include "database.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

void deletePatients(QSqlQuery &q, QString date)
{
    if (!q.prepare("delete from ZdravstveniRadnik where vreme_brisanja like ?"))
        qDebug() << "delete PROBLEM";
    q.addBindValue(date);
    q.exec();
}

void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int mesec, QString vreme)
{
    if(!q.prepare(QLatin1String("insert into ZdravstveniRadnik(imePrezime, zanimanje, jmbg, id_usluge, mesec_unosa, vreme_brisanja)"
                                  "values(?,?,?,?,?,?)")))
    {
        qDebug() << "JMBG PROBLEM!!!";
        return;
    }
    q.addBindValue(radnik);
    q.addBindValue(zanimanje);
    q.addBindValue(jmbg);
    q.addBindValue(id_usl);
    q.addBindValue(mesec);
    q.addBindValue(vreme);
    q.exec();
}

void dodajZdrUslugu(QSqlQuery &q, const QString &usluga, int broj)
{
    if(!q.prepare(QLatin1String("insert into ZdravstvenaUsluga(naziv_usluge, ukupno_usluge) values(?, ?)")))
    {
        qDebug() << "zdr_usl PROBLEM!!!";
        return;
    }
    q.addBindValue(usluga);
    q.addBindValue(broj);
    q.exec();
}

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

int brojZdrUsluga(QSqlQuery &query, int idUsluge)
{
    if (!query.prepare("select ukupno_usluge from ZdravstvenaUsluga where id_usluge like ?"))
        return -1;
    query.addBindValue(idUsluge);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

int brUslugaPoRadniku(QSqlQuery &q, int idUsluge, int mesec)
{
    if(!q.prepare("select count(*) from ZdravstveniRadnik where id_usluge like "+ QString::number(idUsluge) +" "
                  "and mesec_unosa like " + QString::number(mesec)))
        qDebug() << "brUslugaPoRadniku!!!!!!!!!!!";
    q.exec();
    q.first();
    return q.value(0).toInt();
}

void updateVremeBrisanje(QSqlQuery &q, QString jmbg, QString datum_brisanja)
{
    if (!q.prepare("update ZdravstveniRadnik set vreme_brisanja = ? where jmbg like ?"))
        qDebug("Promena vremena!!!!");
    q.addBindValue(datum_brisanja);
    q.addBindValue(jmbg);
    q.exec();
}

//void dodajNovogRadnika(QSqlQuery &q, QString zdr_rad)
//{
//    bool ok = 1;
//    if(!q.prepare("pragma table_info(ZdravstvenaUsluga)")) {
//        qDebug() << "PRAGMA PROBLEM!!!";
//        return;
//    }
//    q.exec();
//    q.first();

//    while(q.next()) {
//        if (q.value(1).toString() == zdr_rad) {
//            qDebug() << q.value(1).toString();
//            ok = 0;
//        }
//        qDebug() << "ok =" << ok;
//    }

//    if (ok)
//        q.exec("alter table ZdravstvenaUsluga add " + zdr_rad + " integer");
//}

//void updateBrojUsluga(QSqlQuery &q, QString radnik, QString usluga)
//{
//    int idU = nadjiIDusluge(q, usluga);
//    if(!q.prepare("select count(imePrezime) from ZdravstveniRadnik where id_usluge like ? and imePrezime like ?")) {
//        qDebug() << "broj usluga po doktoru PROBLEM";
//        return;
//    }
//    q.addBindValue(idU);
//    q.addBindValue(radnik);
//    q.exec();
//    q.first();
//    int brUsluga = q.value(0).toInt();
//    q.prepare("update ZdravstvenaUsluga set " + radnik + "=" + QString::number(brUsluga) + " where id_usluge like " + QString::number(idU));
//    if(!q.exec())
//         qDebug() << "FAILED!!!!!!!!!" << q.lastError();
//    else
//        qDebug() << "dobro je";
//    return;
//}

void updateZdrUslugu(QSqlQuery &q, int zdr_usl, int brojUsluga)
{
    if (!q.prepare("update ZdravstvenaUsluga set ukupno_usluge = " + QString::number(brojUsluga) +
                   "  where id_usluge like " + QString::number(zdr_usl)))
        qDebug() << "UPDATE ZdravstvenaUsluga PROBLEM";
    q.exec();
}

#include "database.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

void deletePatients(QSqlQuery &q, QString date)
{
    if (!q.prepare("delete from PruzeneUsluge where datum_brisanja <= ?"))
        qDebug() << "delete PROBLEM";
    q.addBindValue(date);
    q.exec();
}

void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString odeljenje)
{
    int idOdeljenja = zdrOdeljenje(q, odeljenje);
    if(!q.prepare(QLatin1String("insert into ZdravstveniRadnik(imePrezime, id_odeljenja)"
                                  "values(?,?)")))
    {
        qDebug() << "JMBG PROBLEM!!!";
        return;
    }
    q.addBindValue(radnik);
    q.addBindValue(idOdeljenja);
    q.exec();
}

void dodajPruzenuUslugu(QSqlQuery &q, QString jmbg, int id_rad, int id_usl, QString datum, QString datum_brisanja)
{
    if(!q.prepare("insert into PruzeneUsluge(jmbg, id_radnika, id_usluge, datum_unosa, datum_brisanja) "
                  "values(?,?,?,?,?)"))
        qDebug() << "preuzeneUsluge PROBLEM!!!";
    q.addBindValue(jmbg);
    q.addBindValue(id_rad);
    q.addBindValue(id_usl);
    q.addBindValue(datum);
    q.addBindValue(datum_brisanja);
    q.exec();
}

int zdrOdeljenje(QSqlQuery &q, QString odeljenje)
{
    if(!q.prepare("select id_odeljenja from ZdravstvenaOdeljenja where naziv like ?"))
        return -1;
    q.addBindValue(odeljenje);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

void dodajZdrUslugu(QSqlQuery &q, const QString &usluga, QString odeljenje)
{
    int idOdeljenja = zdrOdeljenje(q, odeljenje);
    if(!q.prepare(QLatin1String("insert into ZdravstvenaUsluga(naziv_usluge, id_odeljenja) values(?, ?)")))
    {
        qDebug() << "zdr_usl PROBLEM!!!";
        return;
    }
    q.addBindValue(usluga);
    q.addBindValue(idOdeljenja);
    q.exec();
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

int nadjiOdeljenje(QSqlQuery &q, QString odeljenje)
{
    if(!q.prepare(QLatin1String("select id_odeljenja from ZdravstvenaOdeljenja where naziv like ?")))
        return -1;
    q.addBindValue(odeljenje);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

int nadjiIDRadnika(QSqlQuery &q, QString zdr_rad)
{
    if (!q.prepare("select id_radnika from ZdravstveniRadnik where imePrezime like ?"))
        return -1;
    q.addBindValue(zdr_rad);
    q.exec();
    q.first();
    qDebug() << q.value(0).toInt();
    return q.value(0).toInt();
}

void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje)
{
    qDebug() << odeljenje;
    if (!q.prepare("insert into ZdravstvenaOdeljenja(naziv) values(?)"))
        return;
    q.addBindValue(odeljenje);
    q.exec();
    return;
}

void dodajPacijenta(QSqlQuery &q, QString jmbg)
{
    if (!q.prepare("insert into Pacijent(jmbg) values(?)"))
        qDebug() << "tabela Pacijent PROBLEM!!!";
    q.addBindValue(jmbg);
    q.exec();
}

QString nadjiJmbg(QSqlQuery &q, QString jmbg)
{
    if (!q.prepare("select jmbg from Pacijent where jmbg like ?")) {
        qDebug() << "GRESKAAAAA!!!";
        return NULL;
    }
    q.addBindValue(jmbg);
    q.exec();
    q.first();
    return q.value(0).toString();
}

void updateVremeBrisanje(QSqlQuery &q, QString jmbg, QString datum_brisanja)
{
    if (!q.prepare("update PruzeneUsluge set vreme_brisanja = ? where jmbg like ?"))
        qDebug("Promena vremena!!!!");
    q.addBindValue(datum_brisanja);
    q.addBindValue(jmbg);
    q.exec();
}

void mesecniIzvestaj(QSqlQuery &q, int id_rad, int id_usluge, int mesec, int broj_usluga)
{
    if (!q.prepare("insert into MesecniIzvestaj(id_radnika, id_usluge, mesec, broj_usluga) values(?,?,?,?)"))
        qDebug() << "Unos u mesecni izvestaj PROBLEM!!!!";
    q.addBindValue(id_rad);
    q.addBindValue(id_usluge);
    q.addBindValue(mesec);
    q.addBindValue(broj_usluga);
    q.exec();
}

int brojUsluga(QSqlQuery &q, int id_radnika, int id_usluge)
{
    if (!q.prepare("select broj_usluga from MesecniIzvestaj where id_radnika like ? and id_usluge like ?"))
    {
        qDebug() << "brojUsluge PROBLEM!!!";
        return -1;
    }
    q.addBindValue(id_radnika);
    q.addBindValue(id_usluge);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

void updateMesecniIzvestaj(QSqlQuery &q, int id_rad, int id_usluge, int mesec, int broj_usluga)
{
    if(!q.prepare("update MesecniIzvestaj set broj_usluga=? where id_radnika like ? and id_usluge like ?"))
    {
        qDebug() << "update MesecniIzvestaj PROBLEM";
        return;
    }
    q.addBindValue(broj_usluga);
    q.addBindValue(id_rad);
    q.addBindValue(id_usluge);
    q.exec();
}

int getMonth(QSqlQuery &q)
{
    if (!q.prepare("select mesec from MesecniIzvestaj")) {
       qDebug() << "Izvlacenje meseca PROBLEM!!!!";
       return -1;
    }
    q.exec();
    q.first();
    qDebug() << "upit mesec " << q.value(0).toInt();
    return q.value(0).toInt();
}

int getYear(QSqlQuery &q)
{
    if (!q.prepare("select godina from GodisnjiIzvestaj")) {
       qDebug() << "Izvlacenje godine PROBLEM!!!!";
       return -1;
    }
    q.exec();
    q.first();
    qDebug() << "godina iz izvestaja " << q.value(0).toInt();
    return q.value(0).toInt();
}

void godisnjiIzvestaj(QSqlQuery &q, int mesec, int godina, int radnik, int usluga, int br_usluga)
{
    if (!q.prepare("inser into GodisnjiIzvestaj(id_radnika, id_usluge, godina, " + QString::number(mesec) + ") values(?,?,?,?)"))
    {
        qDebug() << "unos u GodisnjiIzvestaj PROBLEM!!!!!!!!";
        return;
    }
    q.addBindValue(radnik);
    q.addBindValue(usluga);
    q.addBindValue(godina);
    q.addBindValue(br_usluga);
    q.exec();
    return;
}

void resetMesecnogIzvestaja(QSqlQuery &q)
{
    if (!q.prepare("delete from MesecniIzvestaj"))
        qDebug() << "brisanje MesecniIzvestaj PROBLEM";
    q.exec();
    return;
}

void resetGodisnjiIzvestaj(QSqlQuery &q)
{
    if (!q.prepare("delete from GodisnjiIzvestaj"))
        qDebug() << "brisanje GodisnjiIzvestaj PROBLEM";
    q.exec();
    return;
}

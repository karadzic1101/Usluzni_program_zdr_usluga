#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>


#endif // DATABASE_H

void deletePatients(QSqlQuery &q, QString date);
void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString odeljenje);
void dodajPruzenuUslugu(QSqlQuery &q, QString jmbg, int id_rad, int id_usl, QString datum, QString datum_brisanja);
int zdrOdeljenje(QSqlQuery &q, QString odeljenje);
void dodajZdrUslugu(QSqlQuery &q, const QString &usluga, QString odeljenje);
int nadjiIDusluge(QSqlQuery &q, QString zdr_usl);
int nadjiOdeljenje(QSqlQuery &q, QString odeljenje);
int nadjiIDRadnika(QSqlQuery &q, QString zdr_rad);
void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje);
void dodajPacijenta(QSqlQuery &q, QString jmbg);
QString nadjiJmbg(QSqlQuery &q, QString jmbg);
void updateVremeBrisanje(QSqlQuery &q, QString jmbg, QString datum_brisanja);
void mesecniIzvestaj(QSqlQuery &q, int id_rad, int id_usluge, int mesec, int broj_usluga);
int brojUsluga(QSqlQuery &q, int id_radnika, int id_usluge);
void updateMesecniIzvestaj(QSqlQuery &q, int id_rad, int id_usluge, int mesec, int broj_usluga);
int getMonth(QSqlQuery &q);
int getYear(QSqlQuery &q);
void godisnjiIzvestaj(QSqlQuery &q, int mesec, int godina, int radnik, int usluga, int br_usluga);
void resetMesecnogIzvestaja(QSqlQuery &q);
void resetGodisnjiIzvestaj(QSqlQuery &q);
QString nadjiRadnika(QSqlQuery &q, int id_radnika);
int nadjiIDRadnikaIzvestaj(QSqlQuery &q, int id_radnika);
int nadjiIDuslugeIzvestaj(QSqlQuery &q, int id_usluge);

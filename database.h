#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>

void dodajZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int mesec, QString vreme);
void dodajZdrUslugu(QSqlQuery &q, const QString &usluga, int broj);
QString dodajJmbg(QSqlQuery &q, QString jmbg);
int nadjiIDusluge(QSqlQuery &q, QString zdr_usl);
void nadjiIDRadnika(QSqlQuery &q, QString zdr_rad);
void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje);
void dodajZdrUslugu(QSqlQuery &q, const QString &usluga);
void nadjiIdRadUsl(QSqlQuery &q, int idRad, int idUsl);
QString nadjiOdeljenje(QSqlQuery &q, QString odeljenje);
void updateZdrUslugu(QSqlQuery &q, int zdr_usl, int brojUsluga);
int brojZdrUsluga(QSqlQuery &query, int idUsluge);
int brUslugaPoRadniku(QSqlQuery &q, int idUsluge, int mesec);
void dodajNovogRadnika(QSqlQuery &q, QString zdr_rad);
void updateBrojUsluga(QSqlQuery &q, QString radnik, QString usluga);
void updateVremeBrisanje(QSqlQuery &q, QString jmbg, QString datum_brisanja);
void deletePatients(QSqlQuery &q, QString date);

#endif // DATABASE_H


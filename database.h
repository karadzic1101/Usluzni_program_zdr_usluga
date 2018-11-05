#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>

void pripremiZdrRadnika(QSqlQuery &q, const QString &radnik, QString zanimanje, QString jmbg, int id_usl, int broj, QString vreme);
void pripremiZdrUslugu(QSqlQuery &q, const QString &usluga);
void dodajJmbg(QSqlQuery &q, QString jmbg);
void nadjiIDusluge(QSqlQuery &q, QString zdr_usl);
void nadjiIDRadnika(QSqlQuery &q, QString zdr_rad);
void dodajZdravstvenoOdeljenje(QSqlQuery &q, QString odeljenje, int idRadnika, int idUsluge);
void dodajZdrUslugu(QSqlQuery &q, const QString &usluga);

#endif // DATABASE_H


#include "izvestajform.h"
#include "ui_izvestajform.h"
#include "database.h"

#include <QDebug>

IzvestajForm::IzvestajForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IzvestajForm)
{
    ui->setupUi(this);   
}

IzvestajForm::~IzvestajForm()
{
    delete ui;
}

void IzvestajForm::zdravstveneUsluge(const QList<QString> &usluge)
{
    ui->comboBox->addItems(usluge);
}

void IzvestajForm::posaljiQuery(const QSqlQuery &q)
{
    query = q;
}

void IzvestajForm::on_buttonBox_accepted()
{
    if (ui->rb_mesecni_izvestaj->isChecked())
        ispisiMesecniIzvestaj();
    else if (ui->rb_godisnji_izvestaj->isChecked())
        ispisiGodisnjiIzvestaj();
}

void IzvestajForm::procitajGodisnjiIzvestaj()
{
    QString usluga = ui->comboBox->currentText();
    int id_usluge = nadjiIDusluge(query, usluga);

    if(!query.prepare("select * from GodisnjiIzvestaj where id_usluge like ?"))
        qDebug() << "citanje iz godisnjeg izvestaja PROBLEM";
    query.addBindValue(id_usluge);
    query.exec();
    query.first();

    id_radnika.append(query.value(0).toInt());
    januar.append(query.value(3).toInt());
    februar.append(query.value(4).toInt());
    mart.append(query.value(5).toInt());
    april.append(query.value(6).toInt());
    maj.append(query.value(7).toInt());
    jun.append(query.value(8).toInt());
    jul.append(query.value(9).toInt());
    avgust.append(query.value(10).toInt());
    septembar.append(query.value(11).toInt());
    oktobar.append(query.value(12).toInt());
    novembar.append(query.value(13).toInt());
    decembar.append(query.value(14).toInt());

    while(query.next()) {
        id_radnika.append(query.value(0).toInt());
        januar.append(query.value(3).toInt());
        februar.append(query.value(4).toInt());
        mart.append(query.value(5).toInt());
        april.append(query.value(6).toInt());
        maj.append(query.value(7).toInt());
        jun.append(query.value(8).toInt());
        jul.append(query.value(9).toInt());
        avgust.append(query.value(10).toInt());
        septembar.append(query.value(11).toInt());
        oktobar.append(query.value(12).toInt());
        novembar.append(query.value(13).toInt());
        decembar.append(query.value(14).toInt());
    }

    imenaRadnika(id_radnika);
}

void IzvestajForm::procitajMesecniIzvestaj()
{
    QString usluga = ui->comboBox->currentText();
    int id_usluge = nadjiIDusluge(query, usluga);

    if (!query.prepare("select id_radnika, broj_usluga, sum(broj_usluga) from MesecniIzvestaj where id_usluge like ?"))
        qDebug() << "citanje iz mesecnog izvestaja PROBLEM!!!";

    query.addBindValue(id_usluge);
    query.exec();
    query.first();

    id_radnika.append(query.value(0).toInt());
    kolicina_usluga.append(query.value(1).toInt());
    ukupno_usluge = query.value(2).toInt();

    while(query.next()) {
        id_radnika.append(query.value(0).toInt());
        kolicina_usluga.append(query.value(1).toInt());
        ukupno_usluge = query.value(2).toInt();
    }

    qDebug() << "ukupno usluga " << ukupno_usluge;
    qDebug() << "usluge " << kolicina_usluga;

    imenaRadnika(id_radnika);
}

void IzvestajForm::imenaRadnika(QList<int> id_radnika)
{
    broj_radnika = id_radnika.size();
    for (int i=0; i<broj_radnika; i++) {
        QString radnik = nadjiRadnika(query, id_radnika[i]);
        radnici.append(radnik);
    }
}

void IzvestajForm::ispisiMesecniIzvestaj()
{
    procitajMesecniIzvestaj();

    ui->textEdit->setText("");

    ui->textEdit->setText("Ukupno je bilo " + QString::number(ukupno_usluge) + " " + ui->comboBox->currentText());
    for(int i = 0; i<broj_radnika; i++) {
        ui->textEdit->append(radnici[i] + "\t" + QString::number(kolicina_usluga[i]));
    }

    radnici.clear();
    kolicina_usluga.clear();
    id_radnika.clear();
    qDebug() << "mesecni izvestaj";
}

void IzvestajForm::ispisiGodisnjiIzvestaj()
{
    procitajGodisnjiIzvestaj();

    ui->textEdit->setText("");

    for(int i = 0; i<broj_radnika; i++)
        ui->textEdit->append(radnici[i] + "\t" + QString::number(januar[i])
                                        + "\t" + QString::number(februar[i])
                             + "\t" + QString::number(mart[i])
                             + "\t" + QString::number(april[i])
                             + "\t" + QString::number(maj[i])
                             + "\t" + QString::number(jun[i])
                             + "\t" + QString::number(jul[i])
                             + "\t" + QString::number(avgust[i])
                             + "\t" + QString::number(septembar[i])
                             + "\t" + QString::number(oktobar[i])
                             + "\t" + QString::number(novembar[i])
                             + "\t" + QString::number(decembar[i]));
}

void IzvestajForm::on_buttonBox_rejected()
{
    close();
}

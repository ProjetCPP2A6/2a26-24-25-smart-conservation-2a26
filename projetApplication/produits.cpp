#include "produits.h"
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Produits::Produits()
{
    ID_PRODUIT=0;
    NOM_PRODUIT="";
    QTE=0;
    DATE_PEREMPTION="";
    ETAT="";
    PRIX_UNITAIRE=0;
}
Produits::Produits(int ID_PRODUIT,QString NOM_PRODUIT,int QTE ,QString DATE_PEREMPTION, QString ETAT , float PRIX_UNITAIRE)
{
    this->ID_PRODUIT=ID_PRODUIT;
    this->NOM_PRODUIT=NOM_PRODUIT;
    this->QTE=QTE;
    this->DATE_PEREMPTION=DATE_PEREMPTION;
    this->ETAT=ETAT;
    this-> PRIX_UNITAIRE=PRIX_UNITAIRE;


}
bool Produits::ajouterprod()
{
    QSqlQuery query;
    QString r=QString::number(ID_PRODUIT);
    query.prepare("insert into produits(ID_PRODUIT,NOM_PRODUIT,QTE,DATE_PEREMPTION,ETAT,PRIX_UNITAIRE)" "values(:ID_PRODUIT,:NOM_PRODUIT,:QTE,:DATE_PEREMPTION,:ETAT,:PRIX_UNITAIRE)");
    query.bindValue(":ID_PRODUIT",r);
    query.bindValue(":NOM_PRODUIT",NOM_PRODUIT);
    query.bindValue(":QTE",QTE);
    query.bindValue(":DATE_PEREMPTION",DATE_PEREMPTION);
    query.bindValue(":ETAT",ETAT);
    query.bindValue(":PRIX_UNITAIRE", PRIX_UNITAIRE);

    return query.exec();
    if (!query.exec()){
        qDebug() <<"echec:" <<query.lastError().text();
        return false;
    }
    else
        return true;

}
QSqlQueryModel * Produits::afficherprod()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from produits");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("QTE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRIX_UNITAIRE"));
    return model;

}
/* */



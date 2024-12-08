#include "commandes.h"
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Commandes::Commandes()
{
    ID_COMMANDE=0;
    NOM_CLIENT="";
    METHOD_PAIEMENT="";
    LIVRAISON="false";
    MONTANT=0;
    DATE_COMMANDE="";
    ETAT="en cours";
    PRIX_FINAL=0;
    ID_PRODUIT=0;
    QTE_PRODUITS=0;

}
Commandes::Commandes(int ID_COMMANDE, QString NOM_CLIENT, QString METHOD_PAIEMENT, QString DATE_COMMANDE, int ID_PRODUIT, int QTE_PRODUITS)
{
    this->ID_COMMANDE=ID_COMMANDE;
    this->NOM_CLIENT=NOM_CLIENT;
    this->METHOD_PAIEMENT=METHOD_PAIEMENT;
    LIVRAISON="false";
    MONTANT=0;
    this->DATE_COMMANDE=DATE_COMMANDE;
    ETAT="en cours";
    PRIX_FINAL=0;
    this->ID_PRODUIT=ID_PRODUIT;
    this->QTE_PRODUITS=QTE_PRODUITS;
}


bool Commandes::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO Commandes(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT, LIVRAISON, MONTANT, DATE_COMMANDE, ETAT, PRIX_FINAL , ID_PRODUIT ,QTE_PRODUITS) "
                  "VALUES(:ID_COMMANDE, :NOM_CLIENT, :METHOD_PAIEMENT, :LIVRAISON, :MONTANT, :DATE_COMMANDE, :ETAT, :PRIX_FINAL,:ID_PRODUIT,:QTE_PRODUITS)");

    query.bindValue(":ID_COMMANDE", ID_COMMANDE);
    query.bindValue(":NOM_CLIENT", NOM_CLIENT);
    query.bindValue(":METHOD_PAIEMENT", METHOD_PAIEMENT);
    query.bindValue(":LIVRAISON", LIVRAISON);
    query.bindValue(":MONTANT", MONTANT);
    query.bindValue(":DATE_COMMANDE", DATE_COMMANDE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":PRIX_FINAL", PRIX_FINAL);
    query.bindValue(":ID_PRODUIT", ID_PRODUIT);
    query.bindValue(":QTE_PRODUITS", QTE_PRODUITS);

    if(!query.exec())
    {
        qDebug()<< "Erreur lors de l'ajout de la commande::::"<< query.lastError().text();
        return false;
    }
    return true;

}





QSqlQueryModel * Commandes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Commandes");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL: " << model->lastError().text();
    }

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COMMANDE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_CLIENT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("METHOD_PAIEMENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("LIVRAISON"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MONTANT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_COMMANDE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("PRIX_FINAL"));

    return model;
}
bool Commandes::supprimer(int ID_COMMANDE)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Commandes WHERE ID_COMMANDE = :ID_COMMANDE");
    query.bindValue(":ID_COMMANDE", ID_COMMANDE);  // Directly bind the integer ID_COMMANDE

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de la commande:" << query.lastError().text();
        return false;
    }

    return true;

}
QSqlQueryModel* Commandes::chercher(int ID_COMMANDE)
{
    QSqlQueryModel* model = new QSqlQueryModel();


    QSqlQuery query;
    query.prepare("SELECT * FROM commandes WHERE ID_COMMANDE = :ID_COMMANDE");
    query.bindValue(":ID_COMMANDE", ID_COMMANDE);

    if (!query.exec()) {

        qDebug() << "Erreur SQL : " << query.lastError().text();
        return nullptr;
    }

    model->setQuery(query);

    return model;
}


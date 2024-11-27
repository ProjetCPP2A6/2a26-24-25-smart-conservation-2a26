#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>

class Produits
{
    int ID_PRODUIT;
    QString NOM_PRODUIT;
    int QTE;
    QString DATE_PEREMPTION;
    QString ETAT;
    float PRIX_UNITAIRE;

public:

    Produits();
    Produits(int,QString,int,QString,QString,float);


    int getID_PRODUIT(){return ID_PRODUIT;}
    QString getNOM_PRODUIT(){return NOM_PRODUIT;}
    int getQTE(){return QTE;}
    QString getDATE_PEREMPTION(){return DATE_PEREMPTION;}
    QString getIETAT(){return ETAT;}
    float getPRIX_UNITAIRE(){return PRIX_UNITAIRE;}


    void setID_PRODUIT(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
    void setNOM_PRODUIT(QString NOM_PRODUIT){this->NOM_PRODUIT=NOM_PRODUIT;}
    void setQTE(int QTE){this->QTE=QTE;}
    void setDATE_PEREMPTION(QString DATE_PEREMPTION){this->DATE_PEREMPTION=DATE_PEREMPTION;}
    void setIETAT(QString ETAT){this->ETAT=ETAT;}
    void setPRIX_UNITAIRE(float PRIX_UNITAIRE){this->PRIX_UNITAIRE=PRIX_UNITAIRE;}


    bool ajouterprod();
    QSqlQueryModel * afficherprod();


};

#endif // PRODUITS_H

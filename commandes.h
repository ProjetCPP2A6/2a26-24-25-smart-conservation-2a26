#ifndef COMMANDES_H
#define COMMANDES_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Commandes
{
    int ID_COMMANDE;
    QString NOM_CLIENT;
    QString METHOD_PAIEMENT;
    QString LIVRAISON;
    float MONTANT;
    QString DATE_COMMANDE;
    QString ETAT;
    float PRIX_FINAL;

public:
    Commandes();
    Commandes(int ID_COMMANDE, QString NOM_CLIENT, QString METHOD_PAIEMENT, QString DATE_COMMANDE);
    int getID_COMMANDE(){return ID_COMMANDE;}
    QString getNOM_CLIENT(){return NOM_CLIENT;}
    QString getMETHOD_PAIEMENT(){return METHOD_PAIEMENT;}
    QString getLIVRAISON(){return LIVRAISON;}
    float getMONTANT(){return MONTANT;}
    QString getDATE_COMMANDE(){return DATE_COMMANDE;}
    QString getETAT(){return ETAT;}
    float getPRIX_FINAL(){return PRIX_FINAL;}


    void setID_COMMANDE(int ID_COMMANDE){this->ID_COMMANDE=ID_COMMANDE;}
    void setNOM_CLIENT(QString NOM_CLIENT){this->NOM_CLIENT=NOM_CLIENT;}
    void setMETHOD_PAIEMENT(QString METHOD_PAIEMENT){this->METHOD_PAIEMENT=METHOD_PAIEMENT;}
    void setLIVRAISON(QString LIVRAISON){this->LIVRAISON=LIVRAISON;}
    void setMONTANT(float MONTANT){this->MONTANT=MONTANT;}
    void setDATE_COMMANDE(QString DATE_COMMANDE){this->DATE_COMMANDE=DATE_COMMANDE;}
    void setETAT(QString ETAT){this->ETAT=ETAT;}
    void setPRIX_FINAl(float PRIX_FINAL){this->PRIX_FINAL=PRIX_FINAL;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    QSqlQueryModel* chercher(int ID_COMMANDE);

};
#endif // COMMANDES_H

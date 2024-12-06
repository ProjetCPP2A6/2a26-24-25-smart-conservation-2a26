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
    int ID_PRODUIT;
    int QTE_PRODUITS;

public:
    Commandes();
    Commandes(int ID_COMMANDE, QString NOM_CLIENT, QString METHOD_PAIEMENT, QString DATE_COMMANDE,int ID_PRODUIT,int QTE_PRODUITS);
    int getID_COMMANDE(){return ID_COMMANDE;}
    QString getNOM_CLIENT(){return NOM_CLIENT;}
    QString getMETHOD_PAIEMENT(){return METHOD_PAIEMENT;}
    QString getLIVRAISON(){return LIVRAISON;}
    float getMONTANT(){return MONTANT;}
    QString getDATE_COMMANDE(){return DATE_COMMANDE;}
    QString getETAT(){return ETAT;}
    float getPRIX_FINAL(){return PRIX_FINAL;}
    int getID_PRODUIT(){return ID_PRODUIT;}
    int getQTE_PRODUITS(){return QTE_PRODUITS;}


    void setID_COMMANDE(int ID_COMMANDE){this->ID_COMMANDE=ID_COMMANDE;}
    void setNOM_CLIENT(QString NOM_CLIENT){this->NOM_CLIENT=NOM_CLIENT;}
    void setMETHOD_PAIEMENT(QString METHOD_PAIEMENT){this->METHOD_PAIEMENT=METHOD_PAIEMENT;}
    void setLIVRAISON(QString LIVRAISON){this->LIVRAISON=LIVRAISON;}
    void setMONTANT(float MONTANT){this->MONTANT=MONTANT;}
    void setDATE_COMMANDE(QString DATE_COMMANDE){this->DATE_COMMANDE=DATE_COMMANDE;}
    void setETAT(QString ETAT){this->ETAT=ETAT;}
    void setPRIX_FINAl(float PRIX_FINAL){this->PRIX_FINAL=PRIX_FINAL;}
    void setID_PRODUIT(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
    void setQTE_PRODUITS(int QTE_PRODUITS){this->QTE_PRODUITS=QTE_PRODUITS;}

    bool ajouterCommande();
    QSqlQueryModel * afficherCommande();
    bool supprimerCommande(int ID_COMMANDE);
    QSqlQueryModel * chercherCommande(int ID_COMMANDE);

    bool isID_COMMANDEUnique(int ID_COMMANDE);
    bool isValidDateCommande(const QString& dateString);

};
#endif // COMMANDES_H


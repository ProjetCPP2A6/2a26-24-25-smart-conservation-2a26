#include "comm_prod.h"
#include<QSqlQuery>

Comm_prod::Comm_prod() {}

Comm_prod::Comm_prod(int ID_COMMANDE,int ID_PRODUIT,int QUANTITE_AJOUTEE)
{
    this->ID_COMMANDE=ID_COMMANDE;
    this->ID_PRODUIT=ID_PRODUIT;
    this->QUANTITE_AJOUTEE=QUANTITE_AJOUTEE;
}

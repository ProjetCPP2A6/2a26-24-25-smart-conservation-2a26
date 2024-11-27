#ifndef COMM_PROD_H
#define COMM_PROD_H

class Comm_prod
{
    int ID_COMMANDE;
    int ID_PRODUIT;
    int QUANTITE_AJOUTEE;

public:
    Comm_prod();
    Comm_prod(int ID_COMMANDE,int ID_PRODUIT,int QUANTITE_AJOUTEE);
};

#endif // COMM_PROD_H

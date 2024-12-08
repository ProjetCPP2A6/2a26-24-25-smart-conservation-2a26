#ifndef CUISSON_H
#define CUISSON_H
#include "QString"
#include "QDateTime"
#include "ui_mainwindow.h"
#include "mainwindow.h"
class Cuisson
{
public:
    Cuisson();
    Cuisson(int, int,QDateTime,int,QString);
    QString getETAT(){return ETAT;}
    int getID_PRODUIT(){return ID_PRODUIT;}
     QDateTime getTIME(){return TIME;}
    int getID_CUISSON(){return ID_CUISSON;}
    void setETAT(QString ETAT){this->ETAT=ETAT;}
    int getQTE(){return QTE;}
    void setQTE(int QTE){this->QTE=QTE;}
    void setID_PRODUIT(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
    void setiID_CUISSON(int ID_CUISSON){this->ID_CUISSON=ID_CUISSON;}
    void setTIME(QDateTime TIME){this->TIME=TIME;}

bool ajouter();
bool supprimer(QString id);
bool modifier();
void afficher(Ui::MainWindow *ui);

private :
    QString ETAT;
    QDateTime TIME;
    int ID_CUISSON,ID_PRODUIT,QTE;
};

#endif

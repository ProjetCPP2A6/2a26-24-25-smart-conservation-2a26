#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QDate>
#include "ui_mainwindow.h"
#include "mainwindow.h"
class Produit
{
public:
    Produit();
    Produit(int, QString,QString,QDateTime,int);
    QString getNOM_PRODUIT(){return NOM_PRODUIT;}
    int getcandidat_id(){return ID_PRODUIT;}
    int getQTE(){return QTE;}
    void setQTE(int QTE){this->QTE=QTE;}
    QString getETAT(){return ETAT;}
    void setETAT(QString ETAT){this->ETAT=ETAT;}
     QDateTime getDATE_PEREMPTION(){return DATE_PEREMPTION;}
    void setNOM_PRODUIT(QString NOM_PRODUIT){this->NOM_PRODUIT=NOM_PRODUIT;}
    void seticandidat_id(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
    void setDATE_PEREMPTION(QDateTime DATE_PEREMPTION){this->DATE_PEREMPTION=DATE_PEREMPTION;}
bool ajouter();

bool supprimer(QString id);
bool modifier();
void afficher(Ui::MainWindow *ui);

private :
    QString NOM_PRODUIT,ETAT;
    int ID_PRODUIT;
    int QTE;
    QDateTime DATE_PEREMPTION;

};

#endif

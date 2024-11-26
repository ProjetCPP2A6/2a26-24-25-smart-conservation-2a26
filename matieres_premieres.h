#ifndef MATIERES_PREMIERES_H
#define MATIERES_PREMIERES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTimer>
#include <QEventLoop>

class Matieres_premieres
{
    QString TYPE;
    int ID;
    QString EXPIRYDATE;
    float QUANTITE;
    int SEUIL;

public:
    Matieres_premieres();
    Matieres_premieres(QString,int,QString,int);




    QString getTYPE(){return TYPE;}
    int getID(){return ID;}
    QString getEXPIRYDATE(){return EXPIRYDATE;}
    float getQUANTITE(){return QUANTITE;}
    int getSEUIL(){return SEUIL;}

    void setTYPE(QString t){TYPE=t;}
    void setID(int ID){this->ID=ID;}
    void setEXPIRYDATE(QString exdate){EXPIRYDATE=exdate;}
    void setQUANTITE(float qte){QUANTITE=qte;}
    void setSEUIL(int s){SEUIL=s;}

    bool isIDUnique(int ID);
    bool isValidDate(const QString& date);
    bool isValidType(const QString& type);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int ID, QString field, QString newValue);
    QSqlQueryModel* chercher(int ID);

    QSqlQueryModel* afficherPresExpiration();






};

#endif // MATIERES_PREMIERES_H

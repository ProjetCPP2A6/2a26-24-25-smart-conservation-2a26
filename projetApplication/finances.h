#ifndef FINANCES_H
#define FINANCES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Finance
{
    QString date;
    QString id;
    double montant;

public:
    Finance(){}
    Finance(int,float,QString);
    Finance(QString,float,QString);
    //getters
    QString getDate(){return date;}
    QString getid(){return id;}
    float getmontant(){return montant;}
    //setters
    void setDate(QString d){date=d;}
    void setid(QString id){this->id=id;}
    void setmontant(float m){montant=m;}
    //fnct de base
    bool ajouter();
    QSqlQueryModel * afficher();
        QSqlQueryModel * rechercher(const QString &aux);
    bool supprimer(int);
    Finance rechercherFin(QString cin);
    QSqlQueryModel* trier(const QString& critere);

};

#endif // FINANCE_H

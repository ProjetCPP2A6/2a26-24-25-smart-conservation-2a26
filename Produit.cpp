#include "Produit.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>

Produit::Produit()
{
ID_PRODUIT=0;
NOM_PRODUIT="";
ETAT="";
QTE=0;
}
Produit::Produit(int ID_PRODUIT, QString NOM_PRODUIT, QString ETAT ,QDateTime DATE_PEREMPTION,int QTE)
{
this->ID_PRODUIT=ID_PRODUIT;
    this->NOM_PRODUIT=NOM_PRODUIT;
this->ETAT=ETAT;
this ->DATE_PEREMPTION=DATE_PEREMPTION;
    this -> QTE=QTE;
}

bool Produit::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(ID_PRODUIT);

    query.prepare("insert into PRODUITS (ID_PRODUIT,NOM_PRODUIT,ETAT,DATE_PEREMPTION,QTE)""values(:ID_PRODUIT,:NOM_PRODUIT,:ETAT,:DATE_PEREMPTION,:QTE)");
    query.bindValue(":ID_PRODUIT", ID_PRODUIT);

            query.bindValue(":NOM_PRODUIT", NOM_PRODUIT);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":DATE_PEREMPTION", DATE_PEREMPTION);
    query.bindValue(":QTE", QTE);

return query.exec();
}


bool Produit::supprimer(QString ID_PRODUIT)
{
QSqlQuery query;

query.prepare("Delete from PRODUITS where ID_PRODUIT=:ID_PRODUIT");
query.bindValue(":ID_PRODUIT",ID_PRODUIT);
return query.exec();
}
bool Produit::modifier()
{

    QSqlQuery query;
    QString res=QString::number(ID_PRODUIT);
          query.prepare("UPDATE PRODUITS "" SET ID_PRODUIT=:ID_PRODUIT,NOM_PRODUIT=:NOM_PRODUIT,  ETAT=:ETAT,DATE_PEREMPTION=:DATE_PEREMPTION, QTE=:QTE  where ID_PRODUIT='"+res+"' ");


          query.bindValue(":ID_PRODUIT", res);
          query.bindValue(":NOM_PRODUIT", NOM_PRODUIT);
          query.bindValue(":ETAT", ETAT);

            query.bindValue(":DATE_PEREMPTION", DATE_PEREMPTION);
             query.bindValue(":QTE", QTE);
        return    query.exec();
}

void Produit::afficher(Ui::MainWindow *ui)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from PRODUITS");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
    modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
     modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));

    ui->tableView->setModel(modal);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

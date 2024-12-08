#include "Cuisson.h"


Cuisson::Cuisson()
{
ID_CUISSON=0;
ID_PRODUIT=0;
QTE=0;
ETAT="";
}
Cuisson::Cuisson(int ID_CUISSON, int ID_PRODUIT, QDateTime TIME ,int QTE,QString ETAT)
{
this->ID_CUISSON=ID_CUISSON;
    this->ID_PRODUIT=ID_PRODUIT;
this->TIME=TIME;
this ->QTE=QTE;
    this ->ETAT=ETAT;
}

bool Cuisson::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into Cuissons (ID_Cuisson,ID_PRODUIT,TIME,QTE,ETAT)""values(:ID_Cuisson,:ID_PRODUIT,:TIME,:QTE,:ETAT)");
    query.bindValue(":ID_Cuisson", ID_CUISSON);
            query.bindValue(":ID_PRODUIT", ID_PRODUIT);
    query.bindValue(":TIME", TIME);
    query.bindValue(":QTE", QTE);
    query.bindValue(":ETAT", ETAT);

return query.exec();
}


bool Cuisson::supprimer(QString ID_CUISSON)
{
QSqlQuery query;

query.prepare("Delete from Cuissons where ID_CUISSON=:ID_CUISSON");
query.bindValue(":ID_CUISSON",ID_CUISSON);
return query.exec();
}
bool Cuisson::modifier()
{

    QSqlQuery query;
    QString res=QString::number(ID_CUISSON);
          query.prepare("UPDATE Cuissons "" SET ID_CUISSON=:ID_CUISSON,ID_PRODUIT=:ID_PRODUIT,  TIME=:TIME,QTE=:QTE,ETAT=:ETAT  where ID_CUISSON='"+res+"' ");


          query.bindValue(":ID_CUISSON", res);
          query.bindValue(":ID_PRODUIT", ID_PRODUIT);
          query.bindValue(":TIME", TIME);

            query.bindValue(":QTE", QTE);
             query.bindValue(":ETAT", ETAT);
        return    query.exec();
}

void Cuisson::afficher(Ui::MainWindow *ui)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from Cuissons");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CUISSON"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("TIME"));
modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
    ui->tableView_2->setModel(modal);

    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}



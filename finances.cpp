#include "finances.h"



Finance::Finance(QString id,float montant,QString date)
{
    this->id=id;
    this->montant=montant;
    this->date=date;

}


bool Finance::ajouter()
{
    QSqlQuery query;
    QString res =id;
    query.prepare("INSERT INTO factures (id_facture, montant, datee) "
                  "VALUES (:id, :montant, TO_DATE(:date, 'DD/MM/YYYY'))");

    query.bindValue(":id", res); // Ensure you bind the id
    query.bindValue(":montant", montant); // Fix typo "motant" to "montant"
    query.bindValue(":date", date);


    return query.exec();

}


QSqlQueryModel * Finance::afficher(){
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT id_facture, TO_CHAR(montant, 'FM9999999990.00') AS montant, datee FROM factures");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("montant"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("date"));

   return model;


}



QSqlQueryModel * Finance::rechercher(const QString &aux){
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select id_facture, TO_CHAR(montant, 'FM9999999990.00') AS montant, datee  from factures where ((ID_FACTURE || MONTANT || DATEE ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));


    return model;

}
bool Finance::supprimer(int id) {
   QSqlQuery query;
   QString res=QString::number(id);
   query.prepare("delete from factures where ID_FACTURE= :id");
   query.bindValue(":id",res);
   return query.exec();



}



Finance Finance::rechercherFin(QString cin)
{
    Finance E;
    QSqlQuery query;
    query.prepare("SELECT * FROM factures WHERE ID_FACTURE = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        // If a record is found, populate the Finance object
        QString ID = query.value(0).toString();
        QString Montant = query.value(1).toString();
        QString Date = query.value(2).toString();

        E.setid(ID);
        E.setmontant(Montant.toFloat());
        E.setDate(Date);
    } else {
        // Return a default Finance object if no record is found
        E.setid("0"); // Indicate no record found
    }

    return E;
}



QSqlQueryModel* Finance::trier(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr;

    if (critere == "ID") {

        queryStr = "SELECT id_facture, montant, datee FROM factures ORDER BY CAST(id_facture AS INTEGER) ASC";
    } else if (critere == "Montant") {

        queryStr = "SELECT id_facture, montant, datee FROM factures ORDER BY CAST(montant AS DOUBLE PRECISION) ASC";
    } else if (critere == "Date") {

        queryStr = "SELECT id_facture, montant, datee FROM factures ORDER BY datee ASC";
    } else {

        queryStr = "SELECT id_facture, montant, datee FROM factures";
    }


    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

    return model;
}

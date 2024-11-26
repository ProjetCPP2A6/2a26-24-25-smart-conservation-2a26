#include "ravitaillements.h"
#include <QString>
#include <QSqlQuery>

Ravitaillements::Ravitaillements() {}

Ravitaillements::Ravitaillements(int ID_RAVI , QString DATE_RAVITAILLEMENT)
{
    this->ID_RAVI=ID_RAVI;
    this->DATE_RAVITAILLEMENT=DATE_RAVITAILLEMENT;
}
bool Ravitaillements::isIDUnique(int ID_RAVI)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ravitaillements WHERE ID_RAVI = :ID_RAVI");
    query.bindValue(":ID_RAVI", ID_RAVI);

    if (query.exec()) {
        query.next();
        return query.value(0).toInt() == 0;
    }
    return false;
}
bool Ravitaillements::ajouter_ravi()
{
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Erreur : La base de données n'est pas connectée.";
        return false;
    }

    QSqlQuery query;
    QString r=QString::number (ID_RAVI);
    query.prepare("insert into ravitaillements(ID_RAVI,DATE_RAVITAILLEMENT)""values(:ID_RAVI , :DATE_RAVITAILLEMENT)");

    query.bindValue(":ID_RAVI",r);
    query.bindValue(":DATE_RAVITAILLEMENT",DATE_RAVITAILLEMENT);

    return query.exec();

}

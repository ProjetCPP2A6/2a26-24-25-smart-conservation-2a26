#include "matieres_premieres.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QDebug>
#include <QSqlError>

Matieres_premieres::Matieres_premieres()
{
    TYPE="";
    ID=0;
    EXPIRYDATE="";
    QUANTITE=0;
    SEUIL=0;
}
Matieres_premieres::Matieres_premieres(QString TYPE ,int ID,QString EXPIRYDATE,int SEUIL)
{
    this->TYPE=TYPE;
    this->ID=ID;
    this->EXPIRYDATE=EXPIRYDATE;
    QUANTITE=0;
    this->SEUIL=SEUIL;

}

bool Matieres_premieres::isIDUnique(int ID)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM matieres_premieres WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (query.exec()) {
        query.next();
        return query.value(0).toInt() == 0;
    }
    return false;
}

bool Matieres_premieres::isValidDate(const QString& dateString) {

    QRegularExpression regex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!regex.match(dateString).hasMatch())
    {
        return false;
    }

    // Convertir en QDate pour vérifier si la date est valide
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");
    return date.isValid();
}

bool Matieres_premieres::isValidType(const QString& type)
{
    QRegularExpression regex("^[a-zA-Z]+$");
    return regex.match(type).hasMatch();
}


bool Matieres_premieres::ajouter()
{
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Erreur : La base de données n'est pas connectée.";
        return false;
    }

    QSqlQuery query;
    QString res=QString::number (ID);
    query.prepare("insert into matieres_premieres(TYPE,ID,EXPIRYDATE,QUANTITE,SEUIL)""values(:TYPE, :ID, :EXPIRYDATE, :QUANTITE,:SEUIL)");

    query.bindValue(":ID",res);
    query.bindValue(":TYPE",TYPE);
    query.bindValue(":EXPIRYDATE",EXPIRYDATE);
    query.bindValue(":QUANTITE",QUANTITE);
    query.bindValue(":SEUIL",SEUIL);

    return query.exec();

}
bool Matieres_premieres::supprimer(int ID)
{
    QSqlQuery query;
    QString res=QString::number(ID);
    query.prepare("Delete from matieres_premieres where ID=:ID");
    query.bindValue(":ID",res);

    return query.exec();
}
QSqlQueryModel * Matieres_premieres::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from matieres_premieres");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("EXPIRYDATE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("QUANTITY"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MINIMUM QUANTITY"));

    return model;

}

bool Matieres_premieres::modifier(int ID, QString field, QString newValue   )
{
    QSqlQuery query;
    QString fieldName;
    QString res=QString::number(ID);
    QString l=QString::number(SEUIL);

    if (field == "ID") {
        fieldName = "ID";
    } else if (field == "TYPE") {
        fieldName = "TYPE";
    } else if (field == "EXPIRYDATE") {
        fieldName = "EXPIRYDATE";
    }else if (field=="SEUIL"){
        fieldName="SEUIL";
    }

    query.prepare(QString("UPDATE matieres_premieres SET %1 = :value WHERE ID = :ID").arg(fieldName));
    query.bindValue(":ID", res);
    query.bindValue(":SEUIL",l);
    query.bindValue(":value", newValue);
    return query.exec();
}

QSqlQueryModel* Matieres_premieres::chercher(int ID)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;


    query.prepare("SELECT * FROM matieres_premieres WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("EXPIRYDATE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEUIL"));

    }

    return model;
}


QSqlQueryModel* Matieres_premieres::afficherPresExpiration()
{
    QSqlQueryModel* model1 = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM matieres_premieres WHERE TO_DATE(EXPIRYDATE, 'DD/MM/YYYY') <= TO_DATE(:threeDaysAfter, 'YYYY-MM-DD') AND TO_DATE(EXPIRYDATE, 'DD/MM/YYYY') >= TO_DATE(:currentDate, 'YYYY-MM-DD')");

    QDate currentDate = QDate::currentDate();
    QDate threeDaysAfter = currentDate.addDays(3);

    query.bindValue(":currentDate", currentDate.toString("yyyy-MM-dd"));  // Utilisation du format 'yyyy-MM-dd' pour la comparaison
    query.bindValue(":threeDaysAfter", threeDaysAfter.toString("yyyy-MM-dd"));

    query.exec();
    model1->setQuery(query);
    return model1;
}







QList<QPair<QString, int>> Matieres_premieres::getStocksDisponibles()
{
    QList<std::pair<QString, int>> stocks;
    QSqlQuery query;

    query.prepare("SELECT TYPE, QUANTITE  FROM matieres_premieres WHERE QUANTITE > 0");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des stocks : " << query.lastError().text();
    } else {
        while (query.next()) {
            QString type = query.value(0).toString();
            int quantite = query.value(1).toInt();
            qDebug() << "Matière : " << TYPE << "Quantité : " << QUANTITE;  // Ajoutez ceci pour vérifier les données
            stocks.append(qMakePair(TYPE, QUANTITE));
        }
    }

    return stocks;
}




















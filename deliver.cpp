#include "deliver.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

deliver::deliver(int id, const QString& address, int clientId, const QString& status, int commandId)
    : id_L(id), address(address), clientId(clientId), status(status), commandId(commandId) {}

QSqlQueryModel* deliver::rechercher(int id_L)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM LIVRAISON WHERE ID_L = :id_L");
    query.bindValue(":id_L", id_L);

    if (!query.exec()) {
        qDebug() << "Search query failed: " << query.lastError().text();
        return nullptr;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

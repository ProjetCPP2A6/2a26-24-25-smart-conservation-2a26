#ifndef DELIVER_H
#define DELIVER_H

#include <QSqlQueryModel>

class deliver
{
public:
    deliver(int id = 0, const QString& address = "", int clientId = 0, const QString& status = "", int commandId = 0);
    QSqlQueryModel* rechercher(int id_L);
    // Other functions for your custom operations like insert, delete, etc.

private:
    int id_L;
    QString address;
    int clientId;
    QString status;
    int commandId;
};

#endif // DELIVER_H

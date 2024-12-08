#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    db =QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projetcpp2a26");
    db.setUserName("youssef");
    db.setPassword("oracle");

    if (db.open())
        test=true;





    return  test;
}
void Connection::closeConnection(){ db.close(); }

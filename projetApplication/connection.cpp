#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("application");//inserer le nom de la source de données
    db.setUserName("mahdii");//inserer nom de l'utilisateur
    db.setPassword("azerty1230");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}

void Connection::closeConnection(){db.close();}

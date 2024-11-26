#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projet_cpp");//inserer le nom de la source de données
    db.setUserName("projetcpp2a26");//inserer nom de l'utilisateur
    db.setPassword("mp2a26");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}

void Connection::closeConnection(){db.close();}

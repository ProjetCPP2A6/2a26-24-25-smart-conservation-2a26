#include "ravi_ing.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardItem>

Ravi_ing::Ravi_ing() {}

Ravi_ing::Ravi_ing(int ID_RAVI, int ID ,float QUANTITE_AJOUTEE )
{
    this->ID_RAVI = ID_RAVI;
    this->ID=ID;
    this->QUANTITE_AJOUTEE=QUANTITE_AJOUTEE;
}


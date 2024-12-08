#ifndef RAVI_ING_H
#define RAVI_ING_H

#include <QString>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QTableView>

class Ravi_ing {
private:
    int ID_RAVI;
    int ID;
    float QUANTITE_AJOUTEE;


public:
    Ravi_ing();
    Ravi_ing(int ID_RAVI, int ID , float QUANTITE_AJOUTEE);


};

#endif // RAVI_ING_H

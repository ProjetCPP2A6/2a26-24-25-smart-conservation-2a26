#ifndef RAVITAILLEMENTS_H
#define RAVITAILLEMENTS_H
#include <QString>

class Ravitaillements
{
    int ID_RAVI;
    QString DATE_RAVITAILLEMENT;

public:
    Ravitaillements();
    Ravitaillements(int , QString);

    int getID_RAVI(){return ID_RAVI;}
    QString getDATE_RAVITAILLEMENT(){return DATE_RAVITAILLEMENT;}

    void setID_RAVI(int ID_RAVI){this->ID_RAVI=ID_RAVI;}
    void setDATE_RAVITAILLEMENT(QString date){DATE_RAVITAILLEMENT=date;}

    bool ajouter_ravi();
    bool isIDUnique(int ID_RAVI);



};

#endif // RAVITAILLEMENTS_H

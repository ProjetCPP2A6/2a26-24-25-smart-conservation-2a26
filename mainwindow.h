#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produits.h"
#include "commandes.h"

#include <QMainWindow>
#include<QSqlQueryModel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlQueryModel *modelProduits;
    /*void OpenPdf();*/




private slots:

    void on_pushButton_2_clicked();
    void on_load_clicked();
    void on_add_clicked();
    void on_ADD_3_clicked();
    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
    Commandes C;
    Produits P;
    Produits Etmp;

};
#endif // MAINWINDOW_H


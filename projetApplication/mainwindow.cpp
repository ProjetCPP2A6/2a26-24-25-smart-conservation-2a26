#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commandes.h"
#include <QMessageBox>
#include<QSqlQueryModel>
#include <produits.h>
#include<QString>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDesktopServices>
#include <QStandardItem>
#include <QSqlError>
#include <QSqlRecord>



MainWindow::~MainWindow()
{
    delete ui;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->add,&QPushButton::clicked,this,&MainWindow::on_add_clicked);
    //connect(ui->ADD_3,&QPushButton::clicked,this,&MainWindow::on_ADD_3_clicked);
}

void MainWindow ::on_add_clicked()
{
        int ID_COMMANDE = ui->lineEdit_10->text().toInt();
        QString NOM_CLIENT = ui->saisir13->text();
        QString METHOD_PAIEMENT = ui->saisir12->text();
        QString DATE_COMMANDE = ui->lineEdit_4->text();
        int ID_PRODUIT=ui->lineEdit_6->text().toInt();
        int QTE_PRODUITS=ui->lineEdit_14->text().toInt();


        Commandes C(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT,DATE_COMMANDE,ID_PRODUIT,QTE_PRODUITS);
        bool test = C.ajouter();
        ui->tableView_3->setModel(C.afficher());
        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Ajout effectué\n"
                                                 "Click cancel to exit."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Ajout non effectué.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

/*void MainWindow ::on_ADD_3_clicked()
{
    int ID_PRODUIT=ui->saisir9->text().toInt();
    QString NOM_PRODUIT=ui->saisir5->text();
    int QTE=ui->saisir8->text().toInt();
    QString ETAT=ui->lineEdit_2->text();
    QString DATE_PEREMPTION=ui->saisir7->text();
    float PRIX_UNITAIRE=ui->lineEdit_3->text().toFloat();
    if (NOM_PRODUIT.isEmpty() || DATE_PEREMPTION.isEmpty() || ETAT.isEmpty() || QTE <= 0 || PRIX_UNITAIRE <= 0) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs correctement.");
        return;
    }

    Produits P(ID_PRODUIT,NOM_PRODUIT,QTE,ETAT,DATE_PEREMPTION,PRIX_UNITAIRE);
    bool test=P.ajouterprod();
    if (test)
    {
        ui->tableView_2->setModel(P.afficherprod());
        ui->tableView_4->setModel(P.afficherprod());
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué\n" "Click cancel to exit."),QMessageBox::Ok);

    }    
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."),QMessageBox::Cancel);
        qDebug() << "Erreur SQL : " << P.ajouterprod();
}*/

/*float MainWindow::calculerMontantCommande()
{
    float montantTotal = 0.0;
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_4->model());
    if (!model) {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Modèle de données invalide"));
        return montantTotal;  // Retourner 0 si le modèle est invalide
    }


    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {

        float prixUnitaire = model->data(model->index(row, 2)).toFloat();
        int quantite = model->data(model->index(row, 3)).toInt();


        montantTotal += prixUnitaire * quantite;
    }
    return montantTotal;
}*/

/*float MainWindow::calculerPrixFinal(float montantTotalAvantReduction, int quantiteTotale)
{

    if (montantTotalAvantReduction > 100) {
        montantTotalAvantReduction *= 0.9f;  // Réduction de 10%
    }

    if (quantiteTotale > 4) {
        montantTotalAvantReduction *= 0.95f;  // Réduction de 5%
    }

    return montantTotalAvantReduction;
}

*/



/*void MainWindow::on_remove_2_clicked()
{
    int ID_COMMANDE=ui->lineEdit_10->text().toInt();
    bool test=Etmp.supprimer(ID_COMMANDE);
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression non effectuée\n" "Click cancel to exit."),QMessageBox::Cancel)

}
*/



/*void MainWindow::OpenPdf()
{
    QString filePath = QDir::homePath() + "/Desktop/commandes.pdf";

    QPdfWriter pdfwriter(filePath);
    pdfWriter.setPageSize(PageSize(PageSize::A4));
    QPdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter. setResolution (300);

    QTextDocument doc;
    QTextCursor cursor （&doc);

    cursor.insertText("Liste des Commandes\n", QTextCharFormat());
    cursor.insertBlock();；

    int columnCount=ui->tableView_3->model()->columnCount();
    int rowCount = ui->tableView_3->model()->rowCount() ;

    QTextTable *table = cursor. insertTable(rowtount + 1, columnCount()) ;

    for (int col = 0; col < columnCount; ++col)
    {
    QString headerText = ui->tableView_3->model()->headerData (col, Qt::Horizontal).toString();
     table->cellAt(0, col). firstCursorPosition().insertText(headerText);
    }

    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < columnCount; ++col)
            {
                QString cellText = ui->tableView->model()->data(ui->tableView->model()->index(row, col)).toString();
                table->cellAt(row + 1, col). firstCursorPosition() .insertText(cellText);
            }
    }
    doc.print （&pdfWriter）：
    MessageBox: :information(this, "Succès", "Le PDF a été généré avec succès !"):
    QDesktopServices: :openUrl(QUrl::fromLocalFile(fiLePath));

}
void MainWindow::on_trier_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT *FROM commandes ORDER BY NOM_CLIENT ASC");
    ui->tableView_3->setModel(model);
}*/

/*void MainWindow::on_pushButton_3_clicked()
{
    int ID_COMMANDE=ui->lineEdit_9->text().toInt();
    if (ID_COMMANDE==0)
    {
        QMessageBox::warning(this,"Erreur","veuillez entrer un id valide");
        return;
    }
    QSqlQueryModel* model =C.chercher(ID_COMMANDE);
    if(model->rowCount()==0)
    {
        QMessageBox::warning(this,"resultat","indisponible");

    }
    ui->tableView_3->setModel(model);
}*/
















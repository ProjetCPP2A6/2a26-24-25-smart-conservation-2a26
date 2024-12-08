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
#include <QUrl>
#include <QDir>
#include <QTemporaryFile>
#include <QTextTable>
#include <QTextTableCell>
#include"arduino.h"
#include <QThread>



MainWindow::~MainWindow()
{
    delete ui;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino=new Arduino();
    if(arduino->connect_arduino() == 0)
    {
        qDebug() << "Arduino connecté!";
    }
    else
    {
        qDebug() << "Erreur de connexion Arduino.";
    }
    arduino->write_to_arduino("20"); // Envoyer '1' pour activer le buzzer
    QThread::sleep(1); // Pause pour que le buzzer sonne 1 seconde
    arduino->write_to_arduino("0"); // Envoyer '0' pour désactiver le buzzer

    connect(ui->trier,&QPushButton::clicked,this,&MainWindow::on_trier_clicked);
    connect(ui->pdf2,&QPushButton::clicked,this,&MainWindow::OpenPdf2);

    connect(ui->add,&QPushButton::clicked,this,&MainWindow::on_add_clicked);
    connect(ui->remove_2,&QPushButton::clicked,this,&MainWindow::on_remove_2_clicked);
    ui->tableView_3->setModel(C.afficher());

    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::on_pushButton_3_clicked);
}
/*
void MainWindow::on_add_clicked()
{
    // Récupération des données entrées par l'utilisateur
    int ID_COMMANDE = ui->lineEdit_10->text().toInt();
    QString NOM_CLIENT = ui->saisir13->text();
    QString METHOD_PAIEMENT = ui->saisir12->text();
    QString DATE_COMMANDE = ui->lineEdit_4->text();
    int ID_PRODUIT = ui->lineEdit_6->text().toInt();
    int QTE_PRODUITS = ui->lineEdit_14->text().toInt();

    // Création de l'objet Commande
    Commandes C(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT, DATE_COMMANDE, ID_PRODUIT, QTE_PRODUITS);

    // Tentative d'ajout de la commande à la base de données
    bool test = C.ajouter();

    // Création d'une instance Arduino pour communiquer avec le microcontrôleur
    Arduino* arduino = new Arduino();
    if (!arduino->getserial()->isOpen()) {
        // Si l'Arduino n'est pas encore connecté, essayer de se connecter
        if (arduino->connect_arduino() == 0) {
            QMessageBox::information(this, "Connection", "Connexion à Arduino validée !");
        } else {
            // Si la connexion échoue
            QMessageBox::warning(this, "Erreur", "Connexion à Arduino échouée !");
            arduino->close_arduino();
            return; // Quitte la fonction si la connexion échoue
        }
    } else {
        // Si l'Arduino est déjà connecté
        QMessageBox::information(this, "Connection", "Arduino déjà connecté.");
    }

    // Vérification si l'ajout de la commande a réussi
    if (test) {
        // Mise à jour du modèle de la vue pour afficher les nouvelles commandes
        ui->tableView_3->setModel(C.afficher());

        // Affichage du message de succès
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Ok);

        // Envoi de la commande à Arduino (activation d'un buzzer par exemple)
        QByteArray commande = "BIPPER\n"; // Commande envoyée à Arduino
        arduino->write_to_arduino(commande);  // Envoi de la commande
        qDebug() << "Commande BIPPER envoyée à Arduino.";
    } else {
        // Si l'ajout a échoué, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    // Fermeture de la connexion à Arduino après l'exécution
    arduino->close_arduino();
}*/
/*void MainWindow::on_add_clicked()
{
    // Récupération des données entrées par l'utilisateur
    int ID_COMMANDE = ui->lineEdit_10->text().toInt();
    QString NOM_CLIENT = ui->saisir13->text();
    QString METHOD_PAIEMENT = ui->saisir12->text();
    QString DATE_COMMANDE = ui->lineEdit_4->text();
    int ID_PRODUIT = ui->lineEdit_6->text().toInt();
    int QTE_PRODUITS = ui->lineEdit_14->text().toInt();

    // Création de l'objet Commande
    Commandes C(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT, DATE_COMMANDE, ID_PRODUIT, QTE_PRODUITS);

    // Tentative d'ajout de la commande à la base de données
    bool test = C.ajouter();

    // Création d'une instance Arduino pour communiquer avec le microcontrôleur
    Arduino* arduino = new Arduino();
    if (!arduino->getserial()->isOpen()) {
        // Si l'Arduino n'est pas encore connecté, essayer de se connecter
        if (arduino->connect_arduino() == 0) {
            QMessageBox::information(this, "Connection", "Connexion à Arduino validée !");
        } else {
            // Si la connexion échoue
            QMessageBox::warning(this, "Erreur", "Connexion à Arduino échouée !");
            arduino->close_arduino();
            return; // Quitte la fonction si la connexion échoue
        }
    } else {
        // Si l'Arduino est déjà connecté
        QMessageBox::information(this, "Connection", "Arduino déjà connecté.");
    }

    // Vérification si l'ajout de la commande a réussi
    if (test) {
        // Mise à jour du modèle de la vue pour afficher les nouvelles commandes
        ui->tableView_3->setModel(C.afficher());

        // Affichage du message de succès
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Ok);

        // Envoi de la commande à Arduino pour activer le buzzer (envoi "1" pour faire bipper le buzzer)
        QByteArray commande = "1"; // Envoi de "1" pour activer le buzzer
        arduino->write_to_arduino(commande);  // Envoi de la commande
        qDebug() << "Commande '1' envoyée à Arduino pour activer le buzzer.";
    } else {
        // Si l'ajout a échoué, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    // Fermeture de la connexion à Arduino après l'exécution
    arduino->close_arduino();
}*/

#include <QMessageBox>
#include <QThread> // Inclure pour utiliser QThread::msleep

void MainWindow::on_add_clicked()
{

    int ID_COMMANDE = ui->lineEdit_10->text().toInt();
    QString NOM_CLIENT = ui->saisir13->text();
    QString METHOD_PAIEMENT = ui->saisir12->text();
    QString DATE_COMMANDE = ui->lineEdit_4->text();
    int ID_PRODUIT = ui->lineEdit_6->text().toInt();
    int QTE_PRODUITS = ui->lineEdit_14->text().toInt();


    Commandes C(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT, DATE_COMMANDE, ID_PRODUIT, QTE_PRODUITS);


    bool test = C.ajouter();

    if (test) {

        ui->tableView_3->setModel(C.afficher());


        //
        QByteArray command = QByteArray::number(QTE_PRODUITS);  // Conversion de la quantité en QByteArray
        arduino->write_to_arduino(command);
        qDebug() << "Command envoyée à Arduino pour activer le buzzer : " << command;
        //
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Cancel);

        /*arduino->write_to_arduino("1"); // Envoyer '1' pour activer le buzzer
        QThread::sleep(1); // Pause pour que le buzzer sonne 1 seconde
        arduino->write_to_arduino("0"); // Envoyer '0' pour désactiver le buzzer */

    } else {

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    // Fermeture de la connexion à Arduino après l'exécution
    //arduino->close_arduino();
    //delete arduino; // Supprimer l'objet Arduino après usage
}


void MainWindow::on_remove_2_clicked()
{
    int ID_COMMANDE=ui->lineEdit_8->text().toInt();
    bool test=C.supprimer(ID_COMMANDE);
    if (test)
    {
        ui->tableView_3->setModel(C.afficher());

        arduino->write_to_arduino("30"); // Envoyer '1' pour activer le buzzer
        QThread::sleep(1); // Pause pour que le buzzer sonne 1 seconde
        arduino->write_to_arduino("0"); // Envoyer '0' pour désactiver le buzzer

        //QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression non effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);

}
void MainWindow ::on_ADD_3_clicked()
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


void MainWindow::OpenPdf2()
{

    QString filePath = QDir::homePath() + "/Desktop/matieres_premieres.pdf";
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setResolution(300);


    QTextDocument doc;
    QTextCursor cursor(&doc);


    cursor.insertText("Liste des Commandes\n", QTextCharFormat());
    cursor.insertBlock();


    int columnCount = ui->tableView_3->model()->columnCount();
    int rowCount = ui->tableView_3->model()->rowCount();
    QTextTable *table = cursor.insertTable(rowCount + 1, columnCount);


    for (int col = 0; col < columnCount; ++col) {
        QString headerText = ui->tableView_3->model()->headerData(col, Qt::Horizontal).toString();
        table->cellAt(0, col).firstCursorPosition().insertText(headerText);
    }


    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString cellText = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, col)).toString();
            table->cellAt(row + 1, col).firstCursorPosition().insertText(cellText);
        }
    }

    doc.print(&pdfWriter);
    QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès !");

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));


}
void MainWindow::on_trier_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT *FROM commandes ORDER BY NOM_CLIENT ASC");
    ui->tableView_3->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
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
}
















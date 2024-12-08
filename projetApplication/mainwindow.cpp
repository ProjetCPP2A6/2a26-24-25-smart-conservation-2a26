#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finances.h"
#include <QMessageBox>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QTextDocument>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include<QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Tab_facture->setModel(f.afficher());

    ////arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_add_facture_btn_clicked()
{
    bool ok;

    QString id = ui->Id_facture->text();
    if (id.isEmpty()) {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("ID invalide."));
        return;
    }

    double montant = ui->Montant_Facture->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Montant invalide."));
        return;
    }

    QString date = ui->dateEditFacture->date().toString("dd/MM/yyyy");
    if (date.isEmpty()) {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Date invalide."));
        return;
    }

    Finance F(id, montant, date);

    Finance existingFacture = F.rechercherFin(id);

    if (existingFacture.getid() != "0") {
        // Update existing record
        QSqlQuery query;
        query.prepare("UPDATE factures SET montant = :montant, datee = TO_DATE(:date, 'DD/MM/YYYY') WHERE id_facture = :id");
        query.bindValue(":id", id);
        query.bindValue(":montant", montant);
        query.bindValue(":date", date);

        if (query.exec()) {
            QMessageBox::information(this, QObject::tr("Succès"), QObject::tr("Facture mise à jour avec succès."));
        } else {
            QMessageBox::critical(this, QObject::tr("Échec"), QObject::tr("Mise à jour échouée."));
        }
    } else {
        // Add a new record
        if (F.ajouter()) {
            QMessageBox::information(this, QObject::tr("Succès"), QObject::tr("Ajout effectué avec succès."));
        } else {
            QMessageBox::critical(this, QObject::tr("Échec"), QObject::tr("Ajout échoué."));
        }
    }

    ui->Tab_facture->setModel(f.afficher());
}


void MainWindow::on_Delete_facture_clicked()
{
    int id=ui->idfacture_supp->text().toInt();
    int test=f.supprimer(id);
    if (test==1)
    {         ui->Tab_facture->setModel(f.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Supression effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}


                    else if (test==2)
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                            QObject::tr("Cin n'existe pas.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

        else
                        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                    QObject::tr("Suppression non effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_searcher_facture_foredit_clicked()
{
    if (ui->Id_facture_modif->text()!="")
    {
        Finance E;
        E= E.rechercherFin(ui->Id_facture_modif->text());
        QString ID=E.getid();
        QString Montant=QString::number(E.getmontant());
        QDate Date=QDate::fromString(E.getDate(),"dd/MM/yyyy");
        ui->Id_facture->setText(ID);
        ui->Montant_Facture->setText(Montant);
        ui->dateEditFacture->setDate(Date);
         ui->Tab_facture->setModel(f.afficher());

    }
    else {

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Please don't leave Cin empty.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_Recherche_facture_2_clicked()
{
       ui->Tab_facture->setModel( f.rechercher(ui->Recherche_facture->text()));
}


void MainWindow::on_Recherche_facture_textChanged(const QString &arg1)
{
    ui->Tab_facture->setModel( f.rechercher(ui->Recherche_facture->text()));

}


void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/Youssef Boumallala/Downloads/projetApplication/projetApplication/liste.pdf");
    QPainter painter(&pdf);

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(1100,1200,"Liste Des Factures");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 15));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(100,100,7300,2600);

    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(200,3300,"ID_Facture");
    painter.drawText(1500,3300,"Montant");
    painter.drawText(3400,3300,"Date");


    QSqlQuery query;
    query.prepare("select * from FACTURES");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(3400,i,query.value(2).toString());




        i = i + 500;
    }


    int reponse = QMessageBox::Yes;
    if (reponse == QMessageBox::Yes)
    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        QIcon icon(":/icon.png"); // Ensure the path is correct and the resource is added in .qrc


        if (!icon.isNull()) {
            notifyIcon->setIcon(icon);
        } else {
            qWarning() << "Error: Icon not found or not loaded.";
        }
        notifyIcon->show();

        notifyIcon->showMessage("GESTION DES  Factures ","Liste Factures pret dans PDF",QSystemTrayIcon::Information,15000);

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}





void MainWindow::on_tabWidget_5_currentChanged(int index)
{
             ui->Tab_facture->setModel(f.afficher());
}


void MainWindow::on_comboBox_trifactures_currentTextChanged(const QString &arg1)
{
    QString critere = arg1;
    if (critere != "Aucun") {
        ui->Tab_facture->setModel(f.trier(critere));
    } else {
        ui->Tab_facture->setModel(f.afficher());  // Reset to the default display if "Aucun" is selected
    }
}


void MainWindow::on_Qr_code_btn_clicked()
{

    QModelIndex currentIndex = ui->Tab_facture->selectionModel()->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "No Selection", "Please select a facture first.");
        return;
    }


    int row = currentIndex.row();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->Tab_facture->model());


    QString idFacture = model->data(model->index(row, 0)).toString(); // ID
    QString montant = model->data(model->index(row, 1)).toString();   // Montant
    QString date = model->data(model->index(row, 2)).toString();      // Date


    QString qrText = QString("Facture ID: %1\nMontant: %2\nDate: %3")
                         .arg(idFacture)
                         .arg(montant)
                         .arg(date);


    QImage qrImage = m_generator.generateQr(qrText);


    ui->Qrcode_Label->setPixmap(QPixmap::fromImage(qrImage).scaled(ui->Qrcode_Label->size(), Qt::KeepAspectRatio));
}
QString lastScannedRFID = "";

void MainWindow::on_rfid_btn_clicked()
{
    QString id_rfid = A.read_from_arduino();
    id_rfid = id_rfid.trimmed();

    qInfo() << "rfid: " << id_rfid;


    if (id_rfid == lastScannedRFID) {

        QMessageBox::warning(this, "Carte déjà scannée", "L'ID de cette carte a déjà été scanné.");
    } else {

        ui->Id_facture->setText(id_rfid);
        lastScannedRFID = id_rfid; // Mettre à jour l'ID scanné
    }
}

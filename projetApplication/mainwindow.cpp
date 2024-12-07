#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matieres_premieres.h"
#include "commandes.h"
#include "ravitaillements.h"
#include <QMessageBox>
#include<QStandardItemModel>
#include "arduino.h"

#include <QCloseEvent>

#include <QPdfWriter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableCell>
#include <QDesktopServices>
#include <QUrl>
#include <QTemporaryFile>
#include <QDir>

#include <QTimer>
#include <QPrinter>
#include <QTextDocument>

#include <QSystemTrayIcon>
#include <QDateTime>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlRecord>
#include <QSqlError>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QGraphicsScene>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QColor>
#include <QtCharts>
#include <arduino.h>
#include <QSerialPort>
#include <QSerialPortInfo>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    serial(new QSerialPort(this))

{
    ui->setupUi(this);


/////////////Stock/////////////////////

     arduino = new Arduino();
    if (arduino->connect_arduino() == 0) {
        QMessageBox::information(this, "Connexion", "Arduino a répondu");
        // Si la connexion réussie, envoyez le message
        arduino->sendMessageToArduino("Bienvenue ");
        QTimer::singleShot(10000, this, &MainWindow::clearLCDMessage);


        /*// Lire la réponse de l'Arduino
        QByteArray response = arduino->read_from_arduino();

        if (!response.isEmpty()) {
            qDebug() << "Réponse reçue de l'Arduino:" << response;
            // Vous pouvez aussi vérifier ici si la réponse correspond à ce que vous attendez
            QMessageBox::information(this, "Connexion", "Arduino a répondu : " + response);
        } else {
            qDebug() << "Aucune réponse de l'Arduino";
            QMessageBox::warning(this, "Erreur", "Aucune réponse reçue de l'Arduino.");
        }*/
    } else {
        qDebug() << "Erreur de connexion à l'Arduino!";
        QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à l'Arduino. Vérifiez la connexion.");
    }



    afficherGraphiqueStock();

    updateNearExpiryTable();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkExpiryDates);
    timer->start(5000);  // 3600000 ms = 1 heure

    model = new QSqlTableModel(this);
    model->setTable("LIVRAISON");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select(); // Load data into the model
    ui->tableView_4->setModel(model); // Attach model to tableView

    // Set up QSqlQueryModel for search
    searchModel = new QSqlQueryModel(this);
    ui->tableView_5->setModel(searchModel);

    notificationWidget = new QWidget(this);
    notificationWidget->setStyleSheet
        (
        "background-color: #d2d4d1;"
        "color: black;"
        "border: 2px solid #ffffff;"
        "border-radius: 10px;"
        "padding: 10px;"
        "font-size: 16px;"
        "font-family: 'Verdana', sans-serif;"
        "box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.2);"
        );
    notificationWidget->setVisible(false);

    notificationLabel = new QLabel(notificationWidget);
    notificationLabel->setStyleSheet("border: none; color: black;");
    notificationLabel->setAlignment(Qt::AlignLeft);

    closeButton = new QPushButton("X", notificationWidget);
    closeButton->setStyleSheet
        (
        "background-color: transparent;"
        "border: none;"
        "font-size: 16px;"
        "color: red;"
        );
    closeButton->setFixedSize(20, 20);

    connect(closeButton, &QPushButton::clicked, [this]() {
        notificationWidget->setVisible(false);
    });


    // Layout pour la notification
    QHBoxLayout *layout = new QHBoxLayout(notificationWidget);
    layout->addWidget(notificationLabel);
    layout->addWidget(closeButton);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(2);

    notificationWidget->setLayout(layout);


    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    notificationWidget->move(screenGeometry.width() - notificationWidget->width() - 20, screenGeometry.height() - notificationWidget->height() - 20);


    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(style()->standardIcon(QStyle::SP_MessageBoxInformation));  // Icône par défaut
    trayIcon->setVisible(true);
    trayIcon->showMessage("Notification", "Votre message de notification", QSystemTrayIcon::Information, 3000);

    connect(ui->ADD, &QPushButton::clicked, this, &MainWindow::on_ADD_clicked);
    connect(ui->remove1, &QPushButton::clicked, this, &MainWindow::on_remove1_clicked);
    connect(ui->modifyB, &QPushButton::clicked, this, &MainWindow::on_modifyB_clicked);
    connect(ui->searchB, &QPushButton::clicked, this, &MainWindow::on_searchB_clicked);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::on_refresh_clicked);
    connect(ui->PDF, &QPushButton::clicked, this, &MainWindow::OpenPdf);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_tri_clicked);

    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    connect(ui->save1, &QPushButton::clicked, this, &MainWindow::on_save1_clicked);
    connect(ui->saveravi, &QPushButton::clicked, this, &MainWindow::on_saveravi_clicked);


    ui->tableView->setModel(Mp.afficher());
    ui->tableView->setSortingEnabled(true);

//////////Commandes///////////////////////////

    connect(ui->trier,&QPushButton::clicked,this,&MainWindow::on_trier_clicked);
    connect(ui->pdf2,&QPushButton::clicked,this,&MainWindow::OpenPdf2);

    connect(ui->add,&QPushButton::clicked,this,&MainWindow::on_add_clicked);
    connect(ui->remove_2,&QPushButton::clicked,this,&MainWindow::on_remove_2_clicked);
    ui->tableView_3->setModel(C.afficherCommande());

    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::on_pushButton_3_clicked);
    connect(ui->ref,&QPushButton::clicked,this,&MainWindow::on_ref_clicked);

}
///////Commandes////////////

void MainWindow::on_add_clicked()
{

    int ID_COMMANDE = ui->lineEdit_10->text().toInt();
    QString NOM_CLIENT = ui->saisir13->text();
    QString METHOD_PAIEMENT = ui->saisir12->text();
    QString DATE_COMMANDE = ui->lineEdit_4->text();
    int ID_PRODUIT = ui->lineEdit_6->text().toInt();
    int QTE_PRODUITS = ui->lineEdit_14->text().toInt();

    if (!C.isID_COMMANDEUnique(ID_COMMANDE)) {
        QMessageBox::warning(this, "Erreur", "L'ID du commande doit être unique.", QMessageBox::Ok);
        return;
    }

    if (!C.isValidDateCommande(DATE_COMMANDE)) {
        QMessageBox::warning(this, "Erreur", "La date de commande est invalide.", QMessageBox::Ok);
        return;
    }
    Commandes C(ID_COMMANDE, NOM_CLIENT, METHOD_PAIEMENT, DATE_COMMANDE, ID_PRODUIT, QTE_PRODUITS);


    bool test = C.ajouterCommande();

    if (test) {

        ui->tableView_3->setModel(C.afficherCommande());
        /*QByteArray command = QByteArray::number(QTE_PRODUITS);  // Conversion de la quantité en QByteArray
        arduino->write_to_arduino(command);
        qDebug() << "Command envoyée à Arduino pour activer le buzzer : " << command;
        */
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
    bool test=C.supprimerCommande(ID_COMMANDE);
    if (test)
    {
        ui->tableView_3->setModel(C.afficherCommande());

        /*arduino->write_to_arduino("30"); // Envoyer '1' pour activer le buzzer
        QThread::sleep(1); // Pause pour que le buzzer sonne 1 seconde
        arduino->write_to_arduino("0"); // Envoyer '0' pour désactiver le buzzer*/

        //QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression non effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);

}
void MainWindow::on_pushButton_3_clicked()
{
    int ID_COMMANDE=ui->lineEdit_9->text().toInt();
    if (ID_COMMANDE==0)
    {
        QMessageBox::warning(this,"Erreur","veuillez entrer un id valide");
        return;
    }
    QSqlQueryModel* model =C.chercherCommande(ID_COMMANDE);
    if(model->rowCount()==0)
    {
        QMessageBox::warning(this,"resultat","indisponible");

    }
    ui->tableView_3->setModel(model);
}
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


void MainWindow::on_ref_clicked()
{
    ui->tableView_3->setModel(C.afficherCommande());
}


/////////Stock/////////
void MainWindow::clearLCDMessage()
{
    // Envoyer une commande pour effacer le message
    arduino->sendMessageToArduino("                ");  // Vider l'écran en envoyant des espaces


}
MainWindow::~MainWindow()
{
    delete ui;
    if (arduino != nullptr) {
        arduino->close_arduino();
        delete arduino;
    }
}

void MainWindow::on_ADD_clicked()
{

    int ID=ui->Id->text().toInt();
    QString TYPE=ui->type->text();
    QString EXPIRYDATE=ui->ExpiryDate->text();
    int SEUIL=ui->seuil->text().toInt();



    if (!Mp.isIDUnique(ID)) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être unique.", QMessageBox::Ok);
        return;
    }


    if (!Mp.isValidDate(EXPIRYDATE)) {
        QMessageBox::warning(this, "Erreur", "La date d'expiration est invalide.", QMessageBox::Ok);
        return;
    }
    if (!Mp.isValidType(TYPE)) {
        QMessageBox::warning(this, "Erreur de Type", "Le type doit contenir uniquement des lettres.");
        return;
    }


    Matieres_premieres M(TYPE,ID,EXPIRYDATE,SEUIL);

    bool test=M.ajouter();
    if(test)
    {
        ui->tableView->setModel(Mp.afficher());
        checkExpiryDates();
        afficherGraphiqueStock();
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr(" Not OK"),
                                 QObject::tr("Ajout non effectué\n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel);
    }
    updateNearExpiryTable();


}

void MainWindow::on_remove1_clicked()
{
    int ID=ui->lineEdit->text().toInt();
    bool test=Mp.supprimer(ID);
    if(test)
    {
        ui->tableView->setModel(Mp.afficher());
        afficherGraphiqueStock();
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr(" Not OK"),
                              QObject::tr("Suppression non effectuée\n"
                                          "Click Cancel to exit ."),QMessageBox::Cancel);
    }

}
void MainWindow::on_modifyB_clicked()
{
    int ID=ui->lineEdit_2->text().toInt();
    QString field = ui->comboBox->currentText();
    QString newValue = ui->lineEdit_3->text();
    bool test=Mp.modifier(ID,field,newValue);
    if(test)
    {
        ui->tableView->setModel(Mp.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr(" Not OK"),
                              QObject::tr("Modification non effectuée\n"
                                          "Click Cancel to exit ."),QMessageBox::Cancel);
    }
}
void MainWindow::on_searchB_clicked()
{
    int ID = ui->search->text().toInt();

    if (ID == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQueryModel* model = Mp.chercher(ID);
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Résultat", "Aucun enregistrement trouvé pour cet ID.");
    }
    ui->tableView->setModel(model);
}



void MainWindow::on_refresh_clicked()
{
    ui->tableView->setModel(Mp.afficher());
    updateNearExpiryTable();

}


void MainWindow::OpenPdf()
{

    QString filePath = QDir::homePath() + "/Desktop/matieres_premieres.pdf";
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setResolution(300);


    QTextDocument doc;
    QTextCursor cursor(&doc);


    cursor.insertText("Liste des Matières Premières\n", QTextCharFormat());
    cursor.insertBlock();


    int columnCount = ui->tableView->model()->columnCount();
    int rowCount = ui->tableView->model()->rowCount();
    QTextTable *table = cursor.insertTable(rowCount + 1, columnCount);


    for (int col = 0; col < columnCount; ++col) {
        QString headerText = ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
        table->cellAt(0, col).firstCursorPosition().insertText(headerText);
    }


    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString cellText = ui->tableView->model()->data(ui->tableView->model()->index(row, col)).toString();
            table->cellAt(row + 1, col).firstCursorPosition().insertText(cellText);
        }
    }

    doc.print(&pdfWriter);
    QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès !");

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::on_tri_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM matieres_premieres ORDER BY TYPE ASC");
    ui->tableView->setModel(model);
}







void MainWindow::checkExpiryDates()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM matieres_premieres");
    if (query.exec())
    {
        while (query.next())
        {
            QString expiryDateStr = query.value("EXPIRYDATE").toString();
            QDate expiryDate = QDate::fromString(expiryDateStr, "dd/MM/yyyy");
            if (expiryDate.isValid()) {

                int daysToExpiry = QDate::currentDate().daysTo(expiryDate);
                if (daysToExpiry <= 3 && daysToExpiry >= 0)
                {

                    QString message = QString(" %1 will expire in %2 day(s).")
                                          .arg(query.value("TYPE").toString())
                                          .arg(daysToExpiry);


                    arduino->sendMessageToArduino(message);  // Envoyer le message à l'Arduino

                    // Attendre 3 secondes avant d'effacer le message
                    QTimer::singleShot(3000, [this]() {
                        arduino->sendMessageToArduino("     ");
                    });
                    showNotification(message);

                }
            }
        }

    }
    updateNearExpiryTable();



}


void MainWindow::showNotification(const QString &message)
{
    notificationLabel->setText(message);
    notificationWidget->adjustSize();
    notificationWidget->setVisible(true);

    QRect windowGeometry = this->geometry();
    int xPos = windowGeometry.width() - notificationWidget->width() - 20;
    int yPos = windowGeometry.height() - notificationWidget->height() - 20;
    notificationWidget->move(xPos, yPos);


    QTimer::singleShot(5000, this, [this]() {
        if (notificationWidget->isVisible()) {
            notificationWidget->setVisible(false);
        }
    });
}

void MainWindow::updateNearExpiryTable()
{
    ui->tableView_2->setModel(Mp.afficherPresExpiration());
}




//RAVITAILLEMENTS

void MainWindow::on_pushButton_6_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT ID, TYPE, EXPIRYDATE, QUANTITE FROM matieres_premieres");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors du chargement des matières premières : " + query.lastError().text());
        return;
    }

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"ID", "Type", "Expiry date", "Quantity in the stock", "Quantity to add"});

    while (query.next())
    {
        QList<QStandardItem*> row;
        for (int i = 0; i < query.record().count(); ++i)
        {
            row.append(new QStandardItem(query.value(i).toString()));
        }

        QStandardItem* quantiteAjoutee = new QStandardItem("0");
        quantiteAjoutee->setEditable(true);
        row.append(quantiteAjoutee);

        model->appendRow(row);
    }

    ui->tableView_7->setModel(model);
    ui->tableView_7->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);  // Activer l'édition
}
void MainWindow::on_save1_clicked()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_7->model());
    if (!model) return;

    int idRavi = ui->idravi->text().toInt();


    QSqlQuery query;
    query.prepare("BEGIN TRANSACTION;");  // Démarrer la transaction (si supportée par la base)

    for (int row = 0; row < model->rowCount(); ++row) {
        int idMatiere = model->item(row, 0)->text().toInt();
        float quantiteAjoutee = model->item(row, model->columnCount() - 1)->text().toFloat();


        query.prepare("INSERT INTO ravi_ing (ID_RAVI, ID, QUANTITE_AJOUTEE) "
                      "VALUES (:ID_RAVI, :ID, :QUANTITE_AJOUTEE)");
        query.bindValue(":ID_RAVI", idRavi);
        query.bindValue(":ID", idMatiere);
        query.bindValue(":QUANTITE_AJOUTEE", quantiteAjoutee);

        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'insertion dans ravi_ing : " + query.lastError().text());
            return;
        }


        query.prepare("UPDATE matieres_premieres "
                      "SET QUANTITE = QUANTITE + :QUANTITE_AJOUTEE "
                      "WHERE ID = :ID_MATIERE_PREMIERE");
        query.bindValue(":QUANTITE_AJOUTEE", quantiteAjoutee);
        query.bindValue(":ID_MATIERE_PREMIERE", idMatiere);

        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la mise à jour de la quantité dans matieres_premieres : " + query.lastError().text());
            return;
        }
    }

    query.prepare("COMMIT;");
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la validation de la transaction : " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Les ravitaillements ont été enregistrés et les stocks mis à jour avec succès.");


    on_pushButton_6_clicked();
}

void MainWindow::on_saveravi_clicked()
{

    int ID_RAVI=ui->idravi->text().toInt();
    QString DATE_RAVITAILLEMENT=ui->dateravi->text();




    if (!R.isIDUnique(ID_RAVI)) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être unique.", QMessageBox::Ok);
        return;
    }


    /*if (!R.isValidDate(DATE_RAVITAILLEMENT)) {
        QMessageBox::warning(this, "Erreur", "La date d'expiration est invalide.", QMessageBox::Ok);
        return;
    }*/

    Ravitaillements R(ID_RAVI,DATE_RAVITAILLEMENT);

    bool test=R.ajouter_ravi();
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr(" Not OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit ."),QMessageBox::Cancel);
    }

}

void MainWindow::afficherGraphiqueStock() {
    QSqlQuery query;
    query.prepare("SELECT TYPE, QUANTITE FROM matieres_premieres");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors du chargement des données : " + query.lastError().text());
        return;
    }


    QBarSeries *series = new QBarSeries();
    QStringList categories;
    QMap<QString, QColor> colorMap;

    while (query.next()) {
        QString type = query.value(0).toString();
        int quantite = query.value(1).toInt();


        QBarSet *set = new QBarSet(type);
        set->append(quantite);


        if (!colorMap.contains(type)) {
            QColor color = QColor::fromHsv(QRandomGenerator::global()->bounded(256), 200, 255);
            colorMap[type] = color;
        }
        set->setColor(colorMap[type]);

        series->append(set);
        categories.append(type);
    }


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantités disponibles par ingrédient");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(ui->graphicsView_3->size());

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);


    ui->graphicsView_3->setScene(scene);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (arduino->getserial() && arduino->getserial()->isOpen()) {
        qDebug() << "Connexion avec l'Arduino. Envoi du message 'Au revoir'.";

        arduino->sendMessageToArduino("Au revoir");

        QTimer::singleShot(3000, [this]() {
            arduino->sendMessageToArduino("     ");
        });


        event->accept();
    } else {
        qDebug() << "Le port série est fermé ou non disponible.";
        QMessageBox::critical(this, "Erreur", "Le port série est fermé ou non disponible.");
        event->accept();
    }
}
void MainWindow::on_pushButton_ajouter_clicked()
{
    int idL = ui->lineEdit_id_L->text().toInt();
    QString address = ui->lineEdit_adress_L->text();
    int clientId = ui->lineEdit_num_client->text().toInt();
    QString status = ui->listWidget_statut_L->currentItem()->text();
    int commandId = ui->lineEdit_id_commande->text().toInt();

    QSqlRecord record = model->record();
    record.setValue("ID_L", idL);
    record.setValue("ADRESS_L", address);
    record.setValue("NUM_CLIENT", clientId);
    record.setValue("STATUT_L", status);
    record.setValue("ID_COMMANDE", commandId);

    if (model->insertRecord(-1, record)) {
        QMessageBox::information(this, "Success", "Delivery added successfully.");
        model->select();

        ui->lineEdit_id_L->clear();
        ui->lineEdit_adress_L->clear();
        ui->lineEdit_num_client->clear();
        ui->listWidget_statut_L->clearSelection();
        ui->lineEdit_id_commande->clear();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add delivery: " + model->lastError().text());
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QModelIndex currentIndex = ui->tableView_4->currentIndex();
    if (currentIndex.isValid()) {
        model->removeRow(currentIndex.row());
        if (model->submitAll()) {
            QMessageBox::information(this, "Success", "Delivery deleted successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete delivery: " + model->lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No record selected.");
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    if (model->submitAll()) {

        QMessageBox::information(this, "Success", "Changes saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save changes: " + model->lastError().text());
    }
}

void MainWindow::on_pushButton_rechercher_clicked()
{
    QString searchText = ui->lineEdit_id_search->text();
    if (searchText.isEmpty()) {
        searchModel->setQuery("SELECT * FROM LIVRAISON");
    } else {
        QSqlQuery query;
        query.prepare("SELECT * FROM LIVRAISON WHERE ID_L LIKE :searchText");
        query.bindValue(":searchText", "%" + searchText + "%");
        if (query.exec()) {
            searchModel->setQuery(query);
        } else {
            QMessageBox::critical(this, "Error", "Search failed: " + query.lastError().text());
        }
    }
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("Livraison.pdf");
    QTextDocument doc;

    // Updated HTML to include NOTE and FEEDBACK
    QString html = "<h1 align='center'>Liste des Livraisons</h1>"
                   "<table border='1'>"
                   "<tr><th>ID</th><th>Adresse</th><th>Num Client</th><th>Statut</th><th>ID Commande</th><th>Note</th><th>Feedback</th></tr>";

    // Query updated to select NOTE and FEEDBACK
    QSqlQuery query("SELECT ID_L, ADRESS_L, NUM_CLIENT, STATUT_L, ID_COMMANDE, NOTE, FEEDBACK FROM LIVRAISON");
    while (query.next()) {
        html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td><td>%7</td></tr>")
        .arg(query.value(0).toInt())   // ID_L
            .arg(query.value(1).toString()) // ADRESS_L
            .arg(query.value(2).toInt())   // NUM_CLIENT
            .arg(query.value(3).toString()) // STATUT_L
            .arg(query.value(4).toInt())   // ID_COMMANDE
            .arg(query.value(5).toString()) // NOTE
            .arg(query.value(6).toString()); // FEEDBACK
    }
    html += "</table>";
    doc.setHtml(html);

    // Print to PDF
    doc.print(&printer);
    QMessageBox::information(this, "Success", "PDF generated successfully.");
}


void MainWindow::on_pushButton_status_clicked()
{
    QString deliveryId = ui->lineEdit_id_status->text();
    if (deliveryId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter a delivery ID.");
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT STATUT_L FROM LIVRAISON WHERE ID_L = :id");
    query.bindValue(":id", deliveryId);
    if (query.exec() && query.next()) {
        QString status = query.value(0).toString();
        char command;
        if (status == "in storage") {
            ui->progressBar->setValue(0);
            ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color: gray; }");
            ui->label_5->setText("in storage");

            arduino->write_to_arduino("0");
        } else if (status == "on the way") {
            ui->progressBar->setValue(50);
            ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color: yellow; }");
            ui->label_5->setText("on the way");

            arduino->write_to_arduino("1");
        } else if (status == "delivered") {
            ui->progressBar->setValue(100);
            ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color: green; }");
            ui->label_5->setText("delivered");

            arduino->write_to_arduino("2");
        } else if (status == "canceled") {
            ui->progressBar->setValue(100);
            ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color: red; }");
            ui->label_5->setText("canceled");

            arduino->write_to_arduino("3");
        } else {
            QMessageBox::warning(this, "Error", "Unknown status.");
            ui->label_5->setText("Unknown");

            arduino->write_to_arduino("4");
        }


    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch status: " + query.lastError().text());
    }
}



void MainWindow::on_pushButton_feedback_clicked()
{    QString deliveryId = ui->lineEdit_id_feedback->text();
    QString note = ui->lineEdit_note->text();

    if (deliveryId.isEmpty() || note.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in both Delivery ID and Note.");
        return;
    }

    // Determine feedback based on which checkbox is checked
    QString feedback;
    if (ui->checkBox->isChecked()) {  // sad face checkbox
        feedback = "bad";
    } else if (ui->checkBox_2->isChecked()) {  // normal face checkbox
        feedback = "medium";
    } else if (ui->checkBox_3->isChecked()) {  // happy face checkbox
        feedback = "good";
    } else {
        QMessageBox::warning(this, "Error", "Please select a feedback face.");
        return;
    }

    // Debug: print values to check if they are correct
    qDebug() << "Delivery ID: " << deliveryId;
    qDebug() << "Note: " << note;
    qDebug() << "Feedback: " << feedback;

    // Prepare SQL query to update note and feedback
    QSqlQuery query;
    query.prepare("UPDATE LIVRAISON SET NOTE = :note, FEEDBACK = :feedback WHERE ID_L = :id");
    query.bindValue(":note", note);
    query.bindValue(":feedback", feedback);
    query.bindValue(":id", deliveryId);

    // Check if the database is open
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    // Execute the query and check for errors
    if (query.exec()) {
        QMessageBox::information(this, "Success", "Feedback and note added successfully.");
        model->select();
    } else {
        qDebug() << "SQL Error: " << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to add feedback and note: " + query.lastError().text());
    }

    // Clear input fields after saving
    ui->lineEdit_id_feedback->clear();
    ui->lineEdit_note->clear();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);

}

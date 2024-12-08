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
    ui->frame_18->setVisible(false);

    ui->frame_19->setVisible(false);
    ui->frame_20->setVisible(false);
    ui->frame_21->setVisible(false);
ui->frame_22->setVisible(false);
ui->frame_23->setVisible(false);

/////////////Stock/////////////////////
///


//     arduino = new Arduino();
    int ret=A.connect_arduino(); // lancer la connexion à arduino

    if (ret==0){
        QMessageBox::information(this, "Connexion", "Arduino a répondu");
        // Si la connexion réussie, envoyez le message
//Ken theb trajaaha nahi commentaire A.sendtoarduino
        //  A.sendMessageToArduino("Bienvenue ");
        QTimer::singleShot(10000, this, &MainWindow::clearLCDMessage);


       // / Lire la réponse de l'Arduino
        QByteArray response = A.read_from_arduino();

        if (!response.isEmpty()) {
            qDebug() << "Réponse reçue de l'Arduino:" << response;
            // Vous pouvez aussi vérifier ici si la réponse correspond à ce que vous attendez
            QMessageBox::information(this, "Connexion", "Arduino a répondu : " + response);
        } else {
            qDebug() << "Aucune réponse de l'Arduino";
            QMessageBox::warning(this, "Erreur", "Aucune réponse reçue de l'Arduino.");
        }
    } else {
        qDebug() << "Erreur de connexion à l'Arduino!";
        QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à l'Arduino. Vérifiez la connexion.");
    }

///////////////

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


    //YOUSSEF INTEGRATION

    ui->Tab_facture_2->setModel(f.afficher());

    ////arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


    //


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





//YOUSSEF FUNCTIONS

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

    ui->Tab_facture_2->setModel(f.afficher());
}


void MainWindow::on_Delete_facture_clicked()
{
    int id=ui->idfacture_supp_2->text().toInt();
    int test=f.supprimer(id);
    if (test==1)
    {         ui->Tab_facture_2->setModel(f.afficher());

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
        ui->Tab_facture_2->setModel(f.afficher());

    }
    else {

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Please don't leave Cin empty.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_Recherche_facture_3_clicked()
{
    ui->Tab_facture_2->setModel( f.rechercher(ui->Recherche_facture_3->text()));
}


void MainWindow::on_Recherche_facture_4_textChanged(const QString &arg1)
{
    ui->Tab_facture_2->setModel( f.rechercher(ui->Recherche_facture_3->text()));

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
    ui->Tab_facture_2->setModel(f.afficher());
}


void MainWindow::on_comboBox_trifactures_currentTextChanged(const QString &arg1)
{
    QString critere = arg1;
    if (critere != "Aucun") {
        ui->Tab_facture_2->setModel(f.trier(critere));
    } else {
        ui->Tab_facture_2->setModel(f.afficher());  // Reset to the default display if "Aucun" is selected
    }
}


void MainWindow::on_Qr_code_btn_clicked()
{

    QModelIndex currentIndex = ui->Tab_facture_2->selectionModel()->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "No Selection", "Please select a facture first.");
        return;
    }


    int row = currentIndex.row();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->Tab_facture_2->model());


    QString idFacture = model->data(model->index(row, 0)).toString(); // ID
    QString montant = model->data(model->index(row, 1)).toString();   // Montant
    QString date = model->data(model->index(row, 2)).toString();      // Date


    QString qrText = QString("Facture ID: %1\nMontant: %2\nDate: %3")
                         .arg(idFacture)
                         .arg(montant)
                         .arg(date);


    QImage qrImage = m_generator.generateQr(qrText);


    ui->Qrcode_Label_2->setPixmap(QPixmap::fromImage(qrImage).scaled(ui->Qrcode_Label_2->size(), Qt::KeepAspectRatio));
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


// /////////////////




void MainWindow::on_pushButton_9_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_6->model()->rowCount();
    const int columnCount = ui->tableView_6->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";


    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_6->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_6->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_6->isColumnHidden(column)) {
                QString data = ui->tableView_6->model()->data(ui->tableView_6->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        document->print(&printer);

        delete document;
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_5->text();

    if(text.isEmpty())
    {
         Cuisson cui;
       cui.afficher(ui);


    }
    else
    {
        qry->prepare("select * from Cuissons where ( ID_CUISSON LIKE'%"+text+"%' OR ID_PRODUIT LIKE'%"+text+"%' OR TIME LIKE'%"+text+"%' ) ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_6->setModel(modal);
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    int id =ui->le_id->text().toInt();
    int qte = ui->le_qte->text().toInt();
    QString nom = ui->le_nom->text();
    QDateTime datee = ui->le_date->dateTime();
    QString etat = ui->etat->text();

    // Reset previous error messages
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_9->clear();
    ui->label_20->clear();

    bool isValid = true;


    if (nom.isEmpty()) {
        ui->label_5->setText("Nom vide");
        isValid = false;
    }
    if (datee.isNull()) {
        ui->label_6->setText("datee vide");
        isValid = false;
    }
    if (etat.isEmpty()) {
        ui->label_9->setText("etat vide");
        isValid = false;
    }
    if (ui->le_qte->text().isEmpty()) {
        ui->label_20->setText("etat vide");
        isValid = false;
    }

    if (isValid) {
        Produit po(id, nom, etat, datee, qte);
        bool test = po.modifier();
        if (test) {
            po.afficher(ui);
        }
    }
}

void MainWindow::on_tableView_8_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tableView_8->model()->data(in).toString();

    QSqlQuery qry;
    qry.prepare("select * from PRODUITS where ID_PRODUIT='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_id->setText(qry.value(0).toString());
            ui->etat->setText(qry.value(4).toString());

            ui->le_nom->setText(qry.value(1).toString());
            ui->le_qte->setText(qry.value(2).toString());
            ui->le_date->setDateTime(qry.value(3).toDateTime());


        }
}
}

void MainWindow::on_pushButton_5_clicked()
{
    QModelIndex index=ui->tableView_8->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView_8->model()->data(in).toString();
        Produit prod;


        bool test=prod.supprimer(val);
        if (test)
        {

            prod.afficher(ui);

        }
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id =ui->le_id->text().toInt();

    int qte = ui->le_qte->text().toInt();
    QString nom = ui->le_nom->text();
    QDateTime datee = ui->le_date->dateTime();
    QString etat = ui->etat->text();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_9->clear();
    ui->label_20->clear();
    bool isValid = true;

    if (nom.isEmpty()) {
        ui->label_5->setText("Nom vide");
        isValid = false;
    }
    if (datee.isNull()) {
        ui->label_6->setText("datee vide");
        isValid = false;
    }
    if (etat.isEmpty()) {
        ui->label_9->setText("etat vide");
        isValid = false;
    }
    if (ui->le_qte->text().isEmpty()) {
        ui->label_20->setText("etat vide");
        isValid = false;
    }

    if (isValid) {
        Produit po(id, nom, etat, datee, qte);
        bool test = po.ajouter();
        if (test) {
            po.afficher(ui);
        }
    }
}








void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_7->text();

    if(text.isEmpty())
    {
         Produit prod;
       prod.afficher(ui);


    }
    else
    {
        qry->prepare("select * from PRODUITS where ( ID_PRODUIT LIKE'%"+text+"%' OR NOM_PRODUIT LIKE'%"+text+"%' OR QTE LIKE'%"+text+"%'OR DATE_PEREMPTION LIKE'%"+text+"%'OR ETAT LIKE'%"+text+"%' ) ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_8->setModel(modal);
    }
}



void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox_3->currentText();
    if (type=="Par defaut"){
        qry->prepare("select * from PRODUITS");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
        modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
         modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));
        ui->tableView_8->setModel(modal);}

        else if (type=="nom"){
            qry->prepare("select * from Produits order by NOM_PRODUIT");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
            modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
             modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));
            ui->tableView_8->setModel(modal);


        }
        else if (type=="ID_produit"){
            qry->prepare("select * from Produits order by ID_produit");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
            modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
             modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));
            ui->tableView_8->setModel(modal);


        }
    else if (type=="QTE"){
        qry->prepare("select * from Produits order by QTE ");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
        modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
         modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_PEREMPTION"));
        ui->tableView_8->setModel(modal);


    }
}

void MainWindow::on_pushButton_clicked()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_8->model()->rowCount();
    const int columnCount = ui->tableView_8->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";


    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_8->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_8->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_8->isColumnHidden(column)) {
                QString data = ui->tableView_8->model()->data(ui->tableView_8->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    qDebug() << "hello";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    document->print(&printer);

    delete document;

}


void MainWindow::on_pb_ajouter_2_clicked()
{
    //ajout lola mt3 el cuisson
    QSqlQuery qry;
    qry.prepare("SELECT QUANTITE FROM MATIERES_PREMIERES WHERE ID = :id");
    qry.bindValue(":id", ui->le_id_prod->text().toInt());
    if (qry.exec() && qry.next()) {
        int quantite = qry.value(0).toInt();
        qDebug()<<quantite;

        int requiredQuantity = ui->le_qtee->text().toInt();

        if (quantite >= requiredQuantity) {
            ui->frame_18->setVisible(true);
            ui->frame_19->setVisible(false);
        } else {
            ui->frame_18->setVisible(false);
            ui->frame_19->setVisible(true);
        }
    } else {
        // Handle the case where the query fails or returns no result

        ui->frame_18->setVisible(false);
        ui->frame_19->setVisible(true);
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    int idc =ui->le_id_2->text().toInt();

    int id_prod = ui->le_id_prod->text().toInt();
    int QTE = ui->le_qtee->text().toInt();
    QDateTime TIME = ui->le_time->dateTime();
    QString ETAT = ui->le_etatt->text();

    // Reset previous error messages
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();

    bool isValid = true;

    // Validate the input fields
    if (ui->le_id_prod->text().isEmpty()) {
        ui->label->setText("ID produit vide");
        isValid = false;
    }
    if (ui->le_qtee->text().isEmpty()) {
        ui->label_3->setText("QTE vide");
        isValid = false;
    }
    if (ui->le_time->text().isEmpty()) {
        ui->label_2->setText("TIME vide");
        isValid = false;
    }


    // Proceed with the addition if all fields are valid
    if (isValid) {
        Cuisson cui(idc,id_prod, TIME,QTE,  ETAT);

        bool test = cui.modifier();
        if (test) {
            cui.afficher(ui);
        }
    }
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox_2->currentText();
    if (type=="Par defaut"){
        qry->prepare("select * from Cuissons");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CUISSON"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("TIME"));
    modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
        ui->tableView_6->setModel(modal);}

        else if (type=="ID_CUISSON"){
            qry->prepare("select * from Cuissons order by ID_CUISSON");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CUISSON"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("TIME"));
        modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
            ui->tableView_6->setModel(modal);


        }
        else if (type=="QTE"){
            qry->prepare("select * from Cuissons order by QTE");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CUISSON"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("TIME"));
        modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
            ui->tableView_6->setModel(modal);


        }
    else if (type=="TIME"){
        qry->prepare("select * from Cuissons order by TIME ");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CUISSON"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("TIME"));
    modal->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
        ui->tableView_6->setModel(modal);


    }
}


void MainWindow::on_pushButton_7_clicked()
{
    QModelIndex index=ui->tableView_6->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView_6->model()->data(in).toString();
        Cuisson cui;

        bool test=cui.supprimer(val);
        if (test)
        {

            cui.afficher(ui);

        }
}


void MainWindow::on_tableView_6_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tableView_6->model()->data(in).toString();

    QSqlQuery qry;
    qry.prepare("select * from Cuissons where id_cuisson='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
           ui->le_id_2->setText(qry.value(0).toString());

            ui->le_id_prod->setText(qry.value(1).toString());
            ui->le_qtee->setText(qry.value(2).toString());
            ui->le_time->setDateTime(qry.value(3).toDateTime());
 ui->le_etatt->setText(qry.value(4).toString());

        }
}
}

void MainWindow::on_tableView_6_doubleClicked(const QModelIndex &index)
{
    //double click mt3 table cuisson
    QSqlQuery qry;
    qry.prepare("SELECT etat FROM CUISSONS WHERE ID_CUISSON = :id_cuisson");
    qry.bindValue(":id_cuisson", ui->le_id_2->text());
    if (qry.exec() && qry.next()) {
        QString x = qry.value(0).toString();
        if (x == "Cooling") {

            ui->frame_21->setVisible(true);
        } else {
            ui->frame_20->setVisible(true);
        }
    } else {
        qDebug() << "Error or no data found in CUISSONS for ID_CUISSON.";
    }


}

void MainWindow::on_pb_ajouter_3_clicked()
{
    //confirmation mt3 cooking lola
    int idc = ui->le_id_2->text().toInt();
    int id_prod = ui->le_id_prod->text().toInt();
    int QTE = ui->le_qtee->text().toInt();
    QDateTime TIME = ui->le_time->dateTime();
    QString ETAT = ui->le_qtee->text();

    // Reset previous error messages
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();

    bool isValid = true;

    // Validate the input fields
    if (ui->le_id_prod->text().isEmpty()) {
        ui->label->setText("ID prod vide");
        isValid = false;
    }
    if (ui->le_qtee->text().isEmpty()) {
        ui->label_3->setText("QTE vide");
        isValid = false;
    }
    if (ui->le_time->text().isEmpty()) {
        ui->label_2->setText("TIME vide");
        isValid = false;
    }

    // Proceed with the addition if all fields are valid
    if (isValid) {
        Cuisson cui(idc, id_prod, TIME, QTE, ETAT);

        bool test = cui.ajouter();
        if (test) {
            QSqlQuery qry;
            qry.prepare("SELECT QUANTITE FROM MATIERES_PREMIERES WHERE ID = :id");
            qry.bindValue(":id", id_prod);
            if (qry.exec() && qry.next()) {
                int x = qry.value(0).toInt();

                int newQuantity = x - QTE;
                if (newQuantity < 0) {
                    ui->label_4->setText("Not enough stock available.");
                    return;
                }

                QSqlQuery query;
                query.prepare("UPDATE MATIERES_PREMIERES SET QUANTITE=:QUANTITE WHERE ID=:id");
                query.bindValue(":id", id_prod);
                query.bindValue(":QUANTITE", newQuantity);
                query.exec();

                QSqlQuery query1;
                query1.prepare("UPDATE CUISSONS SET ETAT=:ETAT WHERE ID_CUISSON=:id_cuisson");
                query1.bindValue(":id_cuisson", idc);
                query1.bindValue(":ETAT", "Cooking");
                query1.exec();

                cui.afficher(ui);
                ui->frame_18->setVisible(false);
            }
        }
    }

}



void MainWindow::on_pushButton_10_clicked()
{
    //cancel

     ui->frame_18->setVisible(false);
}

void MainWindow::on_pb_ajouter_4_clicked()
{
    //confirmation mt3 cooked
    QSqlQuery query1;
          query1.prepare("UPDATE CUISSONS "" SET ETAT=:ETAT  where ID_CUISSON='"+ui->le_id_2->text()+"' ");


          query1.bindValue(":ETAT","Cooling");
          query1.exec();
          ui->frame_20->setVisible(false);
          Cuisson cui;
          cui.afficher(ui);

}

void MainWindow::on_pushButton_11_clicked()
{
    //cancel
 ui->frame_19->setVisible(false);
}

void MainWindow::on_pb_ajouter_5_clicked()
{
    //cooling
    QSqlQuery qry1;
    qry1.prepare("SELECT QTE FROM produits WHERE ID_PRODUIT = :id_produit");
    qry1.bindValue(":id_produit", ui->le_id_prod->text());
    if (qry1.exec() && qry1.next()) {
        QString x1 = qry1.value(0).toString();
        QSqlQuery query1;
        query1.prepare("UPDATE produits SET QTE = :QTE WHERE ID_PRODUIT = :id_produit");
        query1.bindValue(":QTE", x1.toInt() + ui->le_qtee->text().toInt());
        query1.bindValue(":id_produit", ui->le_id_prod->text());
        query1.exec();


    }
    ui->frame_21->setVisible(false);
    Cuisson cui;

    bool test=cui.supprimer(ui->le_id_2->text());
    if (test)
    {

        cui.afficher(ui);

    }
}

void MainWindow::on_pushButton_12_clicked()
{
    //cancel
    ui->frame_20->setVisible(false);
}

void MainWindow::on_tableView_8_doubleClicked(const QModelIndex &index)
{
    //table produit doubleclicked
    QSqlQuery qry1;

    // Prepare and bind query
    qry1.prepare("SELECT QTE FROM produits WHERE ID_PRODUIT = :id_produit");
    qry1.bindValue(":id_produit", ui->le_id->text().toInt());

    if (qry1.exec()) {
        if (qry1.next()) {
            int quantity = qry1.value(0).toInt();
            if (quantity > 0) {
                ui->frame_22->setVisible(true);
                ui->frame_23->setVisible(false);
            } else {
                ui->frame_22->setVisible(false);
                ui->frame_23->setVisible(true);
            }
        } else {
            qDebug() << "No matching record found for ID_PRODUIT = " << ui->le_id_prod->text();
            ui->frame_22->setVisible(false);
            ui->frame_23->setVisible(false);
        }
    }

}

void MainWindow::on_pb_ajouter_6_clicked()
{
    //deliever
    QSqlQuery qry1,qry2;
    qry1.prepare("SELECT * FROM produits WHERE ID_PRODUIT = :id_produit");
    qry1.bindValue(":id_produit", ui->le_id_prod->text());
    qry1.exec();
//    qry1.prepare("insert into .....");
//    qry1.exec();
    Produit prod;
    prod.supprimer(ui->le_id->text());
    prod.afficher(ui);

    ui->frame_22->setVisible(false);


}




void MainWindow::on_pushButton_4_clicked()
{
    QModelIndex index=ui->tableView_8->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView_8->model()->data(in).toString();
        Produit prod;


        bool test=prod.supprimer(val);
        if (test)
        {

            prod.afficher(ui);

        }

}

void MainWindow::on_pushButton_15_clicked()
{
    //cancel
    ui->frame_23->setVisible(false);

}

void MainWindow::on_pushButton_14_clicked()
{
    ui->frame_22->setVisible(false);

}

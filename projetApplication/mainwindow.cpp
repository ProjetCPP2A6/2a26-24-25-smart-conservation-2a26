#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matieres_premieres.h"
#include "ravitaillements.h"
#include "ravi_ing.h"
#include <QMessageBox>
#include<QStandardItemModel>

#include <QPdfWriter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableCell>
#include <QDesktopServices>
#include <QUrl>
#include <QTemporaryFile>
#include <QDir>


#include <QSystemTrayIcon>
#include <QDateTime>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QHBoxLayout>

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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    afficherGraphiqueStock();

    updateNearExpiryTable();
    // Initialiser un QTimer pour vérifier les dates d'expiration toutes les heures
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkExpiryDates);
    timer->start(5000);  // 3600000 ms = 1 heure



    // Initialisation des composants de la notification
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
    closeButton->setFixedSize(20, 20);  // Taille fixe pour s'assurer qu'il est visible

    // Connecter le bouton de fermeture
    connect(closeButton, &QPushButton::clicked, [this]() {
        notificationWidget->setVisible(false);
    });


    // Layout pour la notification
    QHBoxLayout *layout = new QHBoxLayout(notificationWidget);
    layout->addWidget(notificationLabel);  // Ajouter le label
    layout->addWidget(closeButton);        // Ajouter le bouton de fermeture
    layout->setContentsMargins(5, 5, 5, 5);  // Marges internes
    layout->setSpacing(2);  // Espacement entre le texte et le bouton

    notificationWidget->setLayout(layout); // Définir le layout pour notificationWidget


    // Positionner la notification en bas à droite
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    /*notificationLabel->move(screenGeometry.width() / 2 - notificationLabel->width() / 2, screenGeometry.height() - notificationLabel->height() - 10);*/
    notificationWidget->move(screenGeometry.width() - notificationWidget->width() - 20, screenGeometry.height() - notificationWidget->height() - 20);


    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(style()->standardIcon(QStyle::SP_MessageBoxInformation));  // Icône par défaut
    trayIcon->setVisible(true);
    trayIcon->showMessage("Notification", "Votre message de notification", QSystemTrayIcon::Information, 3000);



    //matieres_premieres

    connect(ui->ADD, &QPushButton::clicked, this, &MainWindow::on_ADD_clicked);
    connect(ui->remove1, &QPushButton::clicked, this, &MainWindow::on_remove1_clicked);
    connect(ui->modifyB, &QPushButton::clicked, this, &MainWindow::on_modifyB_clicked);
    connect(ui->searchB, &QPushButton::clicked, this, &MainWindow::on_searchB_clicked);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::on_refresh_clicked);
    connect(ui->PDF, &QPushButton::clicked, this, &MainWindow::OpenPdf);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_tri_clicked);

    //ravitaillements

    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    connect(ui->save1, &QPushButton::clicked, this, &MainWindow::on_save1_clicked);
    connect(ui->saveravi, &QPushButton::clicked, this, &MainWindow::on_saveravi_clicked);


    ui->tableView->setModel(Mp.afficher());
    ui->tableView->setSortingEnabled(true);




}

MainWindow::~MainWindow()
{
    delete ui;
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
                    QString message = QString("Warning! The raw material %1 will expire in %2 day(s).")
                                          .arg(query.value("TYPE").toString())
                                          .arg(daysToExpiry);
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
    notificationWidget->adjustSize();  // Ajuste la taille du widget à son contenu
    notificationWidget->setVisible(true);

    QRect windowGeometry = this->geometry();
    int xPos = windowGeometry.width() - notificationWidget->width() - 20;
    int yPos = windowGeometry.height() - notificationWidget->height() - 20;
    notificationWidget->move(xPos, yPos);

    // Fermer automatiquement après 5 secondes si non fermé manuellement
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

    // Démarrer une transaction pour garantir l'intégrité des données
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

        // Mettre à jour la quantité dans matieres_premieres
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

    query.prepare("COMMIT;");  // Terminer la transaction
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la validation de la transaction : " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Les ravitaillements ont été enregistrés et les stocks mis à jour avec succès.");

    // Actualiser l'affichage pour refléter les changements dans le stock
    on_pushButton_6_clicked();  // Rappeler la fonction pour recharger les matières premières et afficher les nouvelles quantités
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

    // Création d'une série pour les barres
    QBarSeries *series = new QBarSeries();
    QStringList categories; // Liste des types pour l'axe X
    QMap<QString, QColor> colorMap; // Associe chaque type à une couleur

    while (query.next()) {
        QString type = query.value(0).toString();
        int quantite = query.value(1).toInt();

        // Ajouter un ensemble de barres pour chaque type
        QBarSet *set = new QBarSet(type);
        set->append(quantite);

        // Associer une couleur unique pour chaque type
        if (!colorMap.contains(type)) {
            QColor color = QColor::fromHsv(QRandomGenerator::global()->bounded(256), 200, 255);  // Couleur aléatoire
            colorMap[type] = color;
        }
        set->setColor(colorMap[type]);

        series->append(set);
        categories.append(type);
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantités disponibles par ingrédient");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axe X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Axe Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité");
    axisY->setRange(0, 100); // Modifier la plage selon vos données
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Création d'une vue pour le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(ui->graphicsView_3->size());
    // Ajouter le QChartView dans une QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);

    // Associer la scène au QGraphicsView
    ui->graphicsView_3->setScene(scene);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "matieres_premieres.h"
#include "ravitaillements.h"
#include "commandes.h"
#include "deliver.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QStandardItemModel>

#include"arduino.h"

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
    void on_ADD_clicked();
    void on_remove1_clicked();
    void on_modifyB_clicked();
    void on_searchB_clicked();
    void on_refresh_clicked();
    void OpenPdf();
    void on_tri_clicked();
     void updateTable();

    void checkExpiryDates();
    void showNotification(const QString &message);
    void updateNearExpiryTable();

    //ravitaillements


    //ravi_ing


    void on_save1_clicked();
    void on_pushButton_6_clicked();
    void on_saveravi_clicked();


    void afficherGraphiqueStock();


    void clearLCDMessage();

    void closeEvent(QCloseEvent *event)override;

    void processAlerts(QQueue<QString>* alertQueue);

////Commandes////
    void on_add_clicked();
    void on_remove_2_clicked();
    void on_pushButton_3_clicked();
    void OpenPdf2();
    void on_trier_clicked();
    void on_ref_clicked();

private slots:
    void on_pushButton_modifier_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_PDF_clicked(); // Slot for PDF generation



    void on_pushButton_status_clicked();




    void on_pushButton_feedback_clicked();

private:
    QLabel *notificationLabel;
    QWidget *notificationWidget;
    QPushButton *closeButton;

    Ui::MainWindow *ui;
    Matieres_premieres Mp;
    Ravitaillements R;
    Arduino *arduino;

    Commandes C;

    deliver Dtmp;
    bool isDeleting = false;
    QSqlTableModel *model;
    QSqlQueryModel *searchModel; // For search results in tableView_2
    QSerialPort *serial;




};

#endif // MAINWINDOW_H

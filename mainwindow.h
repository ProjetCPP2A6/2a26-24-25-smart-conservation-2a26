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
#include "Produit.h"
#include "Cuisson.h"

#include"arduino.h"


//Youssef Libraries
#include "finances.h"
#include <QMainWindow>
#include <QrCodeGenerator.h>  // Include the QR code generator header
#include "arduino.h"

//

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
private slots:
    void on_ADD_clicked();
    void on_remove1_clicked();
    void on_modifyB_clicked();
    void on_searchB_clicked();
    void on_refresh_clicked();
    void OpenPdf();
    void on_tri_clicked();
    // void updateTable();

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

   // void processAlerts(QQueue<QString>* alertQueue);

////Commandes////
    void on_add_clicked();
    void on_remove_2_clicked();
    void on_pushButton_3_clicked();
    void OpenPdf2();
    void on_trier_clicked();
    void on_ref_clicked();


    void on_pushButton_modifier_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_PDF_clicked(); // Slot for PDF generation



    void on_pushButton_status_clicked();




    void on_pushButton_feedback_clicked();


    //Youssef functions  /////////////////////////

    void on_add_facture_btn_clicked();

    void on_Delete_facture_clicked();

    void on_searcher_facture_foredit_clicked();

    void on_Recherche_facture_3_clicked();

    void on_Recherche_facture_4_textChanged(const QString &arg1);
    void on_lineEdit_7_textChanged(const QString &arg1);
void on_comboBox_3_currentTextChanged(const QString &arg1);
    void on_PDF_clicked();

void on_tableView_6_clicked(const QModelIndex &index);
void on_tableView_6_doubleClicked(const QModelIndex &index);
void on_tableView_8_doubleClicked(const QModelIndex &index);


    void on_tabWidget_5_currentChanged(int index);

    void on_comboBox_trifactures_currentTextChanged(const QString &arg1);

    void on_Qr_code_btn_clicked();

    void on_rfid_btn_clicked();

    //   /////////////////////////


    void on_pushButton_9_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);
 void on_tableView_8_clicked(const QModelIndex &index);

    void on_pb_ajouter_clicked();
    void on_pushButton_5_clicked();


    void on_lineEdit_textChanged(const QString &arg1);


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();





    void on_pb_ajouter_2_clicked();

    void on_pushButton_8_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);


    void on_pushButton_7_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pb_ajouter_3_clicked();

    void pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pb_ajouter_4_clicked();

    void on_pushButton_11_clicked();

    void on_pb_ajouter_5_clicked();

    void on_pushButton_12_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pb_ajouter_6_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_15_clicked();

    void on_frame_23_customContextMenuRequested(const QPoint &pos);

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void on_pushButton_14_clicked();

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

    Finance f;

    QrCodeGenerator m_generator; // QR code generator object

    Arduino A;




};

#endif // MAINWINDOW_H

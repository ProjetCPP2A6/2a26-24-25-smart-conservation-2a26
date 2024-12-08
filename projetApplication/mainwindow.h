#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "finances.h"
#include <QMainWindow>
#include <QrCodeGenerator.h>  // Include the QR code generator header
#include "arduino.h"
namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_facture_btn_clicked();

    void on_Delete_facture_clicked();

    void on_searcher_facture_foredit_clicked();

    void on_Recherche_facture_2_clicked();

    void on_Recherche_facture_textChanged(const QString &arg1);

    void on_PDF_clicked();


    void on_tabWidget_5_currentChanged(int index);

    void on_comboBox_trifactures_currentTextChanged(const QString &arg1);

    void on_Qr_code_btn_clicked();

    void on_rfid_btn_clicked();

private:
    Ui::MainWindow *ui;
    Finance f;

    QrCodeGenerator m_generator; // QR code generator object

   Arduino A;


};

#endif // MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *app;
    QTabWidget *modules;
    QWidget *home;
    QWidget *account;
    QCalendarWidget *calendarWidget;
    QWidget *stock;
    QTabWidget *tabWidget;
    QWidget *newstock;
    QWidget *box1;
    QPushButton *ADD;
    QLabel *newtype;
    QLabel *idnew;
    QLabel *date;
    QLineEdit *Id;
    QLineEdit *type;
    QLineEdit *ExpiryDate;
    QLabel *NEW;
    QWidget *voirstock;
    QWidget *widget;
    QLabel *label_34;
    QLineEdit *lineEdit;
    QPushButton *remove1;
    QLineEdit *search;
    QLabel *label_35;
    QPushButton *search_3;
    QTableWidget *tableWidget_4;
    QLabel *STOCK;
    QWidget *tab;
    QLabel *refillstock;
    QWidget *widget_2;
    QPushButton *remove1_2;
    QTableWidget *tableWidget_5;
    QWidget *products;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QWidget *tab_3;
    QWidget *box1_3;
    QPushButton *ADD_3;
    QLabel *Product;
    QLabel *id2;
    QLabel *date_2;
    QLineEdit *saisir9;
    QLineEdit *saisir5;
    QLineEdit *saisir7;
    QLabel *quantity_2;
    QLineEdit *saisir8;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QWidget *tab_4;
    QWidget *box5;
    QLabel *label_36;
    QLineEdit *lineEdit_5;
    QPushButton *search_2;
    QLabel *label_51;
    QLineEdit *lineEdit_7;
    QPushButton *remove;
    QTableView *tableView_2;
    QLabel *PRODUCTS;
    QWidget *orders;
    QTabWidget *tabWidget_3;
    QWidget *newOrder;
    QWidget *box4;
    QPushButton *add;
    QWidget *widget_7;
    QLineEdit *lineEdit_10;
    QLineEdit *saisir12;
    QLineEdit *saisir13;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QLabel *paymentmethod;
    QLabel *name;
    QLabel *date_3;
    QLabel *label_9;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_14;
    QLabel *label_11;
    QLabel *neworder;
    QWidget *consultOrder;
    QWidget *widget_9;
    QTableView *tableView_3;
    QPushButton *remove_2;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLabel *label_38;
    QPushButton *pushButton_3;
    QLabel *label_37;
    QPushButton *trier;
    QWidget *delivery;
    QTabWidget *tabWidget_4;
    QWidget *tab_8;
    QWidget *box4_2;
    QLabel *nameproduct_2;
    QLabel *Price_2;
    QLabel *numberproduct_2;
    QLabel *name_2;
    QLabel *paymentmethod_2;
    QLineEdit *saisir10_2;
    QLineEdit *saisir11_2;
    QLineEdit *saisir12_2;
    QLineEdit *saisir13_2;
    QLineEdit *saisir14_2;
    QLineEdit *saisir15_2;
    QPushButton *add_2;
    QLabel *Delivery_2;
    QLabel *label_5;
    QLineEdit *lineEdit_11;
    QWidget *tab_9;
    QTableWidget *tableWidget_2;
    QLabel *label_6;
    QLineEdit *lineEdit_12;
    QPushButton *pushButton_4;
    QLabel *label_7;
    QLineEdit *lineEdit_13;
    QPushButton *pushButton_5;
    QWidget *canning;
    QWidget *finance;
    QTabWidget *tabWidget_5;
    QWidget *nvfacture;
    QWidget *widget_5;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_52;
    QPushButton *pushButton_8;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_19;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_22;
    QLabel *label_54;
    QWidget *voirfacture;
    QWidget *widget_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_21;
    QLabel *label_3;
    QLabel *label_8;
    QTableWidget *tableWidget_7;
    QLabel *label_10;
    QWidget *tab_10;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QPushButton *pushButton;
    QWidget *interfaceConnexion;
    QFrame *Box;
    QLabel *Password;
    QLineEdit *writepass;
    QPushButton *Enterbutton;
    QLabel *login;
    QLabel *Logo;
    QLabel *slogan;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(955, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("#entre\n"
"{\n"
"background-color: #2596be;\n"
"}\n"
"#frame\n"
"{\n"
"	background-color: #fefeff;\n"
"	border-radius :20px\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 961, 621));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        app = new QWidget();
        app->setObjectName("app");
        app->setStyleSheet(QString::fromUtf8("#app\n"
"{\n"
"background-color:#42b5b2;\n"
"}\n"
"#welcome\n"
"{\n"
"font: 700 17pt \"Berlin Sans FB Demi\";\n"
"}"));
        modules = new QTabWidget(app);
        modules->setObjectName("modules");
        modules->setGeometry(QRect(-6, 80, 971, 521));
        modules->setStyleSheet(QString::fromUtf8("\n"
"font: 900 9pt \"Segoe UI Black\";"));
        home = new QWidget();
        home->setObjectName("home");
        account = new QWidget(home);
        account->setObjectName("account");
        account->setGeometry(QRect(560, 10, 351, 441));
        calendarWidget = new QCalendarWidget(home);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(20, 215, 441, 261));
        modules->addTab(home, QString());
        stock = new QWidget();
        stock->setObjectName("stock");
        tabWidget = new QTabWidget(stock);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 961, 501));
        newstock = new QWidget();
        newstock->setObjectName("newstock");
        newstock->setStyleSheet(QString::fromUtf8("#NEW\n"
"{\n"
"font: 700 26pt \"Berlin Sans FB Demi\";\n"
"color:#42b5b2;\n"
"}\n"
"#tab1\n"
"{\n"
"color:#42b5b2;\n"
"}\n"
"#box1\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#type\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#Id\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#ExpiryDate\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#date\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#idnew\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#newtype\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#ADD\n"
"{\n"
"color: #42b5b2; \n"
"font: 15pt \"Berlin Sans FB\";\n"
"}\n"
"\n"
""));
        box1 = new QWidget(newstock);
        box1->setObjectName("box1");
        box1->setGeometry(QRect(230, 70, 411, 351));
        ADD = new QPushButton(box1);
        ADD->setObjectName("ADD");
        ADD->setGeometry(QRect(272, 280, 101, 29));
        newtype = new QLabel(box1);
        newtype->setObjectName("newtype");
        newtype->setGeometry(QRect(30, 40, 101, 20));
        idnew = new QLabel(box1);
        idnew->setObjectName("idnew");
        idnew->setGeometry(QRect(30, 100, 63, 20));
        date = new QLabel(box1);
        date->setObjectName("date");
        date->setGeometry(QRect(30, 160, 121, 20));
        Id = new QLineEdit(box1);
        Id->setObjectName("Id");
        Id->setGeometry(QRect(162, 100, 191, 26));
        type = new QLineEdit(box1);
        type->setObjectName("type");
        type->setGeometry(QRect(162, 40, 191, 26));
        ExpiryDate = new QLineEdit(box1);
        ExpiryDate->setObjectName("ExpiryDate");
        ExpiryDate->setGeometry(QRect(162, 160, 191, 26));
        NEW = new QLabel(newstock);
        NEW->setObjectName("NEW");
        NEW->setGeometry(QRect(390, 0, 101, 61));
        tabWidget->addTab(newstock, QString());
        voirstock = new QWidget();
        voirstock->setObjectName("voirstock");
        voirstock->setStyleSheet(QString::fromUtf8("#STOCK\n"
"{\n"
"font: 700 26pt \"Berlin Sans FB Demi\";\n"
"color:#42b5b2;\n"
"}\n"
"\n"
"#label_12\n"
"{\n"
"	color:#42b5b2;\n"
"	font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#label_15\n"
"{color:#42b5b2;\n"
"font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"\n"
"\n"
"#label_3\n"
"{color:#42b5b2;\n"
"font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#widget_2\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#widget\n"
"{background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"\n"
"}\n"
"#expirydate\n"
"{\n"
"color:#42b5b2;\n"
"	font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#id\n"
"{\n"
"color:#42b5b2;\n"
"	font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#ingredients\n"
"{\n"
"color:#42b5b2;\n"
"	font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#quantity\n"
"{\n"
"color:#42b5b2;\n"
"	font: 700 12pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#remove1\n"
"{color: #42b5b2; \n"
"font: 15pt \"Berlin Sans FB\";}\n"
""
                        "#search_5\n"
"{color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#remove2\n"
"{color: #42b5b2; \n"
"font: 15pt \"Berlin Sans FB\";\n"
"}\n"
"\n"
"#search_3\n"
"{color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"tableWidget_4 {\n"
"    background-color: #f5f5f5; \n"
"    color: #333333;          \n"
"    gridline-color: #dcdcdc;  \n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        widget = new QWidget(voirstock);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 50, 801, 381));
        label_34 = new QLabel(widget);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(472, 330, 81, 21));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(550, 330, 113, 26));
        remove1 = new QPushButton(widget);
        remove1->setObjectName("remove1");
        remove1->setGeometry(QRect(680, 330, 101, 29));
        QFont font;
        font.setFamilies({QString::fromUtf8("Berlin Sans FB")});
        font.setPointSize(15);
        font.setBold(false);
        font.setItalic(false);
        remove1->setFont(font);
        search = new QLineEdit(widget);
        search->setObjectName("search");
        search->setGeometry(QRect(190, 10, 251, 26));
        label_35 = new QLabel(widget);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(160, 10, 31, 21));
        search_3 = new QPushButton(widget);
        search_3->setObjectName("search_3");
        search_3->setGeometry(QRect(460, 10, 71, 29));
        tableWidget_4 = new QTableWidget(widget);
        if (tableWidget_4->columnCount() < 4)
            tableWidget_4->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(110, 50, 541, 261));
        tableWidget_4->setMinimumSize(QSize(431, 261));
        tableWidget_4->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #f9f9f9;\n"
"    color: #333;\n"
"    font-size: 14px;\n"
"    gridline-color: #e0e0e0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color:#8dced6 ;\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid #dddddd;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #e8f5e9;\n"
"    color: #333;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #eab676;\n"
"    color: white;\n"
"}\n"
""));
        STOCK = new QLabel(voirstock);
        STOCK->setObjectName("STOCK");
        STOCK->setGeometry(QRect(220, 0, 401, 51));
        tabWidget->addTab(voirstock, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tab->setStyleSheet(QString::fromUtf8("#refillstock\n"
"{\n"
"font: 700 26pt \"Berlin Sans FB Demi\";\n"
"color:#42b5b2;\n"
"}\n"
"#widget_2\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#remove1_2\n"
"{color: #42b5b2; \n"
"font: 15pt \"Berlin Sans FB\";\n"
"}"));
        refillstock = new QLabel(tab);
        refillstock->setObjectName("refillstock");
        refillstock->setGeometry(QRect(340, 0, 221, 41));
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(60, 50, 801, 381));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(4);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        remove1_2 = new QPushButton(widget_2);
        remove1_2->setObjectName("remove1_2");
        remove1_2->setGeometry(QRect(672, 330, 101, 29));
        tableWidget_5 = new QTableWidget(widget_2);
        if (tableWidget_5->columnCount() < 4)
            tableWidget_5->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget_5->setObjectName("tableWidget_5");
        tableWidget_5->setGeometry(QRect(120, 30, 581, 291));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(7);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(tableWidget_5->sizePolicy().hasHeightForWidth());
        tableWidget_5->setSizePolicy(sizePolicy1);
        tableWidget_5->setMinimumSize(QSize(0, 261));
        tableWidget_5->setMaximumSize(QSize(581, 16777215));
        tableWidget_5->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #f9f9f9;\n"
"    color: #333;\n"
"    font-size: 14px;\n"
"    gridline-color: #e0e0e0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color:#8dced6 ;\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid #dddddd;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #e8f5e9;\n"
"    color: #333;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #eab676;\n"
"    color: white;\n"
"}\n"
"\n"
""));
        tabWidget->addTab(tab, QString());
        modules->addTab(stock, QString());
        products = new QWidget();
        products->setObjectName("products");
        tabWidget_2 = new QTabWidget(products);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 0, 961, 491));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget_2->addTab(tab_5, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tab_3->setStyleSheet(QString::fromUtf8("\n"
"#box1_3\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#saisir7\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir5\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir8\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir9\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#date_2\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#id2\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#Product\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#ADD_3\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#quantity_2\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"\n"
""));
        box1_3 = new QWidget(tab_3);
        box1_3->setObjectName("box1_3");
        box1_3->setGeometry(QRect(250, 20, 411, 411));
        ADD_3 = new QPushButton(box1_3);
        ADD_3->setObjectName("ADD_3");
        ADD_3->setGeometry(QRect(270, 350, 93, 29));
        Product = new QLabel(box1_3);
        Product->setObjectName("Product");
        Product->setGeometry(QRect(30, 40, 131, 20));
        id2 = new QLabel(box1_3);
        id2->setObjectName("id2");
        id2->setGeometry(QRect(30, 100, 63, 20));
        date_2 = new QLabel(box1_3);
        date_2->setObjectName("date_2");
        date_2->setGeometry(QRect(30, 160, 121, 20));
        saisir9 = new QLineEdit(box1_3);
        saisir9->setObjectName("saisir9");
        saisir9->setGeometry(QRect(162, 100, 191, 26));
        saisir5 = new QLineEdit(box1_3);
        saisir5->setObjectName("saisir5");
        saisir5->setGeometry(QRect(162, 40, 191, 26));
        saisir7 = new QLineEdit(box1_3);
        saisir7->setObjectName("saisir7");
        saisir7->setGeometry(QRect(162, 160, 191, 26));
        quantity_2 = new QLabel(box1_3);
        quantity_2->setObjectName("quantity_2");
        quantity_2->setGeometry(QRect(30, 230, 101, 20));
        saisir8 = new QLineEdit(box1_3);
        saisir8->setObjectName("saisir8");
        saisir8->setGeometry(QRect(160, 230, 191, 26));
        label = new QLabel(box1_3);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 280, 63, 20));
        lineEdit_2 = new QLineEdit(box1_3);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(170, 280, 181, 26));
        lineEdit_3 = new QLineEdit(box1_3);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(180, 320, 161, 26));
        label_2 = new QLabel(box1_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 330, 63, 20));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tab_4->setStyleSheet(QString::fromUtf8("#PRODUCTS\n"
"{font: 700 26pt \"Berlin Sans FB Demi\";\n"
"color:#42b5b2;\n"
"}\n"
"\n"
"#box5\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#cansize2\n"
"{font: 700 10pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#idprod\n"
"{font: 700 10pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#quantity2\n"
"{font: 700 10pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#productdone\n"
"{font: 700 10pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#remove\n"
"{color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#search_2\n"
"{color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
""));
        box5 = new QWidget(tab_4);
        box5->setObjectName("box5");
        box5->setGeometry(QRect(140, 60, 671, 381));
        label_36 = new QLabel(box5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(100, 10, 31, 20));
        lineEdit_5 = new QLineEdit(box5);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(140, 10, 113, 26));
        search_2 = new QPushButton(box5);
        search_2->setObjectName("search_2");
        search_2->setGeometry(QRect(290, 10, 93, 29));
        label_51 = new QLabel(box5);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(160, 310, 31, 20));
        lineEdit_7 = new QLineEdit(box5);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(200, 310, 121, 26));
        remove = new QPushButton(box5);
        remove->setObjectName("remove");
        remove->setGeometry(QRect(340, 310, 93, 29));
        tableView_2 = new QTableView(box5);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(45, 71, 591, 211));
        PRODUCTS = new QLabel(tab_4);
        PRODUCTS->setObjectName("PRODUCTS");
        PRODUCTS->setGeometry(QRect(380, 0, 191, 61));
        tabWidget_2->addTab(tab_4, QString());
        modules->addTab(products, QString());
        orders = new QWidget();
        orders->setObjectName("orders");
        tabWidget_3 = new QTabWidget(orders);
        tabWidget_3->setObjectName("tabWidget_3");
        tabWidget_3->setGeometry(QRect(0, 0, 961, 491));
        newOrder = new QWidget();
        newOrder->setObjectName("newOrder");
        newOrder->setStyleSheet(QString::fromUtf8("#neworder\n"
"{\n"
"font: 700 23pt \"Berlin Sans FB Demi\";\n"
"color:#42b5b2;\n"
"}\n"
"#label_16\n"
"{font: 700 14pt \"Berlin Sans FB Demi\";\n"
"color:white;\n"
"}\n"
"#box4\n"
"{\n"
"background-color: #f0f0f0;\n"
"border: 2px solid #333;\n"
"border-radius: 10px;\n"
"}\n"
"#saisir10\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir11\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir12\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir13\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#saisir14\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#saisir15\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#name\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#Delivery\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#date_3\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#nameproduct\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#add\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#numberproduct\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#paymentmethod\n"
"{\n"
"	font: 12pt \"Berlin S"
                        "ans FB\";\n"
"}\n"
"#Price\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#label_4\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#lineEdit_10\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"\n"
"\n"
"#widget_7\n"
"{\n"
"background-color: #a0d8d1; \n"
"border: 2px solid #333; \n"
"border-radius: 10px; \n"
"padding: 10px; \n"
"}\n"
"#widget_8\n"
"{\n"
"background-color: #a0d8d1;\n"
"border: 2px solid #333; \n"
"border-radius: 10px; \n"
"padding: 10px; \n"
"}"));
        box4 = new QWidget(newOrder);
        box4->setObjectName("box4");
        box4->setGeometry(QRect(80, 10, 801, 441));
        add = new QPushButton(box4);
        add->setObjectName("add");
        add->setGeometry(QRect(672, 398, 101, 31));
        widget_7 = new QWidget(box4);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(190, 70, 401, 341));
        widget_7->setStyleSheet(QString::fromUtf8("font: 12pt \"Berlin Sans FB\";"));
        lineEdit_10 = new QLineEdit(widget_7);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(190, 40, 181, 26));
        lineEdit_10->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        saisir12 = new QLineEdit(widget_7);
        saisir12->setObjectName("saisir12");
        saisir12->setGeometry(QRect(190, 140, 181, 26));
        saisir12->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        saisir13 = new QLineEdit(widget_7);
        saisir13->setObjectName("saisir13");
        saisir13->setGeometry(QRect(190, 90, 181, 26));
        saisir13->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        lineEdit_4 = new QLineEdit(widget_7);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(190, 190, 181, 26));
        lineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        label_4 = new QLabel(widget_7);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 40, 191, 20));
        paymentmethod = new QLabel(widget_7);
        paymentmethod->setObjectName("paymentmethod");
        paymentmethod->setGeometry(QRect(10, 140, 161, 20));
        name = new QLabel(widget_7);
        name->setObjectName("name");
        name->setGeometry(QRect(10, 90, 121, 20));
        date_3 = new QLabel(widget_7);
        date_3->setObjectName("date_3");
        date_3->setGeometry(QRect(10, 190, 63, 20));
        label_9 = new QLabel(widget_7);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 240, 171, 20));
        lineEdit_6 = new QLineEdit(widget_7);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(190, 240, 181, 26));
        lineEdit_6->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        lineEdit_14 = new QLineEdit(widget_7);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(190, 290, 181, 26));
        lineEdit_14->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        label_11 = new QLabel(widget_7);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 290, 121, 20));
        neworder = new QLabel(box4);
        neworder->setObjectName("neworder");
        neworder->setGeometry(QRect(20, 20, 211, 31));
        tabWidget_3->addTab(newOrder, QString());
        consultOrder = new QWidget();
        consultOrder->setObjectName("consultOrder");
        consultOrder->setStyleSheet(QString::fromUtf8("#widget_9\n"
"{background-color: #f0f0f0;\n"
"border: 2px solid #333;\n"
"border-radius: 10px;\n"
"}\n"
"\n"
"#label_37\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#label_38\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_3\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_2\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"\n"
"\n"
""));
        widget_9 = new QWidget(consultOrder);
        widget_9->setObjectName("widget_9");
        widget_9->setGeometry(QRect(40, 20, 861, 411));
        tableView_3 = new QTableView(widget_9);
        tableView_3->setObjectName("tableView_3");
        tableView_3->setGeometry(QRect(40, 80, 771, 241));
        remove_2 = new QPushButton(widget_9);
        remove_2->setObjectName("remove_2");
        remove_2->setGeometry(QRect(740, 360, 93, 29));
        lineEdit_8 = new QLineEdit(widget_9);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(580, 360, 151, 26));
        lineEdit_8->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        lineEdit_9 = new QLineEdit(widget_9);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(420, 30, 151, 26));
        lineEdit_9->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border: 2px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #42b5b2;\n"
"}"));
        label_38 = new QLabel(widget_9);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(250, 30, 151, 20));
        pushButton_3 = new QPushButton(widget_9);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(580, 30, 93, 29));
        label_37 = new QLabel(widget_9);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(420, 360, 151, 21));
        trier = new QPushButton(widget_9);
        trier->setObjectName("trier");
        trier->setGeometry(QRect(720, 30, 93, 29));
        tabWidget_3->addTab(consultOrder, QString());
        modules->addTab(orders, QString());
        delivery = new QWidget();
        delivery->setObjectName("delivery");
        tabWidget_4 = new QTabWidget(delivery);
        tabWidget_4->setObjectName("tabWidget_4");
        tabWidget_4->setGeometry(QRect(0, 0, 961, 491));
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        tab_8->setStyleSheet(QString::fromUtf8("\n"
"#box4_2\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#saisir10_2\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir11_2\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir12_2\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#saisir13_2\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#saisir14_2\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#saisir15_2\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#name_2\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#Delivery_2\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#nameproduct_2\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#add_2\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#numberproduct_2\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#paymentmethod_2\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#Price_2\n"
"{\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#label_5\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#lineEdit_11\n"
"{border:2px solid #42b5b2;\n"
""
                        "}\n"
"\n"
"\n"
"\n"
""));
        box4_2 = new QWidget(tab_8);
        box4_2->setObjectName("box4_2");
        box4_2->setGeometry(QRect(250, 10, 441, 421));
        nameproduct_2 = new QLabel(box4_2);
        nameproduct_2->setObjectName("nameproduct_2");
        nameproduct_2->setGeometry(QRect(20, 90, 81, 20));
        Price_2 = new QLabel(box4_2);
        Price_2->setObjectName("Price_2");
        Price_2->setGeometry(QRect(20, 240, 141, 20));
        numberproduct_2 = new QLabel(box4_2);
        numberproduct_2->setObjectName("numberproduct_2");
        numberproduct_2->setGeometry(QRect(20, 40, 181, 20));
        name_2 = new QLabel(box4_2);
        name_2->setObjectName("name_2");
        name_2->setGeometry(QRect(20, 190, 121, 20));
        paymentmethod_2 = new QLabel(box4_2);
        paymentmethod_2->setObjectName("paymentmethod_2");
        paymentmethod_2->setGeometry(QRect(20, 330, 161, 20));
        saisir10_2 = new QLineEdit(box4_2);
        saisir10_2->setObjectName("saisir10_2");
        saisir10_2->setGeometry(QRect(220, 40, 181, 26));
        saisir11_2 = new QLineEdit(box4_2);
        saisir11_2->setObjectName("saisir11_2");
        saisir11_2->setGeometry(QRect(220, 90, 181, 26));
        saisir12_2 = new QLineEdit(box4_2);
        saisir12_2->setObjectName("saisir12_2");
        saisir12_2->setGeometry(QRect(220, 330, 181, 26));
        saisir13_2 = new QLineEdit(box4_2);
        saisir13_2->setObjectName("saisir13_2");
        saisir13_2->setGeometry(QRect(220, 190, 181, 26));
        saisir14_2 = new QLineEdit(box4_2);
        saisir14_2->setObjectName("saisir14_2");
        saisir14_2->setGeometry(QRect(220, 240, 181, 26));
        saisir15_2 = new QLineEdit(box4_2);
        saisir15_2->setObjectName("saisir15_2");
        saisir15_2->setGeometry(QRect(220, 290, 181, 26));
        add_2 = new QPushButton(box4_2);
        add_2->setObjectName("add_2");
        add_2->setGeometry(QRect(300, 370, 93, 29));
        Delivery_2 = new QLabel(box4_2);
        Delivery_2->setObjectName("Delivery_2");
        Delivery_2->setGeometry(QRect(20, 290, 161, 20));
        label_5 = new QLabel(box4_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 140, 191, 20));
        lineEdit_11 = new QLineEdit(box4_2);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(220, 140, 181, 26));
        tabWidget_4->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        tab_9->setStyleSheet(QString::fromUtf8("#lineEdit_8\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#lineEdit_9\n"
"{\n"
"border:2px solid #42b5b2; \n"
"}\n"
"#label_7\n"
"{\n"
"	\n"
"	font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#label_6\n"
"{font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_4\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_5\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"\n"
"\n"
""));
        tableWidget_2 = new QTableWidget(tab_9);
        if (tableWidget_2->columnCount() < 7)
            tableWidget_2->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem14);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(40, 70, 901, 281));
        tableWidget_2->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #f9f9f9;\n"
"    color: #333;\n"
"    font-size: 14px;\n"
"    gridline-color: #e0e0e0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color:#8dced6 ;\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid #dddddd;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #e8f5e9;\n"
"    color: #333;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #eab676;\n"
"    color: white;\n"
"}\n"
""));
        label_6 = new QLabel(tab_9);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(170, 30, 161, 21));
        lineEdit_12 = new QLineEdit(tab_9);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(340, 30, 113, 26));
        pushButton_4 = new QPushButton(tab_9);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(470, 30, 93, 29));
        label_7 = new QLabel(tab_9);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(410, 380, 151, 21));
        lineEdit_13 = new QLineEdit(tab_9);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(580, 380, 113, 26));
        pushButton_5 = new QPushButton(tab_9);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(710, 380, 93, 29));
        tabWidget_4->addTab(tab_9, QString());
        modules->addTab(delivery, QString());
        canning = new QWidget();
        canning->setObjectName("canning");
        modules->addTab(canning, QString());
        finance = new QWidget();
        finance->setObjectName("finance");
        tabWidget_5 = new QTabWidget(finance);
        tabWidget_5->setObjectName("tabWidget_5");
        tabWidget_5->setGeometry(QRect(0, 0, 961, 491));
        nvfacture = new QWidget();
        nvfacture->setObjectName("nvfacture");
        nvfacture->setStyleSheet(QString::fromUtf8("#lineEdit_18\n"
"{\n"
"border:2px solid #42b5b2;\n"
"}\n"
"#lineEdit_19\n"
"{border:2px solid #42b5b2;}\n"
"#lineEdit_20\n"
"{border:2px solid #42b5b2;}\n"
"#lineEdit_22\n"
"{border:2px solid #42b5b2;}\n"
"#widget_5\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#pushButton_8\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";}\n"
"#label_39\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"#label_40\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"#label_52\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"#label_54\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"\n"
""));
        widget_5 = new QWidget(nvfacture);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(260, 20, 401, 401));
        label_39 = new QLabel(widget_5);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(50, 70, 71, 20));
        label_40 = new QLabel(widget_5);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(50, 120, 81, 20));
        label_52 = new QLabel(widget_5);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(50, 170, 63, 20));
        pushButton_8 = new QPushButton(widget_5);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(240, 310, 93, 29));
        lineEdit_18 = new QLineEdit(widget_5);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(140, 70, 113, 26));
        lineEdit_19 = new QLineEdit(widget_5);
        lineEdit_19->setObjectName("lineEdit_19");
        lineEdit_19->setGeometry(QRect(140, 120, 113, 26));
        lineEdit_20 = new QLineEdit(widget_5);
        lineEdit_20->setObjectName("lineEdit_20");
        lineEdit_20->setGeometry(QRect(140, 170, 113, 26));
        lineEdit_22 = new QLineEdit(widget_5);
        lineEdit_22->setObjectName("lineEdit_22");
        lineEdit_22->setGeometry(QRect(140, 220, 113, 26));
        label_54 = new QLabel(widget_5);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(50, 220, 63, 20));
        tabWidget_5->addTab(nvfacture, QString());
        voirfacture = new QWidget();
        voirfacture->setObjectName("voirfacture");
        voirfacture->setStyleSheet(QString::fromUtf8("\n"
"#lineEdit_15\n"
"{\n"
"border:2px solid #42b5b2;\n"
"}\n"
"#lineEdit_16\n"
"{border:2px solid #42b5b2;}\n"
"#lineEdit_17\n"
"{border:2px solid #42b5b2;}\n"
"#lineEdit_21\n"
"{border:2px solid #42b5b2;}\n"
"#widget_6\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#widget_4\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#pushButton_10\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_7\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_11\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#pushButton_9\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
"#label_9\n"
"{color: #42b5b2; \n"
"font: 16pt \"Berlin Sans FB\"; }\n"
"#label_10\n"
"{color: #42b5b2; \n"
"font: 16pt \"Berlin Sans FB\"; }\n"
"#label_2\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"#label_3\n"
"{\n"
"font: 12"
                        "pt \"Berlin Sans FB\"; }\n"
"#label\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"\n"
"#label_8\n"
"{\n"
"font: 12pt \"Berlin Sans FB\"; }\n"
"\n"
"\n"
"\n"
""));
        widget_6 = new QWidget(voirfacture);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(230, 20, 441, 401));
        pushButton_9 = new QPushButton(widget_6);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(290, 20, 93, 29));
        pushButton_11 = new QPushButton(widget_6);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(310, 350, 93, 29));
        lineEdit_17 = new QLineEdit(widget_6);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(160, 20, 113, 26));
        lineEdit_21 = new QLineEdit(widget_6);
        lineEdit_21->setObjectName("lineEdit_21");
        lineEdit_21->setGeometry(QRect(170, 350, 113, 26));
        label_3 = new QLabel(widget_6);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 10, 51, 41));
        label_8 = new QLabel(widget_6);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 340, 51, 41));
        tableWidget_7 = new QTableWidget(widget_6);
        if (tableWidget_7->columnCount() < 3)
            tableWidget_7->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        tableWidget_7->setObjectName("tableWidget_7");
        tableWidget_7->setGeometry(QRect(20, 80, 411, 201));
        tableWidget_7->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #f9f9f9;\n"
"    color: #333;\n"
"    font-size: 14px;\n"
"    gridline-color: #e0e0e0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color:#8dced6 ;\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid #dddddd;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #e8f5e9;\n"
"    color: #333;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #eab676;\n"
"    color: white;\n"
"}\n"
""));
        label_10 = new QLabel(widget_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 10, 63, 20));
        tabWidget_5->addTab(voirfacture, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        tab_10->setStyleSheet(QString::fromUtf8("#widget_3\n"
"{\n"
"background-color:#fefeff;\n"
"border-radius:30px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#lineEdit_14\n"
"{border:2px solid #42b5b2;\n"
"}\n"
"#label_8\n"
"{\n"
"	font: 700 11pt \"Berlin Sans FB Demi\";\n"
"}\n"
"\n"
"\n"
"#pushButton_6\n"
"{\n"
"color: #42b5b2; \n"
"font: 12pt \"Berlin Sans FB\";\n"
"}\n"
""));
        graphicsView = new QGraphicsView(tab_10);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(70, 50, 361, 331));
        graphicsView_2 = new QGraphicsView(tab_10);
        graphicsView_2->setObjectName("graphicsView_2");
        graphicsView_2->setGeometry(QRect(480, 50, 361, 331));
        tabWidget_5->addTab(tab_10, QString());
        modules->addTab(finance, QString());
        pushButton = new QPushButton(app);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(812, 30, 121, 31));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"font: 15pt \"Berlin Sans FB\";"));
        stackedWidget->addWidget(app);
        interfaceConnexion = new QWidget();
        interfaceConnexion->setObjectName("interfaceConnexion");
        interfaceConnexion->setStyleSheet(QString::fromUtf8("#interfaceConnexion\n"
"{\n"
"background-color: #42b5b2;\n"
"}\n"
"#Box\n"
"{\n"
"	background-color: #fefeff;\n"
"	border-radius :20px #040301;\n"
"	border: 2px solid #040301;\n"
"}\n"
"#writeId\n"
"{\n"
"border:2px solid #42b5b2;\n"
"}\n"
"#writepass\n"
"{\n"
"border:2px solid #42b5b2;\n"
"}\n"
"#Enterbutton\n"
"{\n"
"color:#42b5b2;\n"
"font: 700 13pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#login\n"
"{\n"
"font: 700 30pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#Id\n"
"{\n"
"font: 700 13pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#Password\n"
"{\n"
"font: 700 13pt \"Berlin Sans FB Demi\";\n"
"}\n"
"#slogan\n"
"{\n"
"font: 700 13pt \"Berlin Sans FB Demi\";\n"
"color:#fefeff;\n"
"}\n"
"\n"
"\n"
""));
        Box = new QFrame(interfaceConnexion);
        Box->setObjectName("Box");
        Box->setGeometry(QRect(490, 50, 381, 511));
        Box->setFrameShape(QFrame::Shape::StyledPanel);
        Box->setFrameShadow(QFrame::Shadow::Raised);
        Password = new QLabel(Box);
        Password->setObjectName("Password");
        Password->setGeometry(QRect(50, 200, 121, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Berlin Sans FB Demi")});
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setItalic(false);
        Password->setFont(font1);
        writepass = new QLineEdit(Box);
        writepass->setObjectName("writepass");
        writepass->setGeometry(QRect(170, 200, 113, 26));
        Enterbutton = new QPushButton(Box);
        Enterbutton->setObjectName("Enterbutton");
        Enterbutton->setGeometry(QRect(230, 320, 93, 29));
        login = new QLabel(Box);
        login->setObjectName("login");
        login->setGeometry(QRect(110, 50, 181, 51));
        Logo = new QLabel(interfaceConnexion);
        Logo->setObjectName("Logo");
        Logo->setGeometry(QRect(-50, 140, 451, 181));
        Logo->setStyleSheet(QString::fromUtf8("font: 36pt \"Segoe UI\";"));
        Logo->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/0abf77c0-45b6-45df-89ee-da8bed3ac28b-removebg-preview.png")));
        slogan = new QLabel(interfaceConnexion);
        slogan->setObjectName("slogan");
        slogan->setGeometry(QRect(150, 290, 351, 21));
        stackedWidget->addWidget(interfaceConnexion);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        stackedWidget->setCurrentIndex(0);
        modules->setCurrentIndex(3);
        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(2);
        tabWidget_3->setCurrentIndex(0);
        tabWidget_4->setCurrentIndex(1);
        tabWidget_5->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        modules->setTabText(modules->indexOf(home), QCoreApplication::translate("MainWindow", "Home", nullptr));
        ADD->setText(QCoreApplication::translate("MainWindow", "ADD", nullptr));
        newtype->setText(QCoreApplication::translate("MainWindow", "New type :", nullptr));
        idnew->setText(QCoreApplication::translate("MainWindow", "Id :", nullptr));
        date->setText(QCoreApplication::translate("MainWindow", "Expiry date :", nullptr));
        NEW->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newstock), QCoreApplication::translate("MainWindow", "New", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Enter Id :", nullptr));
        remove1->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        search->setText(QCoreApplication::translate("MainWindow", "search something", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        search_3->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Types", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Expiry Date ", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Quantity", nullptr));
        STOCK->setText(QCoreApplication::translate("MainWindow", "              Stock", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(voirstock), QCoreApplication::translate("MainWindow", "Consult", nullptr));
        refillstock->setText(QCoreApplication::translate("MainWindow", "Refill Stock", nullptr));
        remove1_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Types", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Expiry Date ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Quantity to add", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Refill", nullptr));
        modules->setTabText(modules->indexOf(stock), QCoreApplication::translate("MainWindow", "Stock", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Cooking", nullptr));
        ADD_3->setText(QCoreApplication::translate("MainWindow", "ADD", nullptr));
        Product->setText(QCoreApplication::translate("MainWindow", "New product :", nullptr));
        id2->setText(QCoreApplication::translate("MainWindow", "Id :", nullptr));
        date_2->setText(QCoreApplication::translate("MainWindow", "Expiry date :", nullptr));
        quantity_2->setText(QCoreApplication::translate("MainWindow", "Quantity :", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "price", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "New", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        search_2->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        remove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        PRODUCTS->setText(QCoreApplication::translate("MainWindow", "Products ", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Consult", nullptr));
        modules->setTabText(modules->indexOf(products), QCoreApplication::translate("MainWindow", "Products", nullptr));
        add->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        paymentmethod->setText(QCoreApplication::translate("MainWindow", "Payment method :", nullptr));
        name->setText(QCoreApplication::translate("MainWindow", "Client name : ", nullptr));
        date_3->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Product reference :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Quantity :", nullptr));
        neworder->setText(QCoreApplication::translate("MainWindow", "New Order :", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(newOrder), QCoreApplication::translate("MainWindow", "New", nullptr));
        remove_2->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        trier->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(consultOrder), QCoreApplication::translate("MainWindow", "Consult", nullptr));
        modules->setTabText(modules->indexOf(orders), QCoreApplication::translate("MainWindow", "Orders", nullptr));
        nameproduct_2->setText(QCoreApplication::translate("MainWindow", "Date :", nullptr));
        Price_2->setText(QCoreApplication::translate("MainWindow", "Phone number :", nullptr));
        numberproduct_2->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        name_2->setText(QCoreApplication::translate("MainWindow", "Adress of client :", nullptr));
        paymentmethod_2->setText(QCoreApplication::translate("MainWindow", "Statue :", nullptr));
        add_2->setText(QCoreApplication::translate("MainWindow", "ADD", nullptr));
        Delivery_2->setText(QCoreApplication::translate("MainWindow", "Payment method :", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "name of client : ", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_8), QCoreApplication::translate("MainWindow", "New", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Order reference ", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Date ", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Client name ", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Adress ", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Phone number ", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Payment method", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Statue ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Search ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Order reference :", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Remove ", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_9), QCoreApplication::translate("MainWindow", "Consult", nullptr));
        modules->setTabText(modules->indexOf(delivery), QCoreApplication::translate("MainWindow", "Delivery", nullptr));
        modules->setTabText(modules->indexOf(canning), QCoreApplication::translate("MainWindow", "Canning", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Code :", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "Type :", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "Name :", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "PDF :", nullptr));
        tabWidget_5->setTabText(tabWidget_5->indexOf(nvfacture), QCoreApplication::translate("MainWindow", "New", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Code:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Code:", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_7->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_7->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_7->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Sale", nullptr));
        tabWidget_5->setTabText(tabWidget_5->indexOf(voirfacture), QCoreApplication::translate("MainWindow", "Consult", nullptr));
        tabWidget_5->setTabText(tabWidget_5->indexOf(tab_10), QCoreApplication::translate("MainWindow", "Statistics ", nullptr));
        modules->setTabText(modules->indexOf(finance), QCoreApplication::translate("MainWindow", "Finance", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Log out ", nullptr));
        Password->setText(QCoreApplication::translate("MainWindow", "Password :", nullptr));
        Enterbutton->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        login->setText(QCoreApplication::translate("MainWindow", "LOG IN", nullptr));
        Logo->setText(QString());
        slogan->setText(QCoreApplication::translate("MainWindow", "\"Keep It Fresh, Keep It Flavorful!\"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

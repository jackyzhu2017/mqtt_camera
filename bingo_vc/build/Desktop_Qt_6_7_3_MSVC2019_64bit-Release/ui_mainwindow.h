/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditMessage;
    QLabel *label_3;
    QPushButton *buttonSubscribe;
    QPushButton *buttonQuit;
    QPushButton *buttonPublish;
    QPlainTextEdit *editLog;
    QPushButton *buttonConnect;
    QLineEdit *lineEditHost;
    QLabel *label_4;
    QLineEdit *lineEditTopic;
    QLabel *label;
    QLineEdit *lineEditPort;
    QLabel *label_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(810, 664);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEditMessage = new QLineEdit(centralwidget);
        lineEditMessage->setObjectName("lineEditMessage");
        lineEditMessage->setGeometry(QRect(100, 110, 391, 26));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 70, 63, 20));
        buttonSubscribe = new QPushButton(centralwidget);
        buttonSubscribe->setObjectName("buttonSubscribe");
        buttonSubscribe->setGeometry(QRect(520, 70, 93, 29));
        buttonQuit = new QPushButton(centralwidget);
        buttonQuit->setObjectName("buttonQuit");
        buttonQuit->setGeometry(QRect(720, 570, 81, 41));
        buttonPublish = new QPushButton(centralwidget);
        buttonPublish->setObjectName("buttonPublish");
        buttonPublish->setGeometry(QRect(520, 110, 93, 29));
        editLog = new QPlainTextEdit(centralwidget);
        editLog->setObjectName("editLog");
        editLog->setGeometry(QRect(20, 140, 771, 61));
        buttonConnect = new QPushButton(centralwidget);
        buttonConnect->setObjectName("buttonConnect");
        buttonConnect->setGeometry(QRect(520, 30, 93, 29));
        lineEditHost = new QLineEdit(centralwidget);
        lineEditHost->setObjectName("lineEditHost");
        lineEditHost->setGeometry(QRect(80, 10, 411, 26));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 110, 63, 20));
        lineEditTopic = new QLineEdit(centralwidget);
        lineEditTopic->setObjectName("lineEditTopic");
        lineEditTopic->setGeometry(QRect(70, 70, 401, 26));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 63, 20));
        lineEditPort = new QLineEdit(centralwidget);
        lineEditPort->setObjectName("lineEditPort");
        lineEditPort->setGeometry(QRect(80, 40, 411, 26));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 40, 63, 20));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 200, 691, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 810, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEditMessage->setText(QCoreApplication::translate("MainWindow", "This is a test message", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Topic:", nullptr));
        buttonSubscribe->setText(QCoreApplication::translate("MainWindow", "Subscribe", nullptr));
        buttonQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        buttonPublish->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        buttonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        lineEditHost->setText(QCoreApplication::translate("MainWindow", "localhost", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        lineEditTopic->setText(QCoreApplication::translate("MainWindow", "qtmqtt/topic1", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Host:", nullptr));
        lineEditPort->setText(QCoreApplication::translate("MainWindow", "1883", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

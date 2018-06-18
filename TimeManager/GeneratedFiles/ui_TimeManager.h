/********************************************************************************
** Form generated from reading UI file 'TimeManager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEMANAGER_H
#define UI_TIMEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeManagerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TimeManagerClass)
    {
        if (TimeManagerClass->objectName().isEmpty())
            TimeManagerClass->setObjectName(QStringLiteral("TimeManagerClass"));
        TimeManagerClass->resize(600, 400);
        menuBar = new QMenuBar(TimeManagerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TimeManagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TimeManagerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TimeManagerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TimeManagerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TimeManagerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TimeManagerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TimeManagerClass->setStatusBar(statusBar);

        retranslateUi(TimeManagerClass);

        QMetaObject::connectSlotsByName(TimeManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TimeManagerClass)
    {
        TimeManagerClass->setWindowTitle(QApplication::translate("TimeManagerClass", "TimeManager", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TimeManagerClass: public Ui_TimeManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEMANAGER_H

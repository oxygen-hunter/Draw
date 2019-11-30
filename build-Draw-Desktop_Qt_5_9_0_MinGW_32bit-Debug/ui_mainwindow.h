/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Script;
    QAction *actionSave_Canvas;
    QAction *actionOpen_Terminal;
    QWidget *centralWidget;
    QLabel *CanvasLabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuTerminal;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 500);
        actionOpen_Script = new QAction(MainWindow);
        actionOpen_Script->setObjectName(QStringLiteral("actionOpen_Script"));
        actionSave_Canvas = new QAction(MainWindow);
        actionSave_Canvas->setObjectName(QStringLiteral("actionSave_Canvas"));
        actionOpen_Terminal = new QAction(MainWindow);
        actionOpen_Terminal->setObjectName(QStringLiteral("actionOpen_Terminal"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CanvasLabel = new QLabel(centralWidget);
        CanvasLabel->setObjectName(QStringLiteral("CanvasLabel"));
        CanvasLabel->setGeometry(QRect(110, 90, 301, 181));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu->setGeometry(QRect(339, 116, 150, 111));
        menuTerminal = new QMenu(menuBar);
        menuTerminal->setObjectName(QStringLiteral("menuTerminal"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuTerminal->menuAction());
        menu->addSeparator();
        menu->addAction(actionOpen_Script);
        menu->addAction(actionSave_Canvas);
        menuTerminal->addAction(actionOpen_Terminal);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Draw Demo", Q_NULLPTR));
        actionOpen_Script->setText(QApplication::translate("MainWindow", "Open Script", Q_NULLPTR));
        actionSave_Canvas->setText(QApplication::translate("MainWindow", "Save Canvas", Q_NULLPTR));
        actionOpen_Terminal->setText(QApplication::translate("MainWindow", "Open Terminal", Q_NULLPTR));
        CanvasLabel->setText(QApplication::translate("MainWindow", "TODO:\351\274\240\346\240\207\347\202\271\345\207\273\347\232\204\345\233\276\345\275\242\345\214\226\347\225\214\351\235\242", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuTerminal->setTitle(QApplication::translate("MainWindow", "Terminal", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

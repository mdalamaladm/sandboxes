/********************************************************************************
** Form generated from reading UI file 'notepad.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notepad
{
public:
    QAction *actionPrint_and_Exit;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionPrint_and_Exit_2;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuMenu;

    void setupUi(QMainWindow *Notepad)
    {
        if (Notepad->objectName().isEmpty())
            Notepad->setObjectName("Notepad");
        Notepad->resize(800, 600);
        actionPrint_and_Exit = new QAction(Notepad);
        actionPrint_and_Exit->setObjectName("actionPrint_and_Exit");
        actionNew = new QAction(Notepad);
        actionNew->setObjectName("actionNew");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actionNew->setIcon(icon);
        actionOpen = new QAction(Notepad);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(Notepad);
        actionSave->setObjectName("actionSave");
        actionSave_as = new QAction(Notepad);
        actionSave_as->setObjectName("actionSave_as");
        actionPrint_and_Exit_2 = new QAction(Notepad);
        actionPrint_and_Exit_2->setObjectName("actionPrint_and_Exit_2");
        centralwidget = new QWidget(Notepad);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        Notepad->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Notepad);
        statusbar->setObjectName("statusbar");
        Notepad->setStatusBar(statusbar);
        menubar = new QMenuBar(Notepad);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        Notepad->setMenuBar(menubar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionNew);
        menuMenu->addAction(actionOpen);
        menuMenu->addAction(actionSave);
        menuMenu->addAction(actionSave_as);
        menuMenu->addAction(actionPrint_and_Exit_2);

        retranslateUi(Notepad);

        QMetaObject::connectSlotsByName(Notepad);
    } // setupUi

    void retranslateUi(QMainWindow *Notepad)
    {
        Notepad->setWindowTitle(QCoreApplication::translate("Notepad", "Notepad", nullptr));
        actionPrint_and_Exit->setText(QCoreApplication::translate("Notepad", "Print and Exit", nullptr));
        actionNew->setText(QCoreApplication::translate("Notepad", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("Notepad", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("Notepad", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("Notepad", "Save as", nullptr));
        actionPrint_and_Exit_2->setText(QCoreApplication::translate("Notepad", "Print and Exit", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("Notepad", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Notepad: public Ui_Notepad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H

/********************************************************************************
** Form generated from reading UI file 'mainUI.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUI_H
#define UI_MAINUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiDlg
{
public:
    QPushButton *Start;
    QPushButton *Stop;
    QTextEdit *InfoText;
    QGraphicsView *Grafico;
    QLCDNumber *LCDhor;
    QLCDNumber *LCDmin;
    QLCDNumber *LCDseg;

    void setupUi(QWidget *guiDlg)
    {
        if (guiDlg->objectName().isEmpty())
            guiDlg->setObjectName(QString::fromUtf8("guiDlg"));
        guiDlg->resize(838, 559);
        Start = new QPushButton(guiDlg);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(10, 500, 131, 51));
        Stop = new QPushButton(guiDlg);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(150, 500, 131, 51));
        InfoText = new QTextEdit(guiDlg);
        InfoText->setObjectName(QString::fromUtf8("InfoText"));
        InfoText->setGeometry(QRect(10, 80, 271, 411));
        Grafico = new QGraphicsView(guiDlg);
        Grafico->setObjectName(QString::fromUtf8("Grafico"));
        Grafico->setGeometry(QRect(290, 10, 541, 541));
        LCDhor = new QLCDNumber(guiDlg);
        LCDhor->setObjectName(QString::fromUtf8("LCDhor"));
        LCDhor->setGeometry(QRect(40, 10, 61, 61));
        LCDhor->setDigitCount(2);
        LCDmin = new QLCDNumber(guiDlg);
        LCDmin->setObjectName(QString::fromUtf8("LCDmin"));
        LCDmin->setGeometry(QRect(110, 10, 61, 61));
        LCDmin->setDigitCount(2);
        LCDseg = new QLCDNumber(guiDlg);
        LCDseg->setObjectName(QString::fromUtf8("LCDseg"));
        LCDseg->setGeometry(QRect(180, 30, 51, 41));
        LCDseg->setDigitCount(2);

        retranslateUi(guiDlg);

        QMetaObject::connectSlotsByName(guiDlg);
    } // setupUi

    void retranslateUi(QWidget *guiDlg)
    {
        guiDlg->setWindowTitle(QApplication::translate("guiDlg", "controller", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("guiDlg", "Start Robot", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("guiDlg", "Stop Robot", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class guiDlg: public Ui_guiDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUI_H

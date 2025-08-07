/********************************************************************************
** Form generated from reading UI file 'RecvWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECVWIDGET_H
#define UI_RECVWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecvWidget
{
public:
    QVBoxLayout *vlMain;
    QGroupBox *gbRecv;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbASCII;
    QRadioButton *rbHEX;
    QSpacerItem *horizontalSpacer;
    QCheckBox *cbAutoLine;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *RecvWidget)
    {
        if (RecvWidget->objectName().isEmpty())
            RecvWidget->setObjectName(QString::fromUtf8("RecvWidget"));
        RecvWidget->resize(190, 94);
        vlMain = new QVBoxLayout(RecvWidget);
        vlMain->setObjectName(QString::fromUtf8("vlMain"));
        vlMain->setContentsMargins(5, 5, 5, 5);
        gbRecv = new QGroupBox(RecvWidget);
        gbRecv->setObjectName(QString::fromUtf8("gbRecv"));
        gbRecv->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(gbRecv);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rbASCII = new QRadioButton(gbRecv);
        rbASCII->setObjectName(QString::fromUtf8("rbASCII"));
        rbASCII->setChecked(true);

        horizontalLayout->addWidget(rbASCII);

        rbHEX = new QRadioButton(gbRecv);
        rbHEX->setObjectName(QString::fromUtf8("rbHEX"));

        horizontalLayout->addWidget(rbHEX);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        cbAutoLine = new QCheckBox(gbRecv);
        cbAutoLine->setObjectName(QString::fromUtf8("cbAutoLine"));
        cbAutoLine->setChecked(true);

        verticalLayout->addWidget(cbAutoLine);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        vlMain->addWidget(gbRecv);


        retranslateUi(RecvWidget);

        QMetaObject::connectSlotsByName(RecvWidget);
    } // setupUi

    void retranslateUi(QWidget *RecvWidget)
    {
        RecvWidget->setWindowTitle(QCoreApplication::translate("RecvWidget", "Form", nullptr));
        gbRecv->setTitle(QCoreApplication::translate("RecvWidget", "\346\216\245\346\224\266\350\256\276\347\275\256", nullptr));
        rbASCII->setText(QCoreApplication::translate("RecvWidget", "ASCII", nullptr));
        rbHEX->setText(QCoreApplication::translate("RecvWidget", "HEX", nullptr));
        cbAutoLine->setText(QCoreApplication::translate("RecvWidget", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecvWidget: public Ui_RecvWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECVWIDGET_H

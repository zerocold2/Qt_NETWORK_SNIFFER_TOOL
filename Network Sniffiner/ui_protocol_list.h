/********************************************************************************
** Form generated from reading UI file 'protocol_list.ui'
**
** Created: Tue Jun 25 01:10:30 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOL_LIST_H
#define UI_PROTOCOL_LIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Protocol_List
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Protocol_List)
    {
        if (Protocol_List->objectName().isEmpty())
            Protocol_List->setObjectName(QString::fromUtf8("Protocol_List"));
        Protocol_List->resize(409, 449);
        verticalLayout = new QVBoxLayout(Protocol_List);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Protocol_List);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(Protocol_List);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Protocol_List);
        QObject::connect(buttonBox, SIGNAL(accepted()), Protocol_List, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Protocol_List, SLOT(reject()));

        QMetaObject::connectSlotsByName(Protocol_List);
    } // setupUi

    void retranslateUi(QDialog *Protocol_List)
    {
        Protocol_List->setWindowTitle(QApplication::translate("Protocol_List", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Protocol_List", "List Of Protocols", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Protocol_List: public Ui_Protocol_List {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOL_LIST_H

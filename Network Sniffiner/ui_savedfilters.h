/********************************************************************************
** Form generated from reading UI file 'savedfilters.ui'
**
** Created: Tue Jun 25 01:10:30 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEDFILTERS_H
#define UI_SAVEDFILTERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SavedFilters
{
public:
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QListView *listView;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *SavedFilters)
    {
        if (SavedFilters->objectName().isEmpty())
            SavedFilters->setObjectName(QString::fromUtf8("SavedFilters"));
        SavedFilters->setEnabled(true);
        SavedFilters->resize(514, 480);
        SavedFilters->setAcceptDrops(false);
        groupBox = new QGroupBox(SavedFilters);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(9, 9, 491, 331));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        horizontalLayout_2->addWidget(listView);

        groupBox_3 = new QGroupBox(SavedFilters);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(9, 339, 491, 101));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setReadOnly(true);

        verticalLayout_2->addWidget(lineEdit_2);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout);

        widget = new QWidget(SavedFilters);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(320, 450, 180, 27));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        retranslateUi(SavedFilters);
        QObject::connect(pushButton, SIGNAL(clicked()), SavedFilters, SLOT(close()));

        QMetaObject::connectSlotsByName(SavedFilters);
    } // setupUi

    void retranslateUi(QDialog *SavedFilters)
    {
        SavedFilters->setWindowTitle(QApplication::translate("SavedFilters", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SavedFilters", "Saved Filters", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SavedFilters", "Properties", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SavedFilters", "Filter Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SavedFilters", "Filter String: ", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("SavedFilters", "Ok", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SavedFilters", "Cancle", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SavedFilters: public Ui_SavedFilters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEDFILTERS_H

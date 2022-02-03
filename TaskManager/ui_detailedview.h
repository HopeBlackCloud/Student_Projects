/********************************************************************************
** Form generated from reading UI file 'detailedview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILEDVIEW_H
#define UI_DETAILEDVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_detailedview
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEditDetailedView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonCloseDetailedView;

    void setupUi(QDialog *detailedview)
    {
        if (detailedview->objectName().isEmpty())
            detailedview->setObjectName(QStringLiteral("detailedview"));
        detailedview->setEnabled(true);
        detailedview->resize(359, 364);
        detailedview->setModal(true);
        verticalLayout = new QVBoxLayout(detailedview);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(detailedview);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        textEditDetailedView = new QTextEdit(detailedview);
        textEditDetailedView->setObjectName(QStringLiteral("textEditDetailedView"));
        textEditDetailedView->setEnabled(true);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        textEditDetailedView->setFont(font);
        textEditDetailedView->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(textEditDetailedView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonCloseDetailedView = new QPushButton(detailedview);
        pushButtonCloseDetailedView->setObjectName(QStringLiteral("pushButtonCloseDetailedView"));
        pushButtonCloseDetailedView->setEnabled(true);

        horizontalLayout_2->addWidget(pushButtonCloseDetailedView);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(detailedview);
        QObject::connect(pushButtonCloseDetailedView, SIGNAL(clicked()), detailedview, SLOT(close()));

        QMetaObject::connectSlotsByName(detailedview);
    } // setupUi

    void retranslateUi(QDialog *detailedview)
    {
        detailedview->setWindowTitle(QApplication::translate("detailedview", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("detailedview", "Detailed View", Q_NULLPTR));
        pushButtonCloseDetailedView->setText(QApplication::translate("detailedview", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class detailedview: public Ui_detailedview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILEDVIEW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *system_tab;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *osrelease_textedit;
    QTextEdit *model_name_textedit;
    QTextEdit *storage_textedit;
    QWidget *processes_tab;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidgetProcess;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonDetailedView;
    QToolButton *toolButtonStopContinue;
    QToolButton *toolButtonKill;
    QToolButton *toolButtonFileList;
    QToolButton *toolButtonMemoryMap;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonAllUsers;
    QRadioButton *radioButtonCurrentUser;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonRefresh;
    QWidget *resources_tab;
    QWidget *filesystems_tab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidgetDrives;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(648, 626);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        system_tab = new QWidget();
        system_tab->setObjectName(QStringLiteral("system_tab"));
        verticalLayout_3 = new QVBoxLayout(system_tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        osrelease_textedit = new QTextEdit(system_tab);
        osrelease_textedit->setObjectName(QStringLiteral("osrelease_textedit"));
        osrelease_textedit->setReadOnly(true);

        verticalLayout_3->addWidget(osrelease_textedit);

        model_name_textedit = new QTextEdit(system_tab);
        model_name_textedit->setObjectName(QStringLiteral("model_name_textedit"));
        model_name_textedit->setReadOnly(true);

        verticalLayout_3->addWidget(model_name_textedit);

        storage_textedit = new QTextEdit(system_tab);
        storage_textedit->setObjectName(QStringLiteral("storage_textedit"));
        storage_textedit->setReadOnly(true);

        verticalLayout_3->addWidget(storage_textedit);

        tabWidget->addTab(system_tab, QString());
        processes_tab = new QWidget();
        processes_tab->setObjectName(QStringLiteral("processes_tab"));
        verticalLayout = new QVBoxLayout(processes_tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidgetProcess = new QTreeWidget(processes_tab);
        treeWidgetProcess->setObjectName(QStringLiteral("treeWidgetProcess"));
        treeWidgetProcess->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidgetProcess->setProperty("showDropIndicator", QVariant(false));
        treeWidgetProcess->setAlternatingRowColors(true);

        verticalLayout->addWidget(treeWidgetProcess);

        groupBox_2 = new QGroupBox(processes_tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButtonDetailedView = new QPushButton(groupBox_2);
        pushButtonDetailedView->setObjectName(QStringLiteral("pushButtonDetailedView"));
        pushButtonDetailedView->setEnabled(false);

        horizontalLayout_3->addWidget(pushButtonDetailedView);

        toolButtonStopContinue = new QToolButton(groupBox_2);
        toolButtonStopContinue->setObjectName(QStringLiteral("toolButtonStopContinue"));
        toolButtonStopContinue->setEnabled(false);
        toolButtonStopContinue->setCheckable(true);

        horizontalLayout_3->addWidget(toolButtonStopContinue);

        toolButtonKill = new QToolButton(groupBox_2);
        toolButtonKill->setObjectName(QStringLiteral("toolButtonKill"));
        toolButtonKill->setEnabled(false);

        horizontalLayout_3->addWidget(toolButtonKill);

        toolButtonFileList = new QToolButton(groupBox_2);
        toolButtonFileList->setObjectName(QStringLiteral("toolButtonFileList"));
        toolButtonFileList->setEnabled(false);

        horizontalLayout_3->addWidget(toolButtonFileList);

        toolButtonMemoryMap = new QToolButton(groupBox_2);
        toolButtonMemoryMap->setObjectName(QStringLiteral("toolButtonMemoryMap"));
        toolButtonMemoryMap->setEnabled(false);

        horizontalLayout_3->addWidget(toolButtonMemoryMap);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(processes_tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButtonAllUsers = new QRadioButton(groupBox);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButtonAllUsers);
        radioButtonAllUsers->setObjectName(QStringLiteral("radioButtonAllUsers"));

        horizontalLayout->addWidget(radioButtonAllUsers);

        radioButtonCurrentUser = new QRadioButton(groupBox);
        buttonGroup->addButton(radioButtonCurrentUser);
        radioButtonCurrentUser->setObjectName(QStringLiteral("radioButtonCurrentUser"));

        horizontalLayout->addWidget(radioButtonCurrentUser);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonRefresh = new QPushButton(groupBox);
        pushButtonRefresh->setObjectName(QStringLiteral("pushButtonRefresh"));

        horizontalLayout->addWidget(pushButtonRefresh);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        tabWidget->addTab(processes_tab, QString());
        resources_tab = new QWidget();
        resources_tab->setObjectName(QStringLiteral("resources_tab"));
        tabWidget->addTab(resources_tab, QString());
        filesystems_tab = new QWidget();
        filesystems_tab->setObjectName(QStringLiteral("filesystems_tab"));
        verticalLayout_4 = new QVBoxLayout(filesystems_tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tableWidgetDrives = new QTableWidget(filesystems_tab);
        if (tableWidgetDrives->columnCount() < 7)
            tableWidgetDrives->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetDrives->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidgetDrives->setObjectName(QStringLiteral("tableWidgetDrives"));
        tableWidgetDrives->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_4->addWidget(tableWidgetDrives);

        tabWidget->addTab(filesystems_tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(system_tab), QApplication::translate("MainWindow", "System", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetProcess->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "User", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Process Name", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Operations On Process", Q_NULLPTR));
        pushButtonDetailedView->setText(QApplication::translate("MainWindow", "Detailed View", Q_NULLPTR));
        toolButtonStopContinue->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        toolButtonKill->setText(QApplication::translate("MainWindow", "Kill", Q_NULLPTR));
        toolButtonFileList->setText(QApplication::translate("MainWindow", "File List", Q_NULLPTR));
        toolButtonMemoryMap->setText(QApplication::translate("MainWindow", "Memory Map", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Filter Process By User", Q_NULLPTR));
        radioButtonAllUsers->setText(QApplication::translate("MainWindow", "All Users", Q_NULLPTR));
        radioButtonCurrentUser->setText(QApplication::translate("MainWindow", "Current User", Q_NULLPTR));
        pushButtonRefresh->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(processes_tab), QApplication::translate("MainWindow", "Processes", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(resources_tab), QApplication::translate("MainWindow", "Resources", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetDrives->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Device", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetDrives->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Directory", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDrives->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDrives->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Total", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetDrives->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Free", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetDrives->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Available", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetDrives->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Used", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(filesystems_tab), QApplication::translate("MainWindow", "File Systems", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

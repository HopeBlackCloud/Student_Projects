#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QtGui>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "process.h"
#include "detailedview.h"

struct Drive_Info
{
	QString device;
	QString directory;
	QString type;
	double total;
	double free;
	double available;
};

namespace Ui 
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_tabWidget_tabBarClicked(int index);
    void update_process_information();

    void on_toolButtonKill_clicked();
    void setActiveTool();
    void setPassiveTool();

    void on_radioButtonCurrentUser_clicked();
    void on_radioButtonAllUsers_clicked();
    void on_pushButtonDetailedView_clicked();
    void on_toolButtonStopContinue_toggled(bool checked);
    void on_pushButtonRefresh_clicked();

    void refresh_list();

private:
    void update_system_informations();
    void update_drive_information();
    std::vector<Drive_Info> get_mount_information();
    void update_filtered_process_information();
    void addTreeChild(QTreeWidgetItem *parent, QString id,
                      QString name, QString status, QString user_name);
    QString get_login_user();
    void fill_drives_table();
    void fill_process_tree(std::vector<pi::Process> process_list);
    void fill_filtered_process_tree(std::vector<pi::Process> process_list);
    void openDetailedViewWindow();

private:
    Ui::MainWindow *ui;
    QTreeWidgetItem *treeItem;
};

#endif // MAINWINDOW_H

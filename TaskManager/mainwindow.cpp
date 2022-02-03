#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "systeminformation.h"
#include "definitions.h"
#include "detailedview.h"

#include <QString>
#include <QTimer>
#include <QStorageInfo>
#include <QTreeWidget>

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_system_informations();

    connect(ui->treeWidgetProcess, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setActiveTool()));

    QTimer *timer= new QTimer(this);
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(refresh_list()));
    timer->start(1000);

    ui->tabWidget->setCurrentIndex(0);
    connect(ui->pushButtonDetailedView, SIGNAL(click()), this, SLOT(openDetailedViewWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDetailedViewWindow()
{
    detailedview *det_view = new detailedview(this,
                                             ui->treeWidgetProcess->currentItem()->text(0).toInt());
    det_view->show();
}

void MainWindow::setActiveTool()
{
    ui->toolButtonKill->setEnabled(true);
    ui->toolButtonFileList->setEnabled(true);
    ui->toolButtonMemoryMap->setEnabled(true);
    ui->toolButtonStopContinue->setEnabled(true);
    ui->pushButtonDetailedView->setEnabled(true);
}

void MainWindow::setPassiveTool(){
    ui->toolButtonKill->setEnabled(false);
    ui->toolButtonFileList->setEnabled(false);
    ui->toolButtonMemoryMap->setEnabled(false);
    ui->toolButtonStopContinue->setEnabled(false);
    ui->pushButtonDetailedView->setEnabled(false);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == TAB_TYPES_SYSTEM)
        update_system_informations();
    else if (index == TAB_TYPES_PROCESSES)
        update_process_information();
    else if (index == TAB_TYPES_FILE_SYSTEMS)
        update_drive_information();
}

void MainWindow::fill_process_tree(std::vector<pi::Process> process_list)
{
    ui->treeWidgetProcess->clear();
    for (auto& process : process_list)
    {
        // Check if it's a parent process
        if (process.parent_id == 0)
		{
            treeItem = new QTreeWidgetItem(ui->treeWidgetProcess);
            treeItem->setText(0, QString("%1").arg(process.id));
            treeItem->setText(1, QString(process.name.c_str()));
            treeItem->setText(2, QString(process.state.c_str()));
            treeItem->setText(3, QString(process.user_name.c_str()));

        }else
		{
            if (treeItem != NULL)
			{
                addTreeChild(treeItem, QString("%1").arg(process.id), QString(process.name.c_str()),
                             QString(process.state.c_str()),QString(process.user_name.c_str()));
            }
        }
    }
	
    treeItem->setExpanded(true);
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, QString id,
                              QString name, QString status, QString user_name)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    treeItem->setText(0, id);
    treeItem->setText(1, name);
    treeItem->setText(2, status);
    treeItem->setText(3, user_name);
	
    parent->addChild(treeItem);
}

void MainWindow::fill_drives_table()
{
    int row = 0;
    auto drive_list = get_mount_information();
    ui->tableWidgetDrives->clear();
	
    for (auto& drive : drive_list)
    {
        ui->tableWidgetDrives->insertRow( ui->tableWidgetDrives->rowCount() );
        QTableWidgetItem *pCell =  ui->tableWidgetDrives->item(row, 0);

        if(!pCell)
        {
           pCell = new QTableWidgetItem;
           pCell->setText(drive.device);
           ui->tableWidgetDrives->setItem(row, 0, pCell);
        }

		pCell =  ui->tableWidgetDrives->item(row, 1);

		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(drive.directory);
			ui->tableWidgetDrives->setItem(row, 1, pCell);
		}

        pCell =  ui->tableWidgetDrives->item(row, 2);

		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(drive.type);
			ui->tableWidgetDrives->setItem(row, 2, pCell);
		}

		pCell =  ui->tableWidgetDrives->item(row, 3);

		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(QString("%1").arg((drive.total)/1024/1024));
			ui->tableWidgetDrives->setItem(row, 3, pCell);
		}

		pCell =  ui->tableWidgetDrives->item(row, 4);

		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(QString("%1").arg((drive.free)/1024/1024));
			ui->tableWidgetDrives->setItem(row, 4, pCell);
		}

		pCell =  ui->tableWidgetDrives->item(row, 5);

		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(QString("%1").arg((drive.available)/1024/1024));
			ui->tableWidgetDrives->setItem(row, 5, pCell);
		}

		pCell =  ui->tableWidgetDrives->item(row, 6);
		double used = drive.total - drive.free;
		
		if(!pCell)
		{
			pCell = new QTableWidgetItem;
			pCell->setText(QString("%1").arg((used)/1024/1024));
			ui->tableWidgetDrives->setItem(row, 6, pCell);
		}

        row++;
    }
}

std::vector<Drive_Info> MainWindow::get_mount_information()
{
    Drive_Info drive_info;
    std::vector<Drive_Info> drive_list;
	
    for (auto volume : QStorageInfo::mountedVolumes()) 
	{
		drive_info.device = volume.device();
		drive_info.directory = volume.rootPath();
		drive_info.type = volume.fileSystemType();

		drive_info.available = volume.bytesAvailable();
		drive_info.free = volume.bytesFree();
		drive_info.total = volume.bytesTotal() ;
		drive_list.push_back(drive_info);
    }
	
    return drive_list;
}

void MainWindow::fill_filtered_process_tree(std::vector<pi::Process> process_list)
{
    ui->treeWidgetProcess->clear();

    treeItem = new QTreeWidgetItem(ui->treeWidgetProcess);

    treeItem->setText(0, get_login_user());

    for (auto& process : process_list)
    {
		if (treeItem != NULL)
		{
			addTreeChild(treeItem, QString("%1").arg(process.id), QString(process.name.c_str()),
						 QString(process.state.c_str()),QString(process.user_name.c_str()));

        }
    }
     
	treeItem->setExpanded(true);
}

QString MainWindow::get_login_user()
{
    struct passwd *passwd;
    passwd = getpwuid (getuid());
    return QString(passwd->pw_name);
}

void MainWindow::update_process_information()
{
    fill_process_tree(pi::Process::list());
}

void MainWindow::update_filtered_process_information()
{
    auto allProcess = pi::Process::list();
    auto filterProcess = pi::Process::filter(allProcess,get_login_user().toStdString());
    fill_filtered_process_tree(filterProcess);
}

void MainWindow::update_drive_information()
{
    fill_drives_table();
}

void MainWindow::update_system_informations()
{
    SystemInformation systemInformation;
    char * releaseVersion = systemInformation.getRelease();
    ui->osrelease_textedit->setText(releaseVersion);

    char *modelVersion = systemInformation.getModel();
    ui->model_name_textedit->setText(modelVersion);

    char *storageInfo = systemInformation.getStorage();
    ui->storage_textedit->setText(storageInfo);
}

void MainWindow::on_toolButtonKill_clicked()
{
   pi::Process killProcess;

   killProcess.id = ui->treeWidgetProcess->currentItem()->text(0).toInt();

   killProcess.p_kill();

   update_process_information();
   
   setPassiveTool();
}

void MainWindow::on_radioButtonCurrentUser_clicked()
{
    update_filtered_process_information();
}

void MainWindow::on_radioButtonAllUsers_clicked()
{
    update_process_information();
}

void MainWindow::on_pushButtonDetailedView_clicked()
{
    openDetailedViewWindow();
    setPassiveTool();
}

void MainWindow::on_toolButtonStopContinue_toggled(bool checked)
{
    pi::Process proc;
    proc.id = ui->treeWidgetProcess->currentItem()->text(0).toInt();

    if (checked)
	{
		proc.p_pause();
		ui->toolButtonStopContinue->setText("continue");
    }
	else
	{
        proc.p_continue();
        ui->toolButtonStopContinue->setText("stop");
    }
}

void MainWindow::on_pushButtonRefresh_clicked()
{
    refresh_list();
}

void MainWindow::refresh_list(){
    if (ui->radioButtonAllUsers->isChecked())
        update_process_information();
    else if (ui->radioButtonCurrentUser->isChecked())
        update_filtered_process_information();
}


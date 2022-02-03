#include "detailedview.h"
#include "ui_detailedview.h"
#include <QTextStream>


detailedview::detailedview(QWidget *parent, int proc_id) :
    QDialog(parent),
    ui(new Ui::detailedview)
{
    ui->setupUi(this);
    QString detailed;
    auto process_list = pi::Process::list();

    for (auto detailed_process: process_list)
    {
        if (detailed_process.id == proc_id)
        {
               detailed = "Process Name: " + QString("%1").arg(detailed_process.name.c_str())+"\n";
               detailed += "Process ID: " + QString("%1").arg(detailed_process.id)+"\n";
               detailed += "Parent ID: " + QString("%1").arg(detailed_process.parent_id)+"\n";
               detailed += "User: " + QString("%1").arg(detailed_process.user_name.c_str())+"\n";
               detailed += "State " + QString("%1").arg(detailed_process.state.c_str())+"\n";
               detailed += "VM Data: " + QString("%1").arg(detailed_process.vm_data)+"\n";
               detailed += "VM Size: " + QString("%1").arg(detailed_process.vm_size)+"\n";
               detailed += "FD Size: " + QString("%1").arg(detailed_process.fd_size)+"\n";
               detailed += "Threads: " + QString("%1").arg(detailed_process.number_of_process);

        }
    }

    ui->textEditDetailedView->setText(detailed);
}

detailedview::~detailedview()
{
    delete ui;
}



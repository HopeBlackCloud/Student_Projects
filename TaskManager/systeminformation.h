#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <sys/sysinfo.h>
#include <string>
#include <sys/utsname.h>

#include <QTextStream>
#include <QFile>

#include "mainwindow.h"

using namespace std;

class SystemInformation
{
public:
    SystemInformation();

    char* getRelease();
    char* getModel();
    char* getStorage();
};

#endif // SYSTEMINFORMATION_H

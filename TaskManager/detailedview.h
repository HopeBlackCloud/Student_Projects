#ifndef DETAILEDVIEW_H
#define DETAILEDVIEW_H

#include <QDialog>

#include "process.h"

namespace Ui {
class detailedview;
}

class detailedview : public QDialog
{
    Q_OBJECT

public:
    explicit detailedview(QWidget *parent, int proc_id);
    ~detailedview();

private:
    Ui::detailedview *ui;


};

#endif // DETAILEDVIEW_H

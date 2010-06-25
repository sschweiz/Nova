#ifndef NWMOUTPUTDOCK_H
#define NWMOUTPUTDOCK_H

#include <QMainWindow>
#include <QWidget>
#include "nwmlistwidget.h"

class nwmOutputDock : public QWidget
{
Q_OBJECT

public:
    nwmOutputDock(QWidget *parent = 0);

private:
    void PopulateToolbar();

public slots:
    void save();

public:
    nwmListWidget *m_Output;
    QToolBar *m_Toolbar;
};

#endif // NWMOUTPUTDOCK_H

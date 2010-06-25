#ifndef NWMAPP_H
#define NWMAPP_H

#include <QApplication>
#include <QStandardItemModel>
#include "nwmmodel.h"
#include "nwmmainwindow.h"

class nwmApp;
#define theApp (static_cast<nwmApp *>(QCoreApplication::instance()))

typedef struct __nwmProperty
{
    QString setting, val;
} nwmProperty;

class nwmApp : public QApplication
{
Q_OBJECT

public:
    nwmApp(int &argc, char **argv);

    nwmMainWindow *MainWindow();
    void setMainWindow(nwmMainWindow *wnd);


    void PropertiesLoadAndShow(nwmModel *model, QString name);
    nwmTreeItem *addModelChild(const QString &name, const QVariant &value, nwmInternalData internal, nwmTreeItem *parent);
    nwmTreeItem *addModelChild(const QString &name, const QVariant &value, nwmTreeItem *parent);

    QVariant lookupValue(const QString &name);
public:
    nwmModel *m_Model;

private:
    nwmTreeItem *m_Root;
    nwmMainWindow *m_MainWnd;
};

#endif // NWMAPP_H

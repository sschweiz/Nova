#include <QtGui>
#include "nwmapp.h"

nwmApp::nwmApp(int &argc, char**argv) : QApplication(argc, argv)
{
    m_Root = new nwmTreeItem(tr("Setting"), tr("Value"));

    nwmTreeItem *it = addModelChild(tr("grid"), QVariant(), m_Root);
    addModelChild(tr("bg_color"), QColor(115,115,115,255), it);
    addModelChild(tr("grid_color"), QColor(105,105,105,255), it);

    m_Model = new nwmModel(m_Root);
}

nwmMainWindow *nwmApp::MainWindow()
{
    return m_MainWnd;
}

nwmTreeItem *nwmApp::addModelChild(const QString &name, const QVariant &value, nwmInternalData internal, nwmTreeItem *parent)
{
    nwmTreeItem *item = new nwmTreeItem(name, value, internal, parent);
    parent->appendChild(item);
    return item;
}

nwmTreeItem *nwmApp::addModelChild(const QString &name, const QVariant &value, nwmTreeItem *parent)
{
    nwmTreeItem *item = new nwmTreeItem(name, value, parent);
    parent->appendChild(item);
    return item;
}

QVariant nwmApp::lookupValue(const QString &name)
{
    QModelIndex ii = m_Model->findChildVariable(name);
    QModelIndex iv = ii.sibling(ii.row(), 1);

    return iv.data(Qt::DisplayRole);
}

void nwmApp::setMainWindow(nwmMainWindow *wnd)
{
    m_MainWnd = wnd;
}

void nwmApp::PropertiesLoadAndShow(nwmModel *model, QString name)
{
    //m_MainWnd->m_dockGridProps->setModel(model);
    //m_MainWnd->m_dockGridProps->setRootIndex();

    m_MainWnd->m_Docks[0]->setWindowTitle(name);
    m_MainWnd->m_Docks[0]->show();
}

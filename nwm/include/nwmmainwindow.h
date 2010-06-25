#ifndef NWMMAINWINDOW_H
#define NWMMAINWINDOW_H

#include <QMainWindow>
#include "nwmrenderwidget.h"
#include "nwmoutputdock.h"
#include "nwmresultswidget.h"
#include "nwmtriggereditorwidget.h"
#include "nwmpropertywidget.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QListWidget;
class QTreeView;
class QToolBox;
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE

class nwmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    nwmMainWindow();

private:
    void SetupDocks();
    void SetupMenus();
    void SetupDockBar();
    void SetupToolbar();
    void SetupToolbox();

public slots:
    void showEnvironmentInDock();

public:
    // Grid Properties, Overlays, Output, *Overlay Results, *Quick Trigger Code Input
    // * To be implemented
    QDockWidget *m_Docks[5];
    nwmRenderWidget *m_renderMain;

    QTreeView *m_dockGridProps;
    nwmPropertyWidget *m_dockProps;
    QListWidget *m_dockOverlays;
    nwmOutputDock *m_dockOutput;
    nwmResultsWidget *m_dockResults;
    nwmTriggerEditorWidget *m_dockEditor;

protected:
    QWidget *createToolboxButton(QIcon icon, QString text);

private:

    QMenu *m_menuFile;
    QMenu *m_menuEdit;
    QMenu *m_menuView;
    QMenu *m_menuEnvironment;
    QMenu *m_menuPackages;
    QMenu *m_menuWindow;
    QMenu *m_menuHelp;


    QToolBar *m_mainbar;
    QToolBar *m_dockbar;
    QToolBox *m_toolbox;

    QGraphicsScene *m_sceneResults;
};

#endif // NWMMAINWINDOW_H

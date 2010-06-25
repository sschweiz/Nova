#include <QtGui>
#include <time.h>
#include "nwmmainwindow.h"
#include "qdockbutton.h"
#include "nwmresultitem.h"


nwmMainWindow::nwmMainWindow()
{
    m_renderMain = new nwmRenderWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *mainwidge = new QWidget;

    m_toolbox = new QToolBox;
    m_toolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));

    SetupToolbox();

    layout->setMargin(1);
    layout->setSpacing(2);
    layout->addWidget(m_toolbox);
    layout->addWidget(m_renderMain);

    mainwidge->setLayout(layout);
    setCentralWidget(mainwidge);

    setWindowTitle(tr("Nova"));
    setUnifiedTitleAndToolBarOnMac(true);


    m_sceneResults = new QGraphicsScene;
    nwmResultItem *item = new nwmResultItem;
    item->setPos(QPointF(10, 10));
    m_sceneResults->addItem(item);
    //m_sceneResults->setBackgroundBrush(Qt::white);


    SetupMenus();
    m_mainbar = addToolBar(tr("Standard"));
    statusBar()->showMessage(tr("Ready"));

    SetupToolbar();

    SetupDockBar();

    m_Docks[0]->hide();
    m_Docks[1]->hide();
}

QWidget *nwmMainWindow::createToolboxButton(QIcon icon, QString text)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(icon);
    button->setIconSize(QSize(16, 16));
    button->setFixedSize(32, 32);

    return button;
}

void nwmMainWindow::SetupToolbox()
{
    QGridLayout *boxlayout = new QGridLayout;
    boxlayout->addWidget(createToolboxButton(QIcon(":/star.png"), tr("1")), 0, 0);
    boxlayout->addWidget(createToolboxButton(QIcon(":/star.png"), tr("2")), 0, 1);
    boxlayout->addWidget(createToolboxButton(QIcon(":/star.png"), tr("3")), 0, 2);
    boxlayout->addWidget(createToolboxButton(QIcon(":/star.png"), tr("4")), 1, 0);
    boxlayout->addWidget(createToolboxButton(QIcon(":/star.png"), tr("5")), 1, 1);
    boxlayout->addItem(new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 3);
    boxlayout->setHorizontalSpacing(1);
    boxlayout->setVerticalSpacing(1);
    boxlayout->setMargin(1);
    QWidget *widge = new QWidget;
    widge->setLayout(boxlayout);

    m_toolbox->addItem(widge, tr("Controls"));

    m_toolbox->addItem(createToolboxButton(QIcon(), tr("test")), tr("Modules"));
    m_toolbox->setMinimumWidth(widge->width());
}

void nwmMainWindow::SetupToolbar()
{
    m_mainbar->addAction(QIcon(":/images/new.png"), tr("New Setup"));
    m_mainbar->addAction(QIcon(":/images/open.png"), tr("Load Setup"));
    m_mainbar->addAction(QIcon(":/images/save.png"), tr("Save Setup"));
    m_mainbar->addSeparator();
    m_mainbar->addAction(QIcon(":/images/main/printer.png"), tr("Print Main Viewport"));
    m_mainbar->addAction(QIcon(":/images/main/find.png"), tr("Find Variable"));
    m_mainbar->addAction(QIcon(":/images/main/redo.png"), tr("Redo Last Action"));
    m_mainbar->addAction(QIcon(":/images/main/undo.png"), tr("Undo Last Action"));
    m_mainbar->addSeparator();
    m_mainbar->addAction(QIcon(":/images/main/plugin.png"), tr("Load Plugin"));
    m_mainbar->addAction(QIcon(":/images/main/functions.png"), tr("View Function List"));
    m_mainbar->addAction(QIcon(":/images/main/devices.png"), tr("Edit Device List"));
    m_mainbar->addAction(QIcon(":/images/main/triggers.png"), tr("Open Trigger Editor"));
    m_mainbar->addSeparator();
    m_mainbar->addAction(QIcon(":/images/props.png"), tr("Property Browser"));
    m_mainbar->addAction(QIcon(":/images/pm/model.png"), tr("Process Model"));
    m_mainbar->addAction(QIcon(":/images/main/analyzer.png"), tr("Signal Analyzer"));
    m_mainbar->addSeparator();
    m_mainbar->addAction(QIcon(":/images/main/pref.png"), tr("Preferences"));
    m_mainbar->addAction(QIcon(":/images/main/sync.png"), tr("Sync"));
    m_mainbar->addSeparator();
    m_mainbar->addAction(QIcon(":/images/main/help.png"), tr("Help"));
}

void nwmMainWindow::SetupDockBar()
{
    m_dockbar = new QToolBar;
    m_dockbar->setMovable(false);
    m_dockbar->setFloatable(false);
    m_dockbar->setOrientation(Qt::Vertical);
    m_dockbar->setAllowedAreas(Qt::RightToolBarArea);

    QDockButton *a = new QDockButton(tr("Properties"));
    a->setCheckable(true);
    a->setOrientation(Qt::Vertical);
    a->setMaximumWidth(24);
    m_dockbar->addWidget(a);

    QDockButton *b = new QDockButton(tr("Overlays"));
    b->setCheckable(true);
    b->setOrientation(Qt::Vertical);
    b->setMaximumWidth(24);
    m_dockbar->addWidget(b);

    m_dockbar->setContextMenuPolicy(Qt::NoContextMenu);
    addToolBar(Qt::RightToolBarArea, m_dockbar);
    insertToolBarBreak(m_dockbar);

    SetupDocks();

    QObject::connect(a, SIGNAL(clicked(bool)), m_Docks[0], SLOT(setVisible(bool)));
    QObject::connect(b, SIGNAL(clicked(bool)), m_Docks[1], SLOT(setVisible(bool)));

    // this translates the toggle view action into a signal (I'm not sure this is the best way to do this)
    QAction *acta = m_Docks[0]->toggleViewAction();
    QObject::connect(acta, SIGNAL(toggled(bool)), a, SLOT(setChecked(bool)));
    QAction *actb = m_Docks[1]->toggleViewAction();
    QObject::connect(actb, SIGNAL(toggled(bool)), b, SLOT(setChecked(bool)));
}

void nwmMainWindow::SetupMenus()
{
    m_menuFile = menuBar()->addMenu(tr("File"));
    m_menuEdit = menuBar()->addMenu(tr("Edit"));
    m_menuView = menuBar()->addMenu(tr("View"));

    m_menuEnvironment = menuBar()->addMenu(tr("Environment"));
    QAction *a0 = m_menuEnvironment->addAction(tr("Show Environment"));
    connect(a0, SIGNAL(triggered()), this, SLOT(showEnvironmentInDock()));

    m_menuPackages = menuBar()->addMenu(tr("Packages"));
    m_menuPackages->addAction(tr("Install New"));
    m_menuPackages->addAction(tr("Manage..."));
    m_menuPackages->addSeparator();
    m_menuPackages->addMenu(tr("Physics"));
    m_menuPackages->addMenu(tr("Engineering"));
    m_menuPackages->addMenu(tr("Communication"));
    m_menuPackages->addMenu(tr("Audio"));
    m_menuPackages->addMenu(tr("Other"));
    m_menuPackages->addMenu(tr("User Defined"));

    m_menuWindow = menuBar()->addMenu(tr("Window"));
    m_menuHelp = menuBar()->addMenu(tr("Help"));
}

/*
typedef struct __nwm_environment {
    char name[64];
    dpl_generic value;
    unsigned int flags;
} nwm_environment;
*/

void nwmMainWindow::showEnvironmentInDock()
{

    m_Docks[0]->setWindowTitle(tr("Environment"));
    m_Docks[0]->show();
}

void nwmMainWindow::SetupDocks()
{
    m_dockGridProps = new QTreeView;
    m_dockProps = new nwmPropertyWidget;

    m_Docks[0] = new QDockWidget(tr("Grid Properties"), this);
    m_Docks[0]->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_Docks[0]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    m_Docks[0]->setWidget(m_dockProps);
    addDockWidget(Qt::RightDockWidgetArea, m_Docks[0]);


    m_Docks[1] = new QDockWidget(tr("Overlays"), this);
    m_Docks[1]->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_Docks[1]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    m_dockOverlays = new QListWidget(m_Docks[1]);
    m_Docks[1]->setWidget(m_dockOverlays);
    tabifyDockWidget(m_Docks[0], m_Docks[1]);

    m_Docks[2] = new QDockWidget(tr("Output"), this);
    m_Docks[2]->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    m_Docks[2]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    m_dockOutput = new nwmOutputDock(m_Docks[2]);
    m_Docks[2]->setWidget(m_dockOutput);
    addDockWidget(Qt::BottomDockWidgetArea, m_Docks[2]);

    m_Docks[3] = new QDockWidget(tr("Results"), this);
    m_Docks[3]->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    m_Docks[3]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    m_dockResults = new nwmResultsWidget(m_Docks[3]);
    m_dockResults->view()->setScene(m_sceneResults);
    m_Docks[3]->setWidget(m_dockResults);
    tabifyDockWidget(m_Docks[2], m_Docks[3]);

    m_Docks[4] = new QDockWidget(tr("Editor"), this);
    m_Docks[4]->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    m_Docks[4]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    m_dockEditor = new nwmTriggerEditorWidget(m_Docks[4]);
    m_Docks[4]->setWidget(m_dockEditor);
    tabifyDockWidget(m_Docks[3], m_Docks[4]);

    m_Docks[2]->raise();
}

#include <QtGui>
#include "nwmapp.h"
#include "nwmrenderwidget.h"
#include "nwmcomponentwidget.h"

nwmRenderWidget::nwmRenderWidget()
{
    m_Toolbar = new QToolBar;
    m_btnResult = new QPushButton;
    m_ContentCombo = new QComboBox;
    m_ComponentBox = new QGroupBox;
    QGridLayout *layout = new QGridLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    m_Views = new QStackedLayout;
    m_useOnly = -1;
    z_safe = false;

    // define layouts
    layout->setMargin(1);
    layout->setHorizontalSpacing(2);
    layout->setVerticalSpacing(2);

    hlayout->setMargin(0);
    hlayout->setSpacing(2);

    m_ContentCombo->setMinimumHeight(28);

    // setup views
    setupPM();
    setupDAG();
    setupPreferences();

    // setup default buttons
    m_DefaultButtons[0] = new QAction(QIcon(":/images/decouple.png"), tr("Decouple"), this);
    m_DefaultButtons[0]->setCheckable(true);
    m_DefaultButtons[0]->setStatusTip(tr("Decouple the viewport from the main window"));
    m_DefaultButtons[1] = new QAction(QIcon(":/images/refresh.png"), tr("Refresh"), this);
    m_DefaultButtons[1]->setStatusTip(tr("Refresh current viewport"));
    m_DefaultButtons[2] = new QAction(QIcon(":/images/props.png"), tr("Properties"), this);
    m_DefaultButtons[2]->setStatusTip(tr("Show viewport properties"));

    // setup toolbar
    m_ComboAction = m_Toolbar->addWidget(m_ContentCombo);
    m_Toolbar->addAction(m_DefaultButtons[0]);
    PopulateToolbar();

    // setup error button
    m_btnResult->setIcon(QIcon(":/images/success.png"));
    m_btnResult->setIconSize(QSize(16, 16));
    m_btnResult->setFixedSize(32, 32);

    // setup component box
    m_ComponentBox->setTitle(tr("math.add"));
    m_ComponentBox->setLayout(m_Components);
    //m_ComponentBox->setLayout();

    // populate layouts
    hlayout->addWidget(m_Toolbar);
    hlayout->addWidget(m_btnResult);

    layout->addLayout(hlayout, 1, 0);
    layout->addLayout(m_Views, 0, 0);
    //layout->addWidget(m_Render, 0, 0);

    // initialize
    setLayout(layout);
    Rerender(0);

    // attach connections
    connect(m_ContentCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(Rerender(int)));
    connect(m_ContentCombo, SIGNAL(activated(int)), m_Views, SLOT(setCurrentIndex(int)));

    connect(m_DefaultButtons[1], SIGNAL(triggered()), m_Render, SLOT(update()));
    connect(m_DefaultButtons[0], SIGNAL(triggered(bool)), this, SLOT(Dock(bool)));
    connect(m_DefaultButtons[2], SIGNAL(triggered()), this, SLOT(showProps()));
}

void nwmRenderWidget::setupPM()
{
    QSplitter *slayout = new QSplitter(this);

    m_Render = new nwmRender;
    m_Components = new nwmComponentWidget;

    slayout->addWidget(m_Render);
    slayout->addWidget(m_ComponentBox);

    slayout->setCollapsible(0, false);

    m_ContentCombo->addItem(tr("Process Model"));

    m_Views->addWidget(slayout);
}

void nwmRenderWidget::setupDAG()
{
    m_DAG = new QGraphicsView;
    m_DAG->setRenderHint(QPainter::Antialiasing, false);
    m_DAG->setDragMode(QGraphicsView::RubberBandDrag);
    m_DAG->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_DAG->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);


    QGroupBox *groupBox = new QGroupBox("Contact Details");
    QLabel *numberLabel = new QLabel("Telephone number");
    QLineEdit *numberEdit = new QLineEdit;

    QFormLayout *layout = new QFormLayout;
    layout->addRow(numberLabel, numberEdit);
    groupBox->setLayout(layout);

    QGraphicsScene *scene =  new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    QGraphicsProxyWidget *proxy = scene->addWidget(groupBox);
    proxy->setPos(100, 100);

    m_DAG->setScene(scene);


    m_ContentCombo->addItem(tr("Directed Acyclic Graph"));

    m_Views->addWidget(m_DAG);
}

void nwmRenderWidget::setupPreferences()
{
    m_Preferences = new QGroupBox;
    m_Preferences->setTitle(tr("Preferences"));

    m_ContentCombo->addItem(tr("Preferences"));

    m_Views->addWidget(m_Preferences);
}

void nwmRenderWidget::showProps()
{
    QList<nwmProperty> props;
    nwmProperty p;

    p.setting = tr("Background Color");
    p.val = tr("RGB(115,115,115)");
    props.append(p);

    p.setting = tr("Grid Color");
    p.val = tr("RGB(105,105,105)");
    props.append(p);

    //theApp->PropertiesLoadAndShow(props, m_ContentCombo->currentText());
}

void nwmRenderWidget::Dock(bool d)
{
    int index = m_ContentCombo->currentIndex();
    static nwmRenderWidget *z;
    if (d) {
        z = new nwmRenderWidget;
        z_safe = true;
        z->setUseOnly(index);

//        index++;
//        if (index >= m_ContentCombo->count()) index = 0;
//        m_ContentCombo->setCurrentIndex(index);
//        Rerender(index);

        z->show();
    } else {
        z->hide();
        if (z_safe) delete z;
        z_safe = false;
    }
}

void nwmRenderWidget::setUseOnly(int n)
{
    m_useOnly = n;
    Rerender(n);
}

void nwmRenderWidget::Rerender(int index)
{
    m_Toolbar->clear();
    m_Render->update();
    QAction *cpt;

    if (m_useOnly == -1) {
        m_Toolbar->addAction(m_ComboAction);
        m_Toolbar->addAction(m_DefaultButtons[0]);
    }
    PopulateToolbar();

    switch (index) {
    case 0:
        cpt = m_Toolbar->addAction(QIcon(":/images/pm/edit.png"), tr("Edit Component"));
        m_Toolbar->addAction(QIcon(":/images/pm/vector.png"), tr("Edit Connection"));
        m_Toolbar->addSeparator();
        m_Toolbar->addAction(QIcon(":/images/build.png"), tr("Build"));
        m_Toolbar->addAction(QIcon(":/images/pm/simulate.png"), tr("Run Simulation"));
        m_Toolbar->addAction(QIcon(":/images/pm/optimize.png"), tr("Optimize"));
        m_Toolbar->addAction(QIcon(":/images/pm/timings.png"), tr("Timing Diagram"));
        m_Toolbar->addSeparator();
        m_Toolbar->addAction(QIcon(":/images/pm/dag.png"), tr("View Directed Acyclic Graph"));
        m_Toolbar->addAction(QIcon(":/images/pm/model.png"), tr("View Process Model"));
        m_Toolbar->addAction(QIcon(":/images/pm/zoom.png"), tr("Zoom Extents"));

        cpt->setCheckable(true);
        cpt->setChecked(true);
        connect(cpt, SIGNAL(toggled(bool)), m_ComponentBox, SLOT(setVisible(bool)));
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

void nwmRenderWidget::PopulateToolbar()
{
    m_Toolbar->addAction(m_DefaultButtons[1]);
    m_Toolbar->addAction(m_DefaultButtons[2]);
    m_Toolbar->addSeparator();
}

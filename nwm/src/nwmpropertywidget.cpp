#include <QtGui>
#include "nwmapp.h"
#include "nwmpropertywidget.h"

nwmPropertyWidget::nwmPropertyWidget(QWidget *parent) :
    QWidget(parent)
{
    m_View = new QTreeView;
    m_Toolbar = new QToolBar;
    m_Form = new QGroupBox;

    ilayout = new QVBoxLayout;
    flayout = new QFormLayout;

    m_Submit = new QDialogButtonBox;
    m_Name = new QLineEdit;
    m_Value = new QLineEdit;
    m_Desc = new nwmPropDescriptionTextEdit;
    m_Submit->addButton(tr("Create"), QDialogButtonBox::AcceptRole);
    m_Submit->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);

    m_View->setModel(theApp->m_Model);
    /* Find the "Grid" variable off root and show its properties.
       If the given variable is not found immediately off the given parent,
       the the entire tree is displayed
    */
    m_View->setRootIndex(theApp->m_Model->findChildVariable(tr("grid")));

    /* we can ignore headerData and set our own like this */
    QStandardItemModel *hm = new QStandardItemModel(1, 2);
    hm->setHeaderData(0, Qt::Horizontal, tr("Variable Name"), Qt::DisplayRole);
    hm->setHeaderData(1, Qt::Horizontal, tr("Value"), Qt::DisplayRole);
    QHeaderView *hv = new QHeaderView(Qt::Horizontal);
    hv->setModel(hm);

    m_View->setHeader(hv);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(2);

    ilayout->setSpacing(2);
    ilayout->setMargin(1);

    ilayout->addWidget(m_View, 2);
    flayout->addRow(new QLabel(tr("Name")), m_Name);
    flayout->addRow(new QLabel(tr("Value")), m_Value);
    flayout->addRow(new QLabel(tr("Description")), m_Desc);
    //flayout->addRow(m_Submit);
    mainLayout->addLayout(flayout);
    mainLayout->addWidget(m_Submit);
    m_Form->setLayout(mainLayout);

    m_Toolbar->addAction(QIcon(":/images/props/add.png"), tr("Add Result Box"));
    QAction *a = m_Toolbar->addAction(QIcon(":/images/props/edit.png"), tr("Create Variable"));
    m_Toolbar->addAction(QIcon(":/images/cross.png"), tr("Delete Variable"));

    ilayout->addWidget(m_Form);
    ilayout->addWidget(m_Toolbar);
    m_Form->hide();

    a->setCheckable(true);
    connect(a, SIGNAL(triggered(bool)), m_Form, SLOT(setVisible(bool)));
    connect(m_Submit, SIGNAL(rejected()), a, SLOT(toggle()));

    connect(m_Submit, SIGNAL(rejected()), m_Form, SLOT(hide()));
    connect(m_Submit, SIGNAL(rejected()), m_Name, SLOT(clear()));
    connect(m_Submit, SIGNAL(rejected()), m_Value, SLOT(clear()));
    connect(m_Submit, SIGNAL(rejected()), m_Desc, SLOT(clear()));

    setLayout(ilayout);
}

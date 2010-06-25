#include <QtGui>
#include "nwmoutputdock.h"

nwmOutputDock::nwmOutputDock(QWidget *parent) : QWidget(parent)
{
    m_Output = new nwmListWidget;
    m_Toolbar = new QToolBar;
    QGridLayout *layout = new QGridLayout;

    layout->setMargin(1);
    layout->setHorizontalSpacing(2);
    layout->setVerticalSpacing(2);

    PopulateToolbar();

    layout->addWidget(m_Output, 1, 0);
    layout->addWidget(m_Toolbar, 0, 0);

    m_Output->addItem(tr("Line 1"));
    m_Output->addItem(tr("Line 2"));
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/warning.png"), tr("Warning: Ambiguous logic."));
    m_Output->addItem(item);

    setLayout(layout);
}

void nwmOutputDock::save()
{
    int i;
    QDateTime *time = new QDateTime(QDateTime::currentDateTime());
    QString fname = "output-";
    QListWidgetItem *item;

    fname.append(time->toString(tr("yyyy-MM-dd_hhmmss")));
    fname.append(tr(".txt"));
    QFile *file = new QFile(fname);
    file->open(QIODevice::WriteOnly);

    for (i = 0; i < m_Output->count(); i++) {
        item = m_Output->item(i);
        file->write(item->text().toLatin1());
        file->write("\n");
    }

    file->close();
    delete file;
    delete time;
}

void nwmOutputDock::PopulateToolbar()
{
    //m_Toolbar->addAction(m_Output->clear())
    QAction *a = m_Toolbar->addAction(QIcon(":/images/cross.png"), tr("Clear"));
    QAction *b = m_Toolbar->addAction(QIcon(":/images/save.png"), tr("Save"));

    connect(a, SIGNAL(triggered()), m_Output, SLOT(clear()));
    connect(b, SIGNAL(triggered()), this, SLOT(save()));
}

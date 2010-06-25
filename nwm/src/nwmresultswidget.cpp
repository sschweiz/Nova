#include <QtGui>
#include "nwmresultswidget.h"

nwmResultsWidget::nwmResultsWidget(QWidget *parent) : QWidget(parent)
{
    m_View = new QGraphicsView;
    m_View->setRenderHint(QPainter::Antialiasing, false);
    m_View->setDragMode(QGraphicsView::RubberBandDrag);
    m_View->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_View->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    m_Toolbar = new QToolBar;
    QGridLayout *layout = new QGridLayout;

    layout->setMargin(1);
    layout->setHorizontalSpacing(2);
    layout->setVerticalSpacing(2);

    layout->addWidget(m_View, 1, 0);
    layout->addWidget(m_Toolbar, 0, 0);

    setLayout(layout);
}

QGraphicsView *nwmResultsWidget::view() const
{
    return m_View;
}

#ifndef NWMRESULTSWIDGET_H
#define NWMRESULTSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QToolBar;
class QGraphicsView;
QT_END_NAMESPACE

class nwmResultsWidget : public QWidget
{
Q_OBJECT

public:
    nwmResultsWidget(QWidget *parent = 0);

    QGraphicsView *view() const;

private:
    QGraphicsView *m_View;
    QToolBar *m_Toolbar;
};

#endif // NWMRESULTSWIDGET_H

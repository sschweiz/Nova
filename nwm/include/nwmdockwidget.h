#ifndef NWMDOCKWIDGET_H
#define NWMDOCKWIDGET_H

#include <QDockWidget>

class nwmDockWidget : public QDockWidget
{
public:
    nwmDockWidget();

protected:
    void closeEvent(QCloseEvent * event);

//signals:
//    void onClose();
};

#endif // NWMDOCKWIDGET_H

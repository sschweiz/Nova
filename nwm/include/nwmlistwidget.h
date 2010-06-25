#ifndef NWMLISTWIDGET_H
#define NWMLISTWIDGET_H

#include <QListWidget>

class nwmListWidget : public QListWidget
{
public:
    nwmListWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
};

#endif // NWMLISTWIDGET_H

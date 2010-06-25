#include "nwmlistwidget.h"

nwmListWidget::nwmListWidget()
{
}

QSize nwmListWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize nwmListWidget::sizeHint() const
{
    return QSize(300, 100);
}

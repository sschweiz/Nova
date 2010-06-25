#include "qdockbutton.h"

#include <QStylePainter>
#include <QMenu>

QDockButton::QDockButton(QWidget* parent)
: QPushButton(parent)
{
    init();
}

QDockButton::QDockButton(const QString& text, QWidget* parent)
: QPushButton(text, parent)
{
    init();
}

QDockButton::QDockButton(const QIcon& icon, const QString& text, QWidget* parent)
: QPushButton(icon, text, parent)
{
    init();
}

QDockButton::~QDockButton()
{
}

void QDockButton::init()
{
    orientation_ = Qt::Horizontal;
    mirrored_ = false;
}

Qt::Orientation QDockButton::orientation() const
{
    return orientation_;
}

void QDockButton::setOrientation(Qt::Orientation orientation)
{
    orientation_ = orientation;
    switch (orientation)
    {
    case Qt::Horizontal:
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        break;

    case Qt::Vertical:
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        break;
    }
}

bool QDockButton::mirrored() const
{
    return mirrored_;
}

void QDockButton::setMirrored(bool mirrored)
{
    mirrored_ = mirrored;
}

QSize QDockButton::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    if (orientation_ == Qt::Vertical)
        size.transpose();
    return size;
}

QSize QDockButton::minimumSizeHint() const
{
    QSize size = QPushButton::minimumSizeHint();
    if (orientation_ == Qt::Vertical)
        size.transpose();
    return size;
}

void QDockButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStylePainter p(this);

    switch (orientation_)
    {
    case Qt::Horizontal:
        if (mirrored_)
        {
            p.rotate(180);
            p.translate(-width(), -height());
        }
        break;

    case Qt::Vertical:
        if (mirrored_)
        {
            p.rotate(-90);
            p.translate(-height(), 0);
        }
        else
        {
            p.rotate(90);
            p.translate(0, -width());
        }
        break;
    }

    p.drawControl(QStyle::CE_PushButton, getStyleOption());
}

QStyleOptionButton QDockButton::getStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);
    if (orientation_ == Qt::Vertical)
    {
        QSize size = opt.rect.size();
        size.transpose();
        opt.rect.setSize(size);
    }
    opt.features = QStyleOptionButton::None;
    if (isFlat())
        opt.features |= QStyleOptionButton::Flat;
    if (menu())
        opt.features |= QStyleOptionButton::HasMenu;
    if (autoDefault() || isDefault())
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    if (isDefault())
        opt.features |= QStyleOptionButton::DefaultButton;
    if (isDown() || (menu() && menu()->isVisible()))
        opt.state |= QStyle::State_Sunken;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (!isFlat() && !isDown())
        opt.state |= QStyle::State_Raised;
    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}

/**
  From:
  http://www.qtcentre.org/wiki/index.php?title=OrientationButton
 */

#ifndef QDOCKBUTTON_H
#define QDOCKBUTTON_H

#include <QPushButton>
#include <QStyleOptionButton>

class QDockButton : public QPushButton
{
public:
    QDockButton(QWidget* parent = 0);
    QDockButton(const QString& text, QWidget* parent = 0);
    QDockButton(const QIcon& icon, const QString& text, QWidget* parent = 0);
    ~QDockButton();

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    bool mirrored() const;
    void setMirrored(bool mirrored);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    QStyleOptionButton getStyleOption() const;
    void init();

    Qt::Orientation orientation_;
    bool mirrored_;
};

#endif // QDOCKBUTTON_H

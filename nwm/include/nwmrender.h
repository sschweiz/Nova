#ifndef NWMRENDER_H
#define NWMRENDER_H

#include <QGLWidget>

class nwmRender : public QGLWidget
{
    Q_OBJECT

public:
    nwmRender(QWidget *parent = 0);
    ~nwmRender();

    int m_width, m_height;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void setFromQColor(const QColor &color);
};

#endif // NWMRENDER_H

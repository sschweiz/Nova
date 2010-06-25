#include "nwmrender.h"
#include "nwmapp.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

nwmRender::nwmRender(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

nwmRender::~nwmRender()
{
}

QSize nwmRender::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize nwmRender::sizeHint() const
{
    return QSize(800, 480);
}

void nwmRender::setFromQColor(const QColor &color)
{
    glColor4ub(color.red(), color.green(), color.blue(), color.alpha());
}

void nwmRender::initializeGL()
{
    /*
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    */
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(1, 1, 1, 1);
}

void nwmRender::paintGL()
{
    int x, y;
    QColor cc = theApp->lookupValue(tr("grid.bg_color")).value<QColor>();
    glClearColor(cc.redF(), cc.greenF(), cc.blueF(), 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();

    //glGetIntegerv(GL_VIEWPORT, scissor);
    //glScissor(); // set
    //glScissor(scissor[0], scissor[1], scissor[2], scissor[3]); // restore

    /* grid */
    glBegin(GL_LINES);
    //glColor4f(0.41, 0.41, 0.41, 1);
    cc = theApp->lookupValue(tr("grid.grid_color")).value<QColor>();
    glColor4f(cc.redF(), cc.greenF(), cc.blueF(), 1);
    for (x = 0; x < m_width; x+=25) {
            glVertex2i(x, 0);
            glVertex2i(x, m_height);
    }
    for (y = 0; y < m_height; y+=25) {
            glVertex2i(0, y);
            glVertex2i(m_width, y);
    }
    glEnd();

    glFlush();
}

void nwmRender::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    m_width = width;
    m_height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void nwmRender::mousePressEvent(QMouseEvent *event)
{
}

void nwmRender::mouseMoveEvent(QMouseEvent *event)
{
//     int dx = event->x();
//     int dy = event->y();
//    updateGL();
}

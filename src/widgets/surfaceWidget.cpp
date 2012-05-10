#include "surfaceWidget.h"

//#include <GL/glut.h>
#include <QtOpenGL>
#include <QMouseEvent>

const QString SurfaceWidget::TAG = QString("SurfaceWidget");

/**
 *
 */
SurfaceWidget::SurfaceWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
}

/**
 *
 */
void SurfaceWidget::initializeGL()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

/**
 *
 */
void SurfaceWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    qDebug() << w << h;
}

/**
 *
 */
void SurfaceWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(100,500);
    glVertex2f(500,100);
    glEnd();
}

/**
 *
 */
void SurfaceWidget::mousePressEvent(QMouseEvent *event)
{

}

/**
 *
 */
void SurfaceWidget::mouseMoveEvent(QMouseEvent *event)
{
    QLOG_TRACE() << TAG << event->x() << event->y();
}

/**
 *
 */
void SurfaceWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

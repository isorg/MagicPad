#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QsLog.h>

#include <QtOpenGL>

#include <opencv2/opencv.hpp>

/**
 *
 */
class SurfaceWidget : public QGLWidget
{

    Q_OBJECT

public:

    static const QString TAG;

    SurfaceWidget(QWidget *parent = 0);

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:

private:

};

#endif // VUMETER_H

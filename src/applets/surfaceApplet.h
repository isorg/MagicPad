#ifndef SURFACEAPPLET_H
#define SURFACEAPPLET_H

#include "applet.h"

#include <QPainter>

#include "filters/calibrationFilter.h"

#define SURFACE_NAME "surface"
#define SURFACE_TITLE "Surface"

/**
 *
 */
class SurfaceApplet : public Applet
{

    Q_OBJECT

public:

    static const QString TAG;

    SurfaceApplet(QWidget *parent = 0);

public slots:

    void setFrame( cv::Mat& frame );

    void paintEvent(QPaintEvent *) {
        QPainter painter( this );
        painter.fillRect( rect(), Qt::red );
    }

private:
    void allocateData();

    void setupSurface();

private:

    CalibrationFilter *mCalibrationFilter;
};

#endif // SURFACEAPPLET_H

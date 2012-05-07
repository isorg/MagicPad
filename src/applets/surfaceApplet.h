#ifndef SURFACEAPPLET_H
#define SURFACEAPPLET_H

#include "applet.h"

#include "filters/calibrationFilter.h"

#include <qwt3d_surfaceplot.h>
#include <qwt3d_function.h>

#define SURFACE_NAME "surface"
#define SURFACE_TITLE "Surface"

#define SURFACE_UPSCALING_FACTOR 3

#define SURFACE_PLOTFACTOR 20

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
    // algo
    CalibrationFilter *mCalibrationFilter;
    cv::Mat mFrame;
    cv::Mat mFrameFiltered;
    cv::Mat mFrameDouble;
    cv::Mat mHighResFrame;

    // view
    Qwt3D::SurfacePlot *mSurface;
    Qwt3D::ColorVector mColorVector;
    double **mTable;
    int m_hrWidth;
    int m_hrHeight;
};

#endif // SURFACEAPPLET_H

#ifndef SURFACEAPPLET_H
#define SURFACEAPPLET_H

#include "applet.h"

#include "filters/calibrationFilter.h"

#include "widgets/surfaceWidget.h"

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

private:

private:

    CalibrationFilter *mCalibrationFilter;

    SurfaceWidget *mSurfaceWidget;
};

#endif // SURFACEAPPLET_H

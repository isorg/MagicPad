#include "surfaceApplet.h"

const QString SurfaceApplet::TAG = QString("SurfaceApplet");

/**
 *
 */
SurfaceApplet::SurfaceApplet(QWidget *parent) : Applet(parent)
{
    mName = SURFACE_NAME;
    mTitle = SURFACE_TITLE;

    // load description, marketing and technical text from
    // xml file. Ensure that mName is set before calling this function
    loadTextFromXml();

    // Pipeline
    mCalibrationFilter = new CalibrationFilter();

}

/**
 *
 */
void SurfaceApplet::setFrame( cv::Mat& frame )
{
    // Filter pipeline
    mCalibrationFilter->setFrame( frame );
    mCalibrationFilter->process();
}

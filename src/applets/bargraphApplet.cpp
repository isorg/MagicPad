#include "bargraphApplet.h"

const QString BargraphApplet::TAG = QString("BargraphApplet");

/**
 *
 */
BargraphApplet::BargraphApplet(QWidget *parent) :
    Applet( parent )
{
    mName = BARGRAPH_NAME;
    mTitle = BARGRAPH_TITLE;

    // load description, marketing and technical text from
    // xml file. Ensure that mName is set before calling this function
    loadTextFromXml();

    // Build filter pipeline
    mCalibrationFilter = new CalibrationFilter( this );
}

/**
 *
 */
void BargraphApplet::setFrame( cv::Mat& frame )
{
    mCalibrationFilter->setFrame( frame );
    mCalibrationFilter->process();

    update();
}

#include "surfaceApplet.h"

#include <QVBoxLayout>

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
    mCalibrationFilter = new CalibrationFilter( this );

    // User interface
    QVBoxLayout *layout = new QVBoxLayout( this );
    mSurfaceWidget = new SurfaceWidget( this );
    layout->addWidget( mSurfaceWidget );

    // Gestures
    GestureType ges[GESTURE_NUMBER];
    ges[0] = SWAP_ALL;
    setGestures(ges);
}

/**
 *
 */
void SurfaceApplet::setFrame( cv::Mat& frame )
{
    // Filter pipeline
    mCalibrationFilter->setFrame( frame );
    mCalibrationFilter->process();

    mSurfaceWidget->setFrame( mCalibrationFilter->getCalibratedFrame() );

    update();
}

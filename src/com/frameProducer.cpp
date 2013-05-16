#include "frameProducer.h"

/**
 * Constructor
 */
FrameProducer::FrameProducer()
{
    mDevice = NULL;
}

/**
 * This method is called once using thread->start();
 */
void FrameProducer::run()
{
    if( mDevice == NULL )
    {
        QLOG_ERROR() << "No device defined";
        return;
    }

    // Set framerate
    QTimer *timer = new QTimer( );
    timer->setInterval( mDevice->maxFramerate() );

    if( ! mDevice->connectDevice() )
    {
        QLOG_ERROR() << "Unable to connect to a GenericDevice";
    }

    connect( timer, SIGNAL( timeout() ), mDevice, SLOT( getDeviceFrame() ) );
    connect( mDevice, SIGNAL( newFrame( cv::Mat& ) ) , this, SLOT( getNewFrame( cv::Mat& ) ) );

    timer->start();

    // Run the event loop
    exec();
}

/**
 * Set the magicPad device
 */
void FrameProducer::setDevice( GenericDevice* device )
{
    mDevice = device;
}

/**
 *
 */
void FrameProducer::getNewFrame( cv::Mat& frame )
{
    emit newFrame( frame );
}

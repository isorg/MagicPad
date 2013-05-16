#ifndef FRAMEPRODUCER_H
#define FRAMEPRODUCER_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include "com/genericDevice.h"

/**
 *
 */
class FrameProducer : public QThread
{

    Q_OBJECT

public:

    FrameProducer();

    void run();

    void setDevice( GenericDevice* device );

signals:

    void newFrame( cv::Mat& frame );

public slots:

    void getNewFrame( cv::Mat& frame );

private:

    GenericDevice *mDevice;
};

#endif // FRAMEPRODUCER_H

#ifndef GENERICDEVICE_H
#define GENERICDEVICE_H

#include <QtCore>

#include <opencv2/opencv.hpp>

#include "QsLog.h"

/**
 * The GenericDevice class defines the common interface to all devices
 */
class GenericDevice : public QObject
{
    Q_OBJECT

public:

    GenericDevice( QObject *parent = 0) : QObject( parent ) { }

    // Connect the device
    virtual bool connectDevice() = 0;
    virtual void disconnectDevice() = 0;

    // Maximum supported framerate
    virtual int maxFramerate() = 0;

signals:

    // Emits last frame
    void newFrame( cv::Mat& frame );

public slots:

    // Request new frame
    virtual void getDeviceFrame() = 0;

private:

};

#endif // GENERICDEVICE_H

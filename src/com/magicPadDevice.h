#ifndef MAGICPADDEVICE_H
#define MAGICPADDEVICE_H

#include <QtCore>

#include "QsLog.h"

#include <opencv2/opencv.hpp>

#include "genericDevice.h"

#include "magicPadFrame.h"

#include <windows.h>
#include "ftd2xx.h"

#define MAGICPAD_BAUDRATE   115200

#define MAGICPAD_OLD_FIRMWARE

/**
 *
 */
class MagicPadId
{

public:

    MagicPadId()
    {
        name = "";
        comport = -1;
    }

    MagicPadId(int _port, const QString& _name)
    {
        name = _name;
        comport = _port;
    }

    QString name;
    int comport;

};


/**
 *
 */
class MagicPadDevice : public GenericDevice
{
    Q_OBJECT

public:

    MagicPadDevice( QObject *parent = 0 );

    // List all MagicPad devices that are connected
    QList<MagicPadId> listDevices();

    // Connect to a magicpad device
    bool setMagicPad( const MagicPadId& device )
    {
        mDeviceId = device;
    }

    bool connectDevice();

    void disconnectDevice();

    int maxFramerate() { return 40; }

protected:

    // List FTDI devices
    QList<MagicPadId> listDevicesFTDI();
    QList<MagicPadId> listDevicesBluetooth();

    // Check device integrity
    bool checkDevice( HANDLE& h );

    // Get device name
    QString getDeviceName( HANDLE& h );

    bool writeDevice( HANDLE& h, const char* data, long len );
    bool readDevice( HANDLE& h, char* data, long len );

    bool openComPort( LONG comport, HANDLE& h );
    bool readComPort();
    bool writeComPort();

    QString reportError( DWORD dwError );

signals:

    void newFrame( cv::Mat &frame );

public slots:

    void getDeviceFrame();

private:
    MagicPadId mDeviceId;
    HANDLE mDeviceHandle;
    QString TAG;

};

#endif // MAGICPADDEVICE_H

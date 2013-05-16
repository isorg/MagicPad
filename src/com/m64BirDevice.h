#ifndef M64BIRDEVICE_H
#define M64BIRDEVICE_H

#include "QsLog.h"
#include "genericDevice.h"
#include <usb.h>
#include <opencv2/opencv.hpp>

#define M64_DEVICE_VID 0x0483   // 0x04D8=Microchip, 0x0483=STMicro
#define M64_DEVICE_PID 0xF8BA   // 0x0204=PIDEM, 0xF8BA=Mircochip+ISORG

#define M64_EP_OUT 0x01
#define M64_EP_IN  0x81

#define M64_MANUFACTURER "ISORG"
#define M64_PRODUCT_NAME "Organic Multitouch Device"

/*
 * This is where the m64_frame_t structure is declared. The structure
 * contains the data to be sent to the host (PC). It is crucial that the size
 * of the structure be a multiple of 64 bytes. This is enforced by declaring
 * a dummy array 'fill' at the end of the structure.
 */
typedef struct {
    uint32_t frameId;       // incremented one-by-one
    uint32_t timestamp;     // real world time of the frame
    uint16_t img[256];      // image[line][column]
    uint8_t _fill[56];      // 64 bytes alignment at the end of the struct
} m64_frame_t;

/**
 *
 */
class M64BirDevice : public GenericDevice
{
    Q_OBJECT

public:

    M64BirDevice(QObject *parent = 0);

    bool findDevice();

    bool connectDevice();

    void disconnectDevice();

    int maxFramerate() { return 40; }

signals:

    void newFrame( cv::Mat& frame );

public slots:

    void getDeviceFrame();

private:

    QString mDeviceManufacturer;
    QString mDeviceProductName;
    usb_dev_handle *mDeviceHandle;
    struct usb_device *mDevice;
    QString TAG;

};

#endif // M64BIRDEVICE_H

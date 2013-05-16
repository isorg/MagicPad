#include "m64BirDevice.h"

/**
 * Constructor
 */
M64BirDevice::M64BirDevice(QObject *parent)
    : GenericDevice( parent ), TAG("M64BirDevice")
{
    mDevice = NULL;
    mDeviceHandle = NULL;
}

/**
 *
 */
bool M64BirDevice::connectDevice()
{
    int err;
    char str[100];

    // At this point device should point to a valid usb_device if a M64Bir was attached
    if( mDevice == NULL )
    {
        QLOG_ERROR() << "No M64BIR device defined: " << usb_strerror();
        return false;
    }

    // Open the USB device
    usb_dev_handle *handle = usb_open( mDevice );

    err = usb_set_configuration( handle, 1 );
    if( err < 0 )
    {
        QLOG_ERROR() << "usb_set_configuration() returned " << usb_strerror();
        usb_close( handle );
        return false;
    }

    err = usb_claim_interface( handle, 0 );
    if( err < 0 )
    {
        QLOG_ERROR() << "usb_claim_interface() returned " << usb_strerror();
        usb_close( handle );
        return false;
    }

    mDeviceHandle = handle;

    // Print device information
    if( mDevice->descriptor.iManufacturer )
    {
        err = usb_get_string_simple( mDeviceHandle, mDevice->descriptor.iManufacturer, str, sizeof(str) );
        if( err > 0 )
        {
            mDeviceManufacturer = str;
            QLOG_INFO() << "Manufacturer is " << mDeviceManufacturer;
        }
    }
    if( mDevice->descriptor.iProduct )
    {
        err = usb_get_string_simple( mDeviceHandle, mDevice->descriptor.iProduct, str, sizeof(str) );
        if( err > 0 )
        {
            mDeviceProductName = str;
            QLOG_INFO() << "Product is " << mDeviceProductName;
        }
    }

    return true;
}

/**
 * Disconnect from current device
 */
void M64BirDevice::disconnectDevice()
{
    usb_release_interface( mDeviceHandle, 0 );
    if( mDeviceHandle != NULL )
    {
        usb_close( mDeviceHandle );
    }
}

/**
 * Find all M64BirDevice connected
 */
bool M64BirDevice::findDevice()
{
    mDevice = NULL;

    // Find all busses and devices
    usb_init();
    usb_find_busses();
    usb_find_devices();

    // list all the USB busses
    struct usb_bus *busses = usb_get_busses();

    // browse through USB busses, through each devices and look for a device that match the VID/PID
    for(struct usb_bus *bus = busses; bus != NULL; bus = bus->next)
    {
        for(struct usb_device *dev = bus->devices; dev != NULL; dev = dev->next)
        {
            if( dev->descriptor.idVendor == M64_DEVICE_VID && dev->descriptor.idProduct == M64_DEVICE_PID )
            {
                mDevice = dev;
            }
        }
    }

    if( mDevice != NULL )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *
 */
void M64BirDevice::getDeviceFrame()
{
    char buffer[1];         // buffer for the 'read command'
    m64_frame_t myFrame;    // storage structure, this should be an attribute of the
                            // class and not a local variable.
    int ret;                // nb of bytes written or read

    if( mDeviceHandle == NULL )
    {
        QLOG_ERROR() << "mDeviceHandle not defined";
        return;
    }

    //
    // Step 1 - send the 'read command'
    // Send 'read M64Bir Device opd values' command
    //
    buffer[0] = 'A';
    ret = usb_bulk_write( mDeviceHandle, M64_EP_OUT, buffer, 1, 1000);
    if( ret < 0 )
    {
        QLOG_WARN() << "Error writting: " << usb_strerror();
        return;
    }

    //
    // Step 2 - Read the data
    //
    ret = usb_bulk_read( mDeviceHandle, M64_EP_IN, (char *)&myFrame, sizeof(m64_frame_t), 1000);
    if( ret != sizeof(m64_frame_t) )
    {
        QLOG_WARN() << "ERROR: read" << ret << "bytes instead of" << sizeof(m64_frame_t);
    }

    if( ret < 0 )
    {
        QLOG_WARN() << "Error reading: " << usb_strerror();
        return;
    }

    //
    // Build OpenCV frame here
    //
    cv::Mat data( 16, 16, CV_16U );

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            data.at< unsigned short int >( i, j ) = myFrame.img[ i*16 + j ];
        }
    }

    emit newFrame( data );

}

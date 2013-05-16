#ifndef MAGICPADFRAME_H
#define MAGICPADFRAME_H

#include <opencv2/opencv.hpp>

#include <QtCore>

typedef enum {
    MAGICPAD,
    M64BIR
} OriginDevice ;

/**
 *
 */
class MagicPadFrame
{
public:
    MagicPadFrame()
    {
        img = cv::Mat(10, 10, CV_8U);
        timestamp = 0;
        origin = MAGICPAD;
    }

    MagicPadFrame(unsigned char *data, long unsigned int _timestamp = 0)
    {
        img = cv::Mat(10, 10, CV_8U, data);
        timestamp = _timestamp;
    }

    MagicPadFrame(cv::Mat& _img, long unsigned int _timestamp = 0)
    {
        img = _img;
        timestamp = _timestamp;
    }

    cv::Mat img;
    long unsigned int timestamp;
    OriginDevice origin;


};

#endif // MAGICPADFRAME_H

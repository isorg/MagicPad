#ifndef BARGRAPHAPPLET_H
#define BARGRAPHAPPLET_H

#include <QtCore>
#include <QtGui>

#include "applet.h"

#include "filters/calibrationFilter.h"
#include "filters/objectDetectionFilter.h"
#include "filters/otsuFilter.h"

#define BARGRAPH_NAME "bargraph"
#define BARGRAPH_TITLE "Bargraph"

class BargraphApplet : public Applet
{
    Q_OBJECT

public:

    static const QString TAG;

    BargraphApplet(QWidget *parent = 0);

public slots:

    void setFrame( cv::Mat& frame );

private:
    CalibrationFilter *mCalibrationFilter;
    ObjectDetectionFilter *mDetectionFilter;
    OtsuFilter *mOtsuFilter;

    cv::Mat mHistory;
    cv::Mat mPrev;
    cv::Mat mMask;
    cv::Mat mMotion;

};

#endif // BARGRAPHAPPLET_H

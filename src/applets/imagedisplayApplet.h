#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QtCore>
#include <QtGui>

#include "applet.h"

#include "filters/calibrationFilter.h"

#define IMAGEDISPLAY_NAME "imagedisplay"
#define IMAGEDISPLAY_TITLE "Image Display"

class ImagedisplayApplet : public Applet
{
    Q_OBJECT

public:

    static const QString TAG;

    ImagedisplayApplet(QWidget *parent = 0);

    void setFrame( cv::Mat& frame );

public slots:

    void paintEvent(QPaintEvent *);

private:

    CalibrationFilter *mCalibrationFilter;

    cv::Mat mFrame;
};

#endif // IMAGEDISPLAY_H

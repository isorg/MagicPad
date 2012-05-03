#ifndef OPDAPPLET_H
#define OPDAPPLET_H

#include <QtCore>
#include <QtGui>

#include "applet.h"

#include "filters/calibrationFilter.h"

#define OPD_NAME "opd"
#define OPD_TITLE "Opd"

/**
 *
 */
class OpdApplet : public Applet
{
    Q_OBJECT
public:    
    static const QString TAG;

    OpdApplet(QWidget *parent = 0);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void paintEvent(QPaintEvent *);

    void setFrame( cv::Mat& frame );

    void reset();

private:
    CalibrationFilter *mCalibrationFilter;

    cv::Mat mRaw, mRef, mCal, mAlive;

    int mImageCounter;
};

#endif // OPDAPPLET_H

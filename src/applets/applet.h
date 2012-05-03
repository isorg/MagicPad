#ifndef APPLET_H
#define APPLET_H

#include <QtGui>
#include <QtXml>
#include "QsLog.h"

#include <opencv2/opencv.hpp>

#include "appletInterface.h"

// Type of application gesture
typedef enum {
    TWIST           = 0x00000001,
    SWAP_LEFT_RIGHT = 0x00000004,
    SWAP_BACK_FORTH = 0x00000008,
    SWAP_ALL        = 0x00000010,
    JOYSTICK        = 0x00000020,
    UP_DOWN         = 0x00000040,
    OBJECT          = 0x00000080,
    PRESS           = 0x00000100
    } GestureType;

/**
 *
 */
class Applet : public QWidget, public AppletInterface
{
    Q_OBJECT
    Q_INTERFACES( AppletInterface )

public:

    static const QString TAG;

    Applet(QWidget *parent = 0);

    // Applet identity
    virtual QString name() { return mName; }

    virtual QString title() { return mTitle; }

    virtual QPixmap icon();

    // Descriptive text
    virtual QString descriptionText() { return mDescription; }

    virtual QString marketingText() { return mMarketing; }

    virtual QString technicalText() { return mTechnical; }

    void setFrame( cv::Mat& frame ) = 0;

    virtual void hide() {
        QWidget::hide();
    }

    virtual void resize( const QSize& size ) {
        QWidget::resize( size );
    }

    virtual void show() {
        QWidget::show();
    }

    virtual void start() {}
    virtual void stop() {}

    virtual void setParent(QWidget *parent) {
        QWidget::setParent( parent );
    }

protected:

    void loadTextFromXml();

protected:
    QString mName;      // short name: no spaces
    QString mTitle;     // title displayed on home screen

    // Descriptive text
    QString mDescription;   // Complete description
    QString mMarketing;     // Advantages over competing products
    QString mTechnical;     // Technical details
};

#endif // APPLET_H

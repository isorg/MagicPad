#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QSettings>
#include <QWidget>

#include "version.h"

// Debug
#include "QsLog.h"

// Core
#include "actionBar.h"
#include "connectionDialog.h"
#include "loggerDialog.h"

// Com
#include "com/magicPad.h"
#include "com/frameProducer.h"

// GUI
#include "appletButton.h"
#include "actionButton.h"

// Applets
#include "applets/templateApplet.h"
#include "applets/alphabetApplet.h"
#include "applets/backlightApplet.h"
#include "applets/bargraphApplet.h"
#include "applets/bulbApplet.h"
#include "applets/DjApplet.h"
#include "applets/gestureApplet.h"
#include "applets/imagedisplayApplet.h"
#include "applets/mapsApplet.h"
#include "applets/musicApplet.h"
#include "applets/opdApplet.h"
#include "applets/pandaApplet.h"
#include "applets/pictureflowApplet.h"
#include "applets/purpleApplet.h"
#include "applets/rollingballApplet.h"
#include "applets/slideshowApplet.h"
#include "applets/surfaceApplet.h"
#include "applets/switchApplet.h"
#include "applets/twistApplet.h"
#include "applets/tyuuApplet.h"
#include "applets/vumeterApplet.h"

#define MAINWINDOW_APPLETGRID_NCOL  5

#define APPLICATION_SETTINGS_FILE "config.ini"

class View : public QGraphicsView
{

     Q_OBJECT

public:

     View(QGraphicsScene *scene) : QGraphicsView(scene)
     {
         //setViewport( new QGLWidget() );

         //setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
         //setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );

         // Anti-aliasing
         setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

         // (0,0) in the top left corner
         setAlignment(Qt::AlignLeft | Qt::AlignTop);

         // background image
         _bg.load(":image/metal.jpg");
         setBackgroundBrush( _bg );
         setCacheMode(QGraphicsView::CacheBackground);
     }

 protected:

     void resizeEvent(QResizeEvent *event)
     {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
     }

     QPixmap _bg;
 };

class MainWindow : public QWidget
{

    Q_OBJECT

public:

    static const QString TAG;

    MainWindow(QWidget *parent = 0);

    //~MainWindow() {}

public slots:
    // TODO: autostart applet if specified in config.ini
    //void autostart();

    void closeCurrentApplet();

    void closeCurrentAppletLater();

    void launchApplet(AppletInterface *applet);

    void setAppletText(AppletInterface *applet);

    void testevent(cv::Mat img) { qDebug() << __LINE__; }

signals:
    void goApplet();

private:
    void loadApplets(QGraphicsScene *scene);

    void loadSettings();

    void registerApplet(AppletInterface *applet);

    void setupUI();

private slots:

    void dispatchFrame( cv::Mat& frame ) {
        if( mCurrentApplet ) mCurrentApplet->setFrame( frame );
    }

private:
    // UI
    QGraphicsWidget *mAppletButtonGrid;
    QWidget *mAppletRect;
    QGraphicsTextItem *mText;
    QRectF mScreen;
    LoggerDialog *mLogger;

    AppletInterface *mCurrentApplet;
    FrameProducer *mProducer;
    QList< AppletInterface* > mApplets;
    QState *rootState;

    // Settings
    QSettings *mSettings;
    bool mShowLogger;
    bool mShowBack;
    bool mShowQuit;
    bool mShowText;

};

#endif // MAINWINDOW_H

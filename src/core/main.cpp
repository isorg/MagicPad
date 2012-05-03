#include <QtGui>
#include <QtCore>
#include <opencv2/opencv.hpp>

#include "QsLog.h"
#include "QsLogDest.h"

#include "mainwindow.h"
#include "version.h"

// Log file
#define APPLICATION_LOG_FILE "log.txt"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Splashscreen
    QPixmap pixmap(":/image/isorg.jpg");
    QSplashScreen splash( pixmap );
    splash.show();
    splash.showMessage( "Debug information" );

    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();

    logger.setLoggingLevel(QsLogging::TraceLevel);

    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath( APPLICATION_LOG_FILE ));

    QsLogging::DestinationPtr fileDestination(
        QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );

    QsLogging::DestinationPtr debugDestination(
        QsLogging::DestinationFactory::MakeDebugOutputDestination() );

    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    // Print program info: Version, Start time, ...
    QLOG_INFO() << "------------------------------------------------------------";
    QLOG_INFO() << QDateTime::currentDateTime().toString("yyyy-MM-dd @ hh:mm:ss")
                << "- MagicPad v" << MAGICPAD_VERSION_STR;

    splash.showMessage( "Building main application" );
    MainWindow w;
    w.show();

    // Hide splashscreen
    splash.finish( &w );
    
    return a.exec();
}


#include "applet.h"

#include <QtXml>

#define stringify( name ) # name

const QString Applet::TAG = QString("Applet");

/**
 *
 */
Applet::Applet(QWidget *parent) :
    QWidget(parent)
{
    mName = "defaultName";
    mTitle = "defaultTitle";
    mGestures[0] = TWIST;
}

/**
 * icon - return applet icon
 */
QPixmap Applet::icon()
{
    // default icon name is ":/icon/icon_myappletname.png"
    QString fname = ":image/icon_" + mName + ".png";

    QPixmap p;
    if( !p.load( fname ) ) {
        QLOG_ERROR() << TAG << "Unable to load icon for " + mName;
    }

    return p;
}

/**
 * acceptedGestures - return accepted gestures icon in ges
 */
void Applet::acceptedGestures(QPixmap * ges)
{
    //int size= sizeof mGestures/sizeof(GestureType);
    for (int i = 0 ; i < GESTURE_NUMBER ; i++) {
        QString fname;
        switch (mGestures[i]) {
        case (UP_DOWN): {
            fname = ":image/icon_acc_ges_UP_DOWN.png"; break;
        }case (TWIST): {
            fname = ":image/icon_acc_ges_TWIST.png"; break;
        }case (SWAP_LEFT_RIGHT): {
            fname = ":image/icon_acc_ges_SWAP_LEFT_RIGHT.png"; break;
        }case (SWAP_BACK_FORTH): {
            fname = ":image/icon_acc_ges_SWAP_BACK_FORTH.png"; break;
        }case (SWAP_ALL): {
            fname = ":image/icon_acc_ges_SWAP_ALL.png"; break;
        }
        }
        if (!ges[i].load (fname) ) {
            QLOG_ERROR() << TAG << "Unable to load accepted gestures icon for " + mName + " number " + i;
        }
    }
    //return p;

}

/**
 * setGestures - set the accepted gestures
 */
void Applet::setGestures(GestureType ges[]) {
    // calculate the size
    int size= sizeof ges/sizeof(GestureType);

    // Check ges has right size
    if (size > GESTURE_NUMBER ) {
        QLOG_ERROR() << TAG << "Wrong size for " + mName + " accepted gestures : " + GESTURE_NUMBER + " is maximum";
        return;
    }
    for (int i = 0; i < GESTURE_NUMBER ; i++) {
        mGestures[i] = ges[i];
    }
}

/**
 * loadTextFromXml - Load text data from config.xml
 */
void Applet::loadTextFromXml()
{
    // open config.xml
    QDomDocument doc("mydocument");
    QFile file( qApp->applicationDirPath() + "/data/text.xml" );

    if(!file.open(QIODevice::ReadOnly))
    {
        QLOG_ERROR() << TAG << "Unable to open XML text file:" << file.fileName();
    }
    if(!doc.setContent(&file))
    {
        QLOG_ERROR() << TAG << "Unable to read" << file.fileName() << "as an XML file.";
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNodeList appletList = docElem.elementsByTagName("applet");
    for(int idx=0; idx<appletList.count(); idx++)
    {
        if(appletList.at(idx).attributes().namedItem("name").nodeValue() == mName)
        {
            //qDebug() << "   " << appletList.at(idx).toElement().tagName();
            QDomElement el = appletList.at(idx).toElement();

            QDomElement desc = el.elementsByTagName("description").item(0).toElement();
            QDomElement market = el.elementsByTagName("marketing").item(0).toElement();
            QDomElement techni = el.elementsByTagName("technical").item(0).toElement();

            if(!desc.isNull()) mDescription = desc.text();
            if(!market.isNull()) mMarketing = market.text();
            if(!techni.isNull()) mTechnical = techni.text();
        }
    }
}

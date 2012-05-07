#include "applet.h"

#include <QtXml>

const QString Applet::TAG = QString("Applet");

/**
 *
 */
Applet::Applet(QWidget *parent) :
    QWidget(parent)
{
    mName = "defaultName";
    mTitle = "defaultTitle";
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

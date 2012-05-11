#ifndef APPLETBUTTON_H
#define APPLETBUTTON_H

#include <QtGui>
#include <QPainter>
#include <QWidget>

#include "applets/appletInterface.h"

/**
 *
 */
class AppletButton : public QWidget
{

    Q_OBJECT

public:

    AppletButton(AppletInterface *applet, QWidget *parent = 0);

    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:

    void clicked(AppletInterface *applet);

private:
    QPixmap _pix;
    QString _name;
    AppletInterface *_applet;
};


#endif // APPLETBUTTON_H

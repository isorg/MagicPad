#include "appletButton.h"

/**
 *
 */
AppletButton::AppletButton(AppletInterface *applet, QWidget *parent)
    : QWidget(parent)
{
    _pix = applet->icon();
    _name = applet->title();
    _applet = applet;

    //setFixedSize( 96, 96 );
}

/**
 *
 */
void AppletButton::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
    painter.drawPixmap( rect(), _pix );
}

/**
 *
 */
void AppletButton::mouseReleaseEvent(QMouseEvent *)
{

    emit clicked(_applet);
    update();
}

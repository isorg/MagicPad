#include "actionButton.h"
#include <QtGui>
#include <QPainter>

/**
 *
 */
ActionButton::ActionButton(const QPixmap& pix, QWidget *parent) :
    QPushButton(parent), mPixmap(pix)
{
    setFixedSize(40, 40);

    mShow = true;
}

/**
 *
 */
void ActionButton::paintEvent(QPaintEvent *)
{
    // Check that the widget is visible
    if( !mShow ) return;

    QPainter painter( this );
    painter.setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );

    painter.drawPixmap( rect(), mPixmap );


}

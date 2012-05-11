#include "actionButton.h"

#include <QPainter>

/**
 *
 */
ActionButton::ActionButton(const QPixmap& pix, QWidget *parent) :
    QPushButton(parent), mPixmap(pix)
{
    setFixedSize(50, 50);
}

/**
 *
 */
void ActionButton::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );

    painter.drawPixmap( rect(), mPixmap );
}

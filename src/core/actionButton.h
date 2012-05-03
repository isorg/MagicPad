#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QtGui>
#include <QtCore>

class ButtonShadowEffect : public QGraphicsDropShadowEffect
{
    Q_OBJECT
public:
    ButtonShadowEffect(QObject *parent = 0) : QGraphicsDropShadowEffect(parent)
    {
        setBlurRadius(7.0);
        setColor(Qt::lightGray);
        setOffset(0, 0);
    }
};

class ActionButton : public QGraphicsWidget
{
    Q_OBJECT
public:
    ActionButton(const QPixmap& pix, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

    void setPixmap(const QPixmap& pix);

    void setShadowColor(const QColor& color);

signals:
    void pressed();

private:
    QPixmap mPixmap;

};

#endif // ACTIONBUTTON_H

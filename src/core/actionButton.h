#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QPushButton>

/**
 *
 */
class ActionButton : public QPushButton
{

    Q_OBJECT

public:

    ActionButton(const QPixmap& pix, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

private:

    QPixmap mPixmap;

};

#endif // ACTIONBUTTON_H

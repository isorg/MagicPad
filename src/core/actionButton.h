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

public slots:

    void hide() { mShow = false; }

    void show() { mShow = true; }

private:

    QPixmap mPixmap;

    bool mShow;

};

#endif // ACTIONBUTTON_H

#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <QWidget>

#include "QsLog.h"

#include "actionButton.h"

// Width in pixels
#define ACTIONBAR_WIDTH 50

/**
 * Left vertical action bar
 */
class ActionBar : public QWidget
{

    Q_OBJECT

public:

    static const QString TAG;

    ActionBar(QWidget *parent = 0);
    
signals:

    void goBack();

    void quit();

    void showLogger();

    
public slots:

    void hideBack() {
        backActionButton->hide();
    }

    void hideMessage() {
        messageActionButton->hide();
    }

    void hideQuit() {
        quitActionButton->hide();
    }

    void showBack() {
        backActionButton->show();
    }

    void showMessage() {
        messageActionButton->show();
    }

    void showQuit() {
        quitActionButton->show();
    }

private slots:

    void clickBack() { emit goBack(); }

    void clickMessage() { emit showLogger(); }

    void clickQuit() { emit quit(); }

private:

    ActionButton *backActionButton;
    ActionButton *messageActionButton;
    ActionButton *quitActionButton;
};

#endif // ACTIONBAR_H

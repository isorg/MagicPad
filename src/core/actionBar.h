#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "QsLog.h"

/**
 * Left vertical action bar
 */
class ActionBar : public QWidget
{
    Q_OBJECT
public:

    static const QString TAG;

    explicit ActionBar(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ACTIONBAR_H

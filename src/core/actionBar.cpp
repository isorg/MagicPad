#include "actionBar.h"

const QString ActionBar::TAG = QString("ActionBar");

/**
 *
 */
ActionBar::ActionBar(QWidget *parent) :
    QWidget(parent)
{
    // Main layout and style
    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout( mainLayout );

    // Add buttons
    QPushButton *backButton = new QPushButton( this );
    backButton->setIcon( QPixmap( ":image/reverse.png" ).scaled( 40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );

    QPushButton *messageButton = new QPushButton( this );
    messageButton->setIcon( QPixmap( ":image/message.png" ).scaled( 40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );

    QPushButton *connectedButton = new QPushButton( this );
    connectedButton->setIcon( QPixmap( ":image/wire_less.png" ).scaled( 40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );

    QPushButton *quitButton = new QPushButton( this );
    quitButton->setIcon( QPixmap( ":image/power.png" ).scaled( 40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );

    mainLayout->addWidget( backButton );
    mainLayout->addStretch();
    mainLayout->addWidget( messageButton );
    mainLayout->addWidget( connectedButton );
    mainLayout->addWidget( quitButton );

    // Connect signals


}

/*
   ActionButton *backButton = new ActionButton(QPixmap(":image/reverse.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
   ActionButton *messageButton = new ActionButton(QPixmap(":image/message.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
   ActionButton *connectedButton = new ActionButton(QPixmap(":image/wire_less.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
   ActionButton *parametersButton = new ActionButton(QPixmap(":image/work.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
   ActionButton *quitButton = new ActionButton(QPixmap(":image/power.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);

   // top left button
   backButton->setPos(5, 25);
   connect(backButton, SIGNAL(pressed()), this, SLOT(closeCurrentAppletLater()));

   // bottom left butons
   parametersButton->setPos(5, mScreen.height()-200);
   messageButton->setPos(5, mScreen.height()-150);
   connect(messageButton, SIGNAL(pressed()), mLogger, SLOT(exec()));
   connectedButton->setPos(5, mScreen.height()-100);
   quitButton->setPos(5, mScreen.height()-50);

   connect(quitButton, SIGNAL(pressed()), this, SLOT(close()));
*/

#include "actionBar.h"

#include <QVBoxLayout>

const QString ActionBar::TAG = QString("ActionBar");

/**
 *
 */
ActionBar::ActionBar(QWidget *parent) :
    QWidget(parent)
{
    // Background
    setAutoFillBackground( true );
    QPalette p = palette();
    p.setColor( backgroundRole(), Qt::black );
    setPalette( p );

    setFixedWidth( ACTIONBAR_WIDTH );

    // Add buttons
    backActionButton = new ActionButton( QPixmap(":/image/reverse.png") );
    messageActionButton = new ActionButton( QPixmap(":/image/message.png") );
    quitActionButton = new ActionButton( QPixmap(":/image/power.png") );

    // Layout
    QVBoxLayout* layout = new QVBoxLayout( this );
    setLayout( layout );
    layout->addWidget( backActionButton );
    layout->addStretch( 0 );
    layout->addWidget( messageActionButton );
    layout->addSpacing( 50 );
    layout->addWidget( quitActionButton );

    // Connect signals
    connect( backActionButton, SIGNAL(pressed()), this, SLOT(clickBack()) );
    connect( messageActionButton, SIGNAL(pressed()), this, SLOT(clickMessage()) );
    connect( quitActionButton, SIGNAL(pressed()), this, SLOT(clickQuit()) );

}

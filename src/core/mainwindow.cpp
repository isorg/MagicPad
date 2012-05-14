#include "mainwindow.h"

const QString MainWindow::TAG = QString("MainWindow");

/**
 *
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // === Preferences === //
    loadSettings();

    // === Connection === //
    MagicPad *magicPad = new MagicPad();
    mProducer = new FrameProducer();

    int force_com_port = mSettings->value("Communication/force_com_port", 0).toInt();
    if(force_com_port)
    {
        MagicPadDevice device(force_com_port, "MagicPad on COM" + QString::number(force_com_port));
        mProducer->setDevice(device);
        QLOG_INFO() << TAG << "Forcing MagicPad on COM" << force_com_port;
    }
    else
    {
        QList<MagicPadDevice> L = magicPad->listDevices();
        QLOG_INFO() << L.size() << "MagicPad devices found";
        if(L.size() > 0)
        {
            mProducer->setDevice(L.first());
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("No MagicPad devices were found.");
            msgBox.setInformativeText("Make sure that the MagicPad is turned on and the USB cable is plugged in. When using bluetooth, set the COM port number in config.ini");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            exit(0);
        }
    }

    // === Main window === //
    setupUI();

    //// connect(mProducer, SIGNAL(newFrame(cv::Mat)), this, SLOT(testevent(cv::Mat)));

    mProducer->start();
}

/**
 *
 */
void MainWindow::setupUI()
{
    // Maximize
    setWindowState( Qt::WindowFullScreen );

    // Logger
    mLogger = new LoggerDialog( this );

    // Set the scene size to the size of the desktop minus toolbar
    QGraphicsScene *scene = new QGraphicsScene();
    mScreen = QApplication::desktop()->screenGeometry();
    scene->setSceneRect( mScreen );
    View *view = new View( scene );

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->setMargin( 0 );
    layout->addWidget( view );
    //setCentralWidget(view);

    // === Version text === //
    // The version text appears at the bottom right of the screen.
    // It shows the program name and version and a link to www.isorg.fr
    QGraphicsTextItem *versionText = new QGraphicsTextItem;
    QFont ff = versionText->font();
    ff.setPointSize( 10 );
    versionText->setFont( ff );
    versionText->setDefaultTextColor( Qt::white );
    versionText->setHtml(QString(
        "MagicPad v%1 © ISORG 2012\n<a href=\"http://www.isorg.fr\" style=\"color: rgb(255,255,255)\">www.isorg.fr</a>"
        ).arg(MAGICPAD_VERSION_STR));
    versionText->setOpenExternalLinks( true );
    versionText->setTextInteractionFlags( Qt::TextBrowserInteraction );
    versionText->setGraphicsEffect( new AppletShadowEffect() );
    versionText->setTextWidth( 200 );
    versionText->setPos( mScreen.width() - 200, mScreen.height() - 40 );
    scene->addItem( versionText );

    // === Action Bar pannel === //
    // The Action Bar is the left vertical pannel that holds the back,
    // connect, quit and message buttons. The buttons are objects of
    // ActionButton type.
    QGraphicsRectItem *actionBar = new QGraphicsRectItem;
    actionBar->setRect( 0, 0, 50, mScreen.height() );
    actionBar->setPen( QPen( Qt::black ) );
    actionBar->setBrush( Qt::black );
    actionBar->setZValue( 100 );
    scene->addItem( actionBar );

    // Back button
    ActionButton *backButton = new ActionButton(QPixmap(":image/reverse.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
    backButton->setPos(5, 25);
    connect(backButton, SIGNAL(pressed()), this, SLOT(closeCurrentAppletLater()));

    // Logger button
    ActionButton *messageButton = new ActionButton(QPixmap(":image/message.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
    messageButton->setPos( 5, mScreen.height()-140 );
    if( !mShowLogger ) messageButton->hide();
    connect( messageButton, SIGNAL(pressed()), mLogger, SLOT(exec()) );


    // Quit button
    ActionButton *quitButton = new ActionButton(QPixmap(":image/power.png").scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), actionBar);
    quitButton->setPos(5, mScreen.height()-50 );
    if( !mShowQuit ) quitButton->hide();
    connect( quitButton, SIGNAL(pressed()), this, SLOT(close()) );

    // === Applets === //
    // Applets are the independent demonstrations embedded in the MagicPad
    // software. Each applet as a name an an icon. When the applets are
    // loaded, their icons are displayed in a grid-like layout.
    mCurrentApplet = NULL;
    loadApplets( scene );

    // === Left column text === //
    // When an applet is launched a descriptive text drops down on the left
    // side of the screen. All applets share the same container for their
    // text: only the text is changed, the style remains.
    mText = new QGraphicsTextItem;
    QFont f = mText->font();
    f.setPointSize( 14 );
    mText->setFont( f );
    mText->setDefaultTextColor( Qt::white );
    mText->setHtml("This is the default text, it is replaced at runtime by the applet descriptive text");
    mText->setPos( 50, 50 );
    mText->setTextWidth( 400 );
    mText->setGraphicsEffect( new AppletShadowEffect() );
    if( !mShowText ) mText->hide();
    scene->addItem( mText );

    // === Animation === //
    // All animations (=item movement, change of style, ...) are handled by a
    // QStateMachine that calls animation

    // State machine
    rootState = new QState;
    QState *homeState = new QState(rootState);
    QState *appState = new QState(rootState);

    QStateMachine *states = new QStateMachine;
    states->addState(rootState);
    states->setInitialState(rootState);
    rootState->setInitialState(homeState);

    homeState->assignProperty(mText, "pos", QPointF(50, -500));
    QPointF origin(50 + mScreen.center().x() - (MAINWINDOW_APPLETGRID_NCOL*180.0)/2.0,
                   mScreen.center().y() - 180.0*0.5*(mApplets.size()/MAINWINDOW_APPLETGRID_NCOL));
    homeState->assignProperty(mAppletButtonGrid, "pos", origin);
    homeState->assignProperty(mAppletRect, "pos", QPointF(mScreen.width(), 10));
    homeState->assignProperty(backButton, "visible", false);

    appState->assignProperty(mText, "pos", QPointF(50, 150));
    appState->assignProperty(mAppletButtonGrid, "pos", origin - QPointF(mScreen.width(), 10));
    if( mShowText ) {
        appState->assignProperty(mAppletRect, "pos", QPointF(500, 10));
    } else {
        appState->assignProperty(mAppletRect, "pos", QPointF(100, 10));
    }
    appState->assignProperty(backButton, "visible", true & mShowBack );

    // Animations
    // HOME -> APP : app icons out, then text in
    QParallelAnimationGroup *slideAppletAnimation = new QParallelAnimationGroup;
    QParallelAnimationGroup *gotoAppStateAnimation = new QParallelAnimationGroup;

    QPropertyAnimation *animGridOut = new QPropertyAnimation(mAppletButtonGrid, "pos");
    animGridOut->setDuration(750);
    animGridOut->setEasingCurve(QEasingCurve::OutQuad);
    slideAppletAnimation->addAnimation(animGridOut);

    QPropertyAnimation *animAppIn = new QPropertyAnimation(mAppletRect, "pos");
    animAppIn->setDuration(750);
    animAppIn->setEasingCurve(QEasingCurve::OutQuad);
    slideAppletAnimation->addAnimation(animAppIn);

    gotoAppStateAnimation->addAnimation(slideAppletAnimation);

    QPauseAnimation *animTextInPause = new QPauseAnimation(350);

    QPropertyAnimation *animTextIn = new QPropertyAnimation(mText, "pos");
    animTextIn->setDuration(750);
    animTextIn->setEasingCurve(QEasingCurve::OutBounce);

    QSequentialAnimationGroup *animTextInGroup = new QSequentialAnimationGroup;
    animTextInGroup->addAnimation(animTextInPause);
    animTextInGroup->addAnimation(animTextIn);

    gotoAppStateAnimation->addAnimation(animTextInGroup);

    // APP -> HOME : app icons in, then text out
    QParallelAnimationGroup *slideHomeAnimation = new QParallelAnimationGroup;
    QParallelAnimationGroup *gotoHomeStateAnimation = new QParallelAnimationGroup;

    QPropertyAnimation *animTextOut = new QPropertyAnimation(mText, "pos");
    animTextOut->setDuration(750);
    animTextOut->setEasingCurve(QEasingCurve::OutQuad);
    gotoHomeStateAnimation->addAnimation(animTextOut);

    QPropertyAnimation *animGridIn = new QPropertyAnimation(mAppletButtonGrid, "pos");
    animGridIn->setDuration(750);
    animGridIn->setEasingCurve(QEasingCurve::OutQuad);
    slideHomeAnimation->addAnimation(animGridIn);

    QPropertyAnimation *animAppOut = new QPropertyAnimation(mAppletRect, "pos");
    animAppOut->setDuration(750);
    animAppOut->setEasingCurve(QEasingCurve::OutQuad);
    slideHomeAnimation->addAnimation(animAppOut);

    gotoHomeStateAnimation->addAnimation(slideHomeAnimation);

    QAbstractTransition *trans = rootState->addTransition(backButton, SIGNAL(pressed()), homeState);
    trans->addAnimation(gotoHomeStateAnimation);

    trans = rootState->addTransition(this, SIGNAL(goApplet()), appState);
    trans->addAnimation(gotoAppStateAnimation);

    // Start state machine
    states->start();
}

/**
 * Instantiate all applets
 */
void MainWindow::loadApplets(QGraphicsScene *scene)
{
    //
    // Applet icon container:
    // This widget hold the applets icon.
    //
    mAppletButtonGrid = new QGraphicsWidget();
    scene->addItem( mAppletButtonGrid );

    //
    // Applet widget container:
    // This widget holds the applets display area
    //
    mAppletRect =  new QWidget( this );
    mAppletRect->resize( mScreen.width()-500, mScreen.height()-100 );
    mAppletRect->move( mScreen.center().toPoint() + QPoint(500, 0) );
    //scene->addItem( mAppletRect );

    //
    // Register applets to the applet manager.
    // Icon, names, etc... will be automatically handled from there!
    // Order of registration is important for applet position in the grid
    // Grid is filled from top-left, row-by-row
    //
    registerApplet( new AlphabetApplet( mAppletRect ) );
    registerApplet( new BacklightApplet( mAppletRect ) );
    //registerApplet( new BargraphApplet( mAppletRect ) );
    registerApplet( new BulbApplet( mAppletRect ) );
    registerApplet( new DjApplet( mAppletRect ) );
    registerApplet( new GestureApplet( mAppletRect ) );
    registerApplet( new ImagedisplayApplet( mAppletRect ) );
    registerApplet( new MapsApplet( mAppletRect ) );
    registerApplet( new MusicApplet( mAppletRect ) );
    registerApplet( new OpdApplet( mAppletRect ) );
    //registerApplet( new pandaApplet( mAppletRect ) );
    registerApplet( new PictureFlowApplet( mAppletRect ) );
    registerApplet( new PurpleApplet( mAppletRect ) );
    registerApplet( new RollingballApplet( mAppletRect ) );
    registerApplet( new SlideshowApplet( mAppletRect ) );
    registerApplet( new SurfaceApplet( mAppletRect ) );
    registerApplet( new SwitchApplet( mAppletRect ) );
    registerApplet( new TwistApplet( mAppletRect ) );
    //registerApplet( new tyuuApplet( mAppletRect ) );
    registerApplet( new VumeterApplet( mAppletRect ) );

    //
    // Load plugin applets
    //
    QDir pluginsDir( qApp->applicationDirPath() );
    pluginsDir.cd( "plugins" );

    int n = 0;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files) )
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if( plugin )
        {
            AppletInterface *papplet = qobject_cast<AppletInterface *>(plugin);
            if (papplet)
            {
                QLOG_INFO() << TAG << "Plugin" << papplet->title() << "loaded successfully";
                papplet->setParent( mAppletRect );
                registerApplet( papplet );
                n++;
            }
        }
    }

    //
    // Connect frame producer
    //
    connect(mProducer, SIGNAL(newFrame(cv::Mat &)), this, SLOT(dispatchFrame(cv::Mat&)));
}

/**
 * Add an applet to the home menu, connect the sigals/slots
 */
void MainWindow::registerApplet(AppletInterface *applet)
{
    // Resize applet
    applet->resize( mAppletRect->size() );
    applet->hide();

    // Connect the frame producer with applet
    //connect(mProducer, SIGNAL(newFrame(cv::Mat &)), applet, SLOT(setFrame(cv::Mat &)));

    // Add applet to the list
    mApplets.push_back( applet );

    // Create icon button
    AppletButton *button = new AppletButton( applet, mAppletButtonGrid );

    // Position button on the grid    
    int row = (mApplets.size()-1) / MAINWINDOW_APPLETGRID_NCOL;
    int col = (mApplets.size()-1) % MAINWINDOW_APPLETGRID_NCOL;
    button->setPos(180*col, 180*row);

    // Change left column text when applet is selected
    connect(button, SIGNAL(pressed(AppletInterface*)), this, SLOT(launchApplet(AppletInterface*)));
}

/**
 * Close the current applet
 */
void MainWindow::closeCurrentApplet()
{
    // mCurrentApplet is the current applet
    if(mCurrentApplet == NULL) {
        QLOG_ERROR() << TAG << "mCurrentApplet is NULL !!!";
        return;
    }

    // hide
    mCurrentApplet->hide();
    mCurrentApplet->stop();
    mCurrentApplet = NULL;
}

// Schedule closeCurrentApplet() in 0.75 sec
void MainWindow::closeCurrentAppletLater()
{
    QTimer::singleShot( 500, this, SLOT(closeCurrentApplet()) );
}

/**
 * Start an applet
 */
void MainWindow::launchApplet(AppletInterface *applet)
{
    mCurrentApplet = applet;

    // change applet text
    setAppletText( mCurrentApplet );

    // show and start
    mCurrentApplet->show();
    mCurrentApplet->start();
}

/**
 * Change the descriptive text that bounces down when an applet is launched.
 */
void MainWindow::setAppletText(AppletInterface *applet)
{
    QString text =
        "<ul align=left><li>" + applet->descriptionText() + "</li></ul>"
        "<ul align=left><li>" + applet->marketingText() + "</li></ul>"
        "<ul align=left><li>" + applet->technicalText() + "</li></ul>";

    mText->setHtml(text);

    emit goApplet();
}

/**
 * Setup and load settings file
 */
void MainWindow::loadSettings()
{
    QString iniFile( QDir(qApp->applicationDirPath()).filePath( APPLICATION_SETTINGS_FILE ) );

    if( QFile::exists( iniFile ) == false )
    {
        QLOG_ERROR() << TAG << "INI file not found at:" << iniFile;
    }

    mSettings = new QSettings( iniFile, QSettings::IniFormat );

    // Access setting value using:
    //mSettings->value("myapplet/autostart", "abc").toString();

    mShowLogger = mSettings->value("show_log", true).toBool();
    mShowBack = mSettings->value("show_back", true).toBool();
    mShowQuit = mSettings->value("show_quit", true).toBool();
    mShowText = mSettings->value("show_description_text", true).toBool();

    /*QLOG_DEBUG() << TAG << "mShowLogger" << mShowLogger;
    QLOG_DEBUG() << TAG << "mShowBack" << mShowBack;
    QLOG_DEBUG() << TAG << "mShowQuit" << mShowQuit;
    QLOG_DEBUG() << TAG << "mShowText" << mShowText;*/
}

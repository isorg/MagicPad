#include "surfaceApplet.h"

const QString SurfaceApplet::TAG = QString("SurfaceApplet");

/**
 *
 */
SurfaceApplet::SurfaceApplet(QWidget *parent) : Applet(parent)
{
    mName = SURFACE_NAME;
    mTitle = SURFACE_TITLE;

    // load description, marketing and technical text from
    // xml file. Ensure that mName is set before calling this function
    loadTextFromXml();

    // Pipeline
    mCalibrationFilter = new CalibrationFilter();

    mFrame = cv::Mat(10, 10, CV_8U);
    mFrameDouble = cv::Mat(10, 10, CV_64F);
    mFrameFiltered = cv::Mat(10, 10, CV_64F);
    mFrameFiltered.setTo( cv::Scalar::all(0) );

    // UI
    setupSurface();
}

/**
 *
 */
void SurfaceApplet::setFrame( cv::Mat& frame )
{
    // Filter pipeline
    mCalibrationFilter->setFrame( frame );
    mCalibrationFilter->process();

    mFrame = mCalibrationFilter->getCalibratedFrame();
    mFrame.convertTo( mFrameDouble, CV_64F );

    // Low pass temporal filter to smooth down movement
    mFrameFiltered += 0.6 * ( mFrameDouble - mFrameFiltered );

    // Increase image resolution
    cv::resize(mFrameFiltered,
               mHighResFrame,
               cv::Size(),
               SURFACE_UPSCALING_FACTOR,
               SURFACE_UPSCALING_FACTOR,
               cv::INTER_CUBIC);

    double maxSensor = 0.0;
    for(int i=0; i<mHighResFrame.rows; i++)
    {
        for(int j=0; j<mHighResFrame.cols; j++)
        {
            double value = (mHighResFrame.at<double>(mHighResFrame.rows-i-1, mHighResFrame.cols-j-1)) / SURFACE_PLOTFACTOR;
            mTable[i+1][j+1] = value;
            if( value > maxSensor ) maxSensor = value;
        }
    }

    // The maximum value across the whole matrix is used to compute the color legend;
    int maxScale = std::max(2, std::min(255, (int)(255.0 * maxSensor / (255.0 / SURFACE_PLOTFACTOR))));
    //int maxScale = 255;

    Qwt3D::ColorVector::iterator last = mColorVector.begin() + (maxScale-1);
    Qwt3D::ColorVector cv_( mColorVector.begin(), last );

    Qwt3D::StandardColor *sc = new Qwt3D::StandardColor( mSurface, maxScale );
    sc->setColorVector( cv_ );
    mSurface->setDataColor( sc );


    mSurface->loadFromData(
        mTable,         // data array
        m_hrWidth,      // number of rows
        m_hrHeight,     // number of columns
        1.0,            // min row
        m_hrWidth,      // max row
        1.0,            // min col
        m_hrHeight);    // max col

    mSurface->updateData();
    mSurface->updateGL();

    update();
}

/**
 *
 */
void SurfaceApplet::setupSurface()
{
    mSurface = new Qwt3D::SurfacePlot( this );

    // Camera
    mSurface->setShift( 0.35, 0, 0 );
    mSurface->setRotation( 60, 0, 60 );
    mSurface->setCoordinateStyle( Qwt3D::NOCOORD );
    mSurface->enableMouse( true );
    mSurface->enableKeyboard( true );

    // Mesh
    mSurface->setMeshLineWidth( 1.0/(2*SURFACE_UPSCALING_FACTOR+1) );
    mSurface->setPlotStyle( Qwt3D::FILLEDMESH );
    mSurface->setSmoothMesh( true );
    this->allocateData();

    // Lightning
    mSurface->enableLighting( true );
    mSurface->illuminate( 0 );
    mSurface->setShading( Qwt3D::GOURAUD );
    mSurface->setLightComponent( GL_DIFFUSE, 0.5 );
    mSurface->setMaterialComponent( GL_SPECULAR, 0.1 );
    mSurface->setShininess( 0.1 );
    mSurface->setMaterialComponent( GL_EMISSION, 0.1 );
    mSurface->setBackgroundColor( Qwt3D::RGBA(1,1,1,0.5) );

    // Colormap
    mColorVector.resize(255);
    for(int i=0; i<mColorVector.size(); i++)
    {
        QColor c;
        c.setHsv( ((255-i)*255.0)/255.0, 255.0, 255.0 );
        mColorVector[i] = Qwt3D::RGBA( c.red()/255., c.green()/255., c.blue()/255. );
    }
    Qwt3D::StandardColor *sc = new Qwt3D::StandardColor( mSurface, 255 );
    sc->setColorVector( mColorVector );
    mSurface->setDataColor( sc );
    mSurface->showColorLegend( true );
    mSurface->legend()->setLimits( 0, 255 );

    //mSurface->resize( size() );
    mSurface->resize( QSize(500, 500) );
}

/**
 *
 */
void SurfaceApplet::allocateData()
{
    // TODO: fix desallocation
    if(mTable != NULL) delete [] mTable;

    m_hrWidth = (10 * SURFACE_UPSCALING_FACTOR) + 2;
    m_hrHeight = (10 * SURFACE_UPSCALING_FACTOR) + 2;

    mTable = new double*[m_hrWidth];
    for(int i=0; i<m_hrWidth; ++i)
        mTable[i] = new double[m_hrHeight];

    for(int i=0; i<m_hrWidth; i++)
    {
        for(int j=0; j<m_hrHeight; j++)
        {
             mTable[i][j] = 0;
        }
    }

    // Set display scale
    mSurface->setScale(1.0, 1.0, (SURFACE_UPSCALING_FACTOR+1)/2.0);
}

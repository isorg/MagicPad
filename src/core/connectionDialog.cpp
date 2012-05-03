#include "connectionDialog.h"


/**
 * Constructor: build UI and setup signal/slot
 */
ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent)
{
    // === UI ===
    setWindowTitle("Connection manager");
    resize(450, 360);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Top description text.
    QLabel *lblDescription = new QLabel("List connected devices. Make sure your MagicPad is turned on. If using USB communication plug the cable in. If using Bluetooth make sure that the MagicPad and the computer are paired.");
    lblDescription->setWordWrap(true);
    layout->addWidget(lblDescription);

    // Refresh layout: contains the refresh button and some text
    QHBoxLayout *refreshLayout = new QHBoxLayout();
    layout->addLayout(refreshLayout);

    btnRefresh = new QPushButton("Refresh list");
    btnRefresh->setCheckable(true);
    btnRefresh->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(btnRefresh, SIGNAL(clicked()), this, SLOT(refreshList()));
    refreshLayout->addWidget(btnRefresh);
    refreshLayout->setAlignment(btnRefresh, Qt::AlignLeft);

    lblRefresh = new QLabel("");
    lblRefresh->hide();
    refreshLayout->addWidget(lblRefresh);
    refreshLayout->setAlignment(lblRefresh, Qt::AlignRight);

    // Radios button for each devices
    QRadioButton *chk1 = new QRadioButton("Device 1");
    QRadioButton *chk2 = new QRadioButton("Device 2");
    QRadioButton *chk3 = new QRadioButton("Device 3");
    QRadioButton *chk4 = new QRadioButton("Device 4");

    devicesLayout = new QVBoxLayout();
    devicesLayout->addWidget(chk1);
    devicesLayout->addWidget(chk2);
    devicesLayout->addWidget(chk3);
    devicesLayout->addWidget(chk4);

    QGroupBox *devicesBox = new QGroupBox();
    layout->addWidget(devicesBox);
    devicesBox->setLayout(devicesLayout);

    // Add a stretch to push device list up and push connection button downward
    layout->addStretch(-1);

    // Option to remember which device should be connected automatically
    QCheckBox *chkRemember = new QCheckBox("Automatically connect to the first avaible device");
    // TODO: read/write prefs
    layout->addWidget(chkRemember);

    // Connect and quit button
    QPushButton *btnConnect = new QPushButton("Connect");
    btnConnect->setDefault(true);
    layout->addWidget(btnConnect);

    // === Logic ===
    // After the UI is build, trigger a 'refreshList' event
    //refreshList();
}

/**
 * Add a device in the device list
 */
void ConnectionDialog::addDevices(QList<QString> devices)
{
    bool first = true;

    for(QList<QString>::iterator device = devices.begin(); device != devices.end(); ++device)
    {
        QRadioButton *chkbox = new QRadioButton(*device);
        if(first) {
            chkbox->setChecked(true);
            first = false;
        }
        devicesLayout->addWidget(chkbox);
    }
}

/**
 * Refresh the device list
 */
void ConnectionDialog::refreshList()
{
    // disable refresh button
    btnRefresh->setChecked(true);
    btnRefresh->setDisabled(true);

    // remove devices from the list
    QLayoutItem* item;
    while((item = devicesLayout->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }

    // show 'scanning' text
    lblRefresh->setText(CONNECTIONDIALOG_SCANNING);
    lblRefresh->show();

    // simulating new devices
    QList<QString> L;
    L.push_front("MagicPad #1 [USB COM4]");
    L.push_front("MagicPad #5 [Bluetooth COM1]");
    L.push_front("MagicPad #2 [USB COM12]");
    addDevices(L);
}

/**
 * Set the currently selected device
 */
void ConnectionDialog::setSelectedDevice(QString& device)
{
    qDebug() << "Selecting device:" << device;
}

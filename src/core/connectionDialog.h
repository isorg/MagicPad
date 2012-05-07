#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QVBoxLayout>

#define CONNECTIONDIALOG_SCANNING   "<i>Scanning for MagicPad devices ...</i>"
#define CONNECTIONDIALOG_FOUND      "<i>(%1) device(s) found.</i>"

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:

    ConnectionDialog(QWidget *parent = 0);

signals:
    void startRefreshing();
    void stopRefreshing();

public slots:
    void addDevices(QList<QString> devices);
    void refreshList();    
    void setSelectedDevice(QString& device);

private:
    QPushButton *btnRefresh;
    QLabel *lblRefresh;
    QScrollArea *scrollDevices;
    QVBoxLayout *devicesLayout;
};

#endif // CONNECTIONDIALOG_H

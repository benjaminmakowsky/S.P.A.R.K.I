#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothaddress.h>
#include "deviceinfo.h"
#include <QVariant>

class DeviceInfo : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInfo(QObject *parent = 0);

    DeviceInfo(const QBluetoothDeviceInfo &d);
    QString getName()const;
    QString getAddress() const;
    void setDevice(const QBluetoothDeviceInfo &m_device);
    QBluetoothDeviceInfo getDevice() const;

signals:

private:
    QBluetoothDeviceInfo device;



};

#endif // DEVICEINFO_H

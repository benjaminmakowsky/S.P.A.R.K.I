#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <qbluetoothglobal.h>
#include <qbluetoothlocaldevice.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceInfo>
#include "deviceinfo.h"
#include <QList>
#include <QVariant>


class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = 0);

    QVariant name();
    ~Device();

signals:
    void address(QVariant);

public slots:

    void startDeviceDiscovery();
    void connectDeivce(const QString &address);

private slots:

    void addDevice(const QBluetoothDeviceInfo&);
    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();
    void controllerError(QLowEnergyController::Error);
    void deviceConnected();
    void deviceDisconnected();

private:

    DeviceInfo m_currentDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QObject*>devices;
    QLowEnergyController *m_control;

};

#endif // DEVICE_H

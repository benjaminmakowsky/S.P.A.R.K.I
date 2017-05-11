#include "device.h"
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothservicediscoveryagent.h>
#include <QDebug>
#include <QString>
#include <QList>

Device::Device(QObject *parent) : QObject(parent)
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    connect(discoveryAgent,SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),this,SLOT(addDevice(const QBluetoothDeviceInfo&)));

}
Device::~Device(){
    qDeleteAll(devices);
    devices.clear();
}
void Device::addDevice(const QBluetoothDeviceInfo &info){
    if(info.coreConfigurations()&QBluetoothDeviceInfo::LowEnergyCoreConfiguration){
        DeviceInfo *d = new DeviceInfo(info);
        devices.append(d);
        qWarning()<<"Discovered BLE Devices" + d->getName() <<"Address: " + d->getAddress();
        if(d->getName() == "SPARKI"){
            address(QString(d->getAddress()));
        }
    }
}

void Device::startDeviceDiscovery(){
    qDeleteAll(devices);
    devices.clear();
    discoveryAgent->start();
    qWarning()<<"Starting to Scan";

}

void Device::connectDeivce(const QString &address){
    for(int i = 0; i<devices.size(); i++){
        if(((DeviceInfo*)devices.at(i))->getAddress()== address){
            m_currentDevice.setDevice(((DeviceInfo*)devices.at(i))->getDevice());
            qWarning()<< "Connecting to Device.";
            break;
        }
    }
    m_control = new QLowEnergyController(m_currentDevice.getDevice(),this);

    connect(m_control,SIGNAL(serviceDiscovered(QBluetoothUuid)),this,SLOT(serviceDiscovered(QBluetoothUuid)));
    connect(m_control,SIGNAL(discoveryFinished()),this,SLOT(serviceScanDone()));
    connect(m_control,SIGNAL(error(QLowEnergyController::Error)),this,SLOT(controllerError(QLowEnergyController::Error)));
    connect(m_control,SIGNAL(connected()),this,SLOT(deviceConnected()));
    connect(m_control,SIGNAL(disconnected()),this,SLOT(deviceDisconnected()));

    m_control->connectToDevice();

}

void Device::deviceConnected(){
    m_control->discoverServices();
}

void Device::deviceDisconnected(){
    qWarning()<<"Device has been disconnected";
}

void Device::controllerError(QLowEnergyController::Error error){
    qWarning()<<"Controller Error: " << error << "Cannot Connect to remote device.";
}

QVariant Device::name(){
    return QVariant::fromValue(devices);
}

void Device::serviceScanDone(){
    qWarning()<< "Service scane done. Waiting...";

}

void Device:: serviceDiscovered(const QBluetoothUuid &gatt){
    if(gatt == QBluetoothUuid(QBluetoothUuid::Direction)){
        qWarning() << "Found the Service.";
    }
}

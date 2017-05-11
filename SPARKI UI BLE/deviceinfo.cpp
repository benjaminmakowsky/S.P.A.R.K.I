#include "deviceinfo.h"
#include <qbluetoothuuid.h>

DeviceInfo::DeviceInfo(QObject *parent) : QObject(parent)
{

}
DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &d){
    device = d;
}
QString DeviceInfo::getName() const{

    return device.name();
}

QString DeviceInfo::getAddress()const{

    return device.address().toString();
}
void DeviceInfo::setDevice(const QBluetoothDeviceInfo &m_device){
    device = m_device;
}
QBluetoothDeviceInfo DeviceInfo::getDevice() const{
    return device;
}

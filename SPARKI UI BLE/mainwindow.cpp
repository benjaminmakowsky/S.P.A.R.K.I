#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth>
#include <QDebug>
#include <QtWidgets>
#include "device.h"
#include "deviceinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Device *myDevice = new Device();


    /*Connections for the directional arrows*/
    connect(ui->forwardButton, SIGNAL(clicked(bool)),this, SLOT(sendData()));
    connect(ui->backButton, SIGNAL(clicked(bool)),this, SLOT(sendData()));
    connect(ui->leftButton, SIGNAL(clicked(bool)),this, SLOT(sendData()));
    connect(ui->rightButton, SIGNAL(clicked(bool)),this, SLOT(sendData()));

    connect(ui->connectButton,&QPushButton::clicked,myDevice,&Device::startDeviceDiscovery);


}

MainWindow::~MainWindow()
{
    //closes everything upon closure of window

    delete ui;
}


void MainWindow::on_forwardButton_pressed()
{

    ui->label->setText("Moving");
    qDebug() << "Button Pushed";
    sendData(forwardCommand);
}

void MainWindow::on_forwardButton_released()
{
    qDebug() << "Button released is running";
    sendData(stopCommand);
    qDebug() <<"Stop command sent";
}


void MainWindow::sendData(QString command){
    qDebug() << "sendData is running";

    QString sendSpeed = command;


}

void MainWindow::sendSpeed(QString speed){
    qDebug() << speed;
    QString sendSpeed = speedCommand + speed;
    qDebug() << "sendSpeed is running" << sendSpeed;

}




void MainWindow::on_leftButton_pressed()
{
    ui->label->setText("Moving");
    qDebug() << "Button Pushed";
    sendData(leftCommand);
}

void MainWindow::on_leftButton_released()
{
    qDebug() << "Button released is running";
    sendData(stopCommand);
    qDebug() <<"Stop command sent";
}

void MainWindow::on_backButton_pressed()
{
    ui->label->setText("Moving");
    qDebug() << "Button Pushed";
    sendData(backCommand);
}

void MainWindow::on_backButton_released()
{
    qDebug() << "Button released is running";
    sendData(stopCommand);
    qDebug() <<"Stop command sent";
}

void MainWindow::on_rightButton_pressed()
{
    ui->label->setText("Moving");
    qDebug() << "Button Pushed";
    sendData(rightCommand);
}

void MainWindow::on_rightButton_released()
{
    qDebug() << "Button released is running";
    sendData(stopCommand);
    qDebug() <<"Stop command sent";
}

void MainWindow::on_transmitButton_clicked()
{
    qDebug() <<"Transmit Button Pressed. Preparing to send data...";
    sendSpeed(ui->lineEdit->displayText());
    qDebug() <<"Transmission Complete";
    ui->lineEdit->clear();
}



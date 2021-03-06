#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino = new QSerialPort; //creates a new serial port object

    /*Section for connecting a click of all the directional arrows to
     * the stop command to prevent a continuous drive loop from occuring*/
    connect(ui->forwardButton, SIGNAL(clicked(bool)),this, SLOT(sendData(stopCommand)));
    connect(ui->backButton, SIGNAL(clicked(bool)),this, SLOT(sendData(stopCommand)));
    connect(ui->leftButton, SIGNAL(clicked(bool)),this, SLOT(sendData(stopCommand)));
    connect(ui->rightButton, SIGNAL(clicked(bool)),this, SLOT(sendData(stopCommand)));

    //Lists all available ports scanned to determine which one the robot is using
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length(); //Returns the number of ports in use
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())//For loop that iterates through all available ports
    {
        qDebug() << "Port Name: " << serialPortInfo.portName(); //prints port name
        arduino_is_available = true; //sets the value determinig arduino is available to true
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName("COM9"); //the com port on my computer that the arduino connects to.
        arduino->open(QSerialPort::WriteOnly); //sets it so that only user can only send data to robot
        arduino->setBaudRate(QSerialPort::Baud9600);//sets the BAUD rate which determines how fast it is communicating
        arduino->setDataBits(QSerialPort::Data8);//sets the number of bits to be transmitted
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }

}

MainWindow::~MainWindow()
{
    //closes everything upon closure of window
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}



void MainWindow::on_forwardButton_pressed()
{

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
    qDebug() << "sendData is running with command " << command;
    if(arduino->isWritable()){
        //arduino->write("moveC");
        arduino->write(command.toStdString().c_str());
        qDebug() << "arduino is writable with command " << command;
        arduino->waitForBytesWritten(2000);
        qDebug() <<"Data has been written";
    }
    else{qDebug() << "Couldn't write to serial!";}
}

void MainWindow::sendSpeed(int speed){
    qDebug() << speed;
    QString sendSpeed = speedCommand + QString::number(speed);
    qDebug() << "sendSpeed is running" << sendSpeed;
    if(arduino->isWritable()){
        arduino->write(sendSpeed.toStdString().c_str());
        arduino->waitForBytesWritten(2000);
        sendSpeed = "";
        //speed = "";
        qDebug() <<"Data has been written with value of: " << sendSpeed;
    }
    else{qDebug() << "Couldn't write to serial!";}
}




void MainWindow::on_leftButton_pressed()
{
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
    qDebug() << "Button Pushed";
    sendData(rightCommand);
}

void MainWindow::on_rightButton_released()
{
    qDebug() << "Button released is running";
    sendData(stopCommand);
    qDebug() <<"Stop command sent";
}

void MainWindow::on_speedSlider_sliderReleased()
{
    qDebug() <<"Sending new speed value. Preparing to send data...";
    sendSpeed(ui->speedSlider->value());
    qDebug() <<"Transmission Complete";
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    ui->speedBar->setValue(value);
}

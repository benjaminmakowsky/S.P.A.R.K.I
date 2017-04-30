#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    arduino_is_available = false;
    arduino = new QSerialPort; //creates a new serial port object


    //Lists all available ports scanned to determine which one the robot is using
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length(); //Returns the number of ports in use
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())//For loop that iterates through all available ports
    {
        qDebug() << "Port Name: " << serialPortInfo.portName(); //prints port name
        arduino_is_available = true; //sets the value determinig arduino is available to true
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName("COM9"); //the com port on my computer that the arduino connects to. MAKE OPTION FOR USER TO PICK!
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

    pButtonTimer = new QTimer;
    connect(pButtonTimer, SIGNAL(timeout()), this, SLOT(sendData()));


}

MainWindow::~MainWindow()
{
    //closes everything upon closure of window
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}




int i = 0;
void MainWindow::on_forwardButton_pressed()
{
    pButtonTimer->start(1000);
    ui->label->setText("Moving");
    qDebug() << "Button Pushed";
}

void MainWindow::on_forwardButton_released()
{
    pButtonTimer->stop();
}

void MainWindow::sendData(){
    i++;
    qDebug() << i << "sendData is running";
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
        qDebug() << i << "arduino is writable with command " << command;
    }
    else{qDebug() << "Couldn't write to serial!";}
}




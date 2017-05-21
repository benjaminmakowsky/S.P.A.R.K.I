#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDialog>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




private slots:

    //Methods movement control
    void on_forwardButton_pressed();//Sends the forwardComamnd when button is pressed
    void on_forwardButton_released();   //Sends the stop command to terminate movement when button is released
    void on_leftButton_pressed();   //Sends the leftCommand when button is pressed
    void on_leftButton_released();      //Sends the stop command to terminate movement when button is released
    void on_backButton_pressed();   //Sends the leftCommand when button is pressed
    void on_backButton_released();      //Sends the stop command to terminate movement when button is released
    void on_rightButton_pressed();  //Sends the leftCommand when button is pressed
    void on_rightButton_released();     //Sends the stop command to terminate movement when button is released

    //Methods for speed control
    void on_speedSlider_sliderReleased();        //Sends the set speed to the arduino
    void on_speedSlider_valueChanged(int value); //Updates the progress bar with the matching speed value

public slots:

    /*
     * The following method sends a command to the arduino
     * and prints out debug information to the console.
     *
     * @param (QString) the command that is desired to be sent
    */
    void sendData(QString command);

    /*
     * The following method reads an integer value converts it
     * to a string sends it to the arduino.
     *
     * @param (Int) The integer value for the speed to be sent
    */
    void sendSpeed(int speed);

private:
    Ui::MainWindow *ui;


    QSerialPort *arduino; //makes arduino a pointer to the SerialPort
    bool arduino_is_available;

    //Command Strings
    QString forwardCommand = "moveC";
    QString leftCommand = "leftC";
    QString rightCommand = "rightC";
    QString backCommand = "backC";
    QString stopCommand = "stopC";
    QString speedCommand = "setSpeed ";

};


#endif // MAINWINDOW_H

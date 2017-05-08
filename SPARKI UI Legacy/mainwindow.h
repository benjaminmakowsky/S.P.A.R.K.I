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

    void on_forwardButton_pressed();
    void on_forwardButton_released();    
    void on_leftButton_pressed();
    void on_leftButton_released();
    void on_backButton_pressed();
    void on_backButton_released();
    void on_rightButton_pressed();
    void on_rightButton_released();


    void on_transmitButton_clicked();

public slots:

    void sendData(QString command);
    void sendSpeed(QString speed);

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

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


    void sendData();
    void on_forwardButton_pressed();

    void on_forwardButton_released();

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino; //makes arduino a pointer to the SerialPort
    bool arduino_is_available;
    QString command = "move 200";
    bool buttonReleased = false;
    QTimer *pButtonTimer;//time to control the buttons
};

#endif // MAINWINDOW_H

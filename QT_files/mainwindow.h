#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include<QTextEdit>
#include<QString>
#include<QDateTime>
#include<QTextEdit>
#include<QColor>
#include"joystick.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *button_x; // Deklaracja przycisku
    QPushButton *button_y; // Deklaracja przycisku
    QPushButton *button_search; // Deklaracja przycisku
    QPushButton *button_connect; // Deklaracja przycisku
    QPushButton *button_clear; // Deklaracja przycisku
    QPushButton *button_disconnect; // Deklaracja przycisku
    QComboBox *combo_box; //Deklaracja Comboboxa
    JoyStick *js;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothSocket *socket;
    QTextEdit *text;

private slots:
    //void handleButton(); // Slot obsługujący kliknięcie przycisku
    void handleJoystickMoved(const QPoint &position);
    void search();
    void succesfull_connect();
    void captureDeviceProperties(const QBluetoothDeviceInfo &device);
    void startConnectToDevice();
    void connectionEstablished();
    void getData();
    void clean();
    void disconnect();
};
#endif // MAINWINDOW_H

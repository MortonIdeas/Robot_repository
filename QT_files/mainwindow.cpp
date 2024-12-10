#include "mainwindow.h"
#include "ui_mainwindow.h"
char getSymbol(int x_cor)
{
    if(x_cor > 0)
    {
        return 0;
    }
}
QString getV(int value)
{
    if(value == 0)
    {
        return "0";
    }
    else if(value<100)
    {
        return "1";
    }
    else if(value<400)
    {
        return "2";
    }
    else if(value<900)
    {
        return "3";
    }
    else if(value<1600)
    {
        return "4";
    }
    else if(value<2500)
    {
        return "5";
    }
    else if(value<3600)
    {
        return "6";
    }
    else if(value<4900)
    {
        return "7";
    }
    else if(value<6400)
    {
        return "8";
    }
    else
    {
        return "9";
    }
}
QString getModule(int x_cor, int y_cor)
{
    int value = x_cor*x_cor+y_cor*y_cor;
    return getV(value);
}
QString getDirection(int x_cor, int y_cor)
{
    if(x_cor == 0 && y_cor == 0)
    {
        return "Z";
    }
    else if(y_cor > 0 && x_cor == 0)
    {
        return "A";
    }
    else if(y_cor<0 && x_cor == 0)
    {
        return "J";
    }
    else if(x_cor>0)
    {
        double tan = double(y_cor)/double(x_cor);

        if(tan>5.67)
        {
            return "A";
        }
        else if(tan>1.73)
        {
            return "B";
        }
        else if(tan>0.83)
        {
            return "C";
        }
        else if(tan>0.37)
        {
            return "D";
        }
        else if(tan>0.0)
        {
            return "E";
        }
        else if(tan>-0.37)
        {
            return "F";
        }
        else if(tan>-0.83)
        {
            return "G";
        }
        else if(tan>-1.73)
        {
            return "H";
        }
        else if(tan>-5.67)
        {
            return "I";
        }
        else
        {
            return "J";
        }
    }
    else if(x_cor<0)
    {
        double tan = double(y_cor)/double(x_cor);

        if(tan<-5.67)
        {
            return "A";
        }
        else if(tan<-1.73)
        {
            return "S";
        }
        else if(tan<-0.83)
        {
            return "R";
        }
        else if(tan<-0.37)
        {
            return "P";
        }
        else if(tan<0.0)
        {
            return "O";
        }
        else if(tan<0.37)
        {
            return "N";
        }
        else if(tan<0.83)
        {
            return "M";
        }
        else if(tan<1.73)
        {
            return "L";
        }
        else if(tan<5.67)
        {
            return "K";
        }
        else
        {
            return "J";
        }
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700, 400);

    //Inicjalizacja przyciskow oraz ich geometrii
    button_x = new QPushButton(this);
    button_x->setGeometry(0, 0, 200, 50);

    //Ustawienie przycisku wskazujacego wspolrzędna y-kowa
    button_y = new QPushButton(this);
    button_y->setGeometry(200, 0, 200, 50);

    button_search = new QPushButton("Szukaj urz. bluetooth", this);
    button_search->setGeometry(400, 0, 170, 50);

    button_connect = new QPushButton("Polacz z robotem", this);
    button_connect->setGeometry(400, 100, 170, 50);

    button_clear = new QPushButton("Wyczyść logi", this);
    button_clear->setGeometry(570, 0, 170, 50);

    button_disconnect = new QPushButton("Rozlacz z robotem", this);
    button_disconnect->setGeometry(570, 100, 170, 50);

    //Inicjalizacja comboBoxa, ktory bedzie przechowywal geometrie
    combo_box = new QComboBox(this);
    combo_box->setGeometry(400, 50, 340, 50);

    //Polaczenie sygnalu wyemitowanego z przycisku button_search ze Slotem, ktory rozpoczyna wyszukiwanie
    connect(button_search, &QPushButton::clicked, this, &MainWindow::search);

    //Polaczenie sygnalu wyemitowanego z przycisku button_clear ze Slotem, ktory czysci logi
    connect(button_clear, &QPushButton::clicked, this, &MainWindow::clean);

    //Polaczenie sygnalu wyemitowanego z przycisku button_search ze Slotem, ktory rozpoczyna wyszukiwanie
    connect(button_disconnect, &QPushButton::clicked, this, &MainWindow::disconnect);

    //Inicjalizacja Klasy JoyStick, ustawienie lokalizacji oraz sprawienie, aby joystick reagowal na zmiany polozenia
    JoyStick *js = new JoyStick(this);
    js->setGeometry(0, 50, 200, 200);
    //Polaczenie sygnalu informujacego ze sie joystick poruszył ze Slotem
    connect(js, &JoyStick::joystickMoved, this, &MainWindow::handleJoystickMoved);

    //Klasa pozwalajaca na wyszukiwanie. Dodanie wyszukiwacza polaczen:
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    //gdy klasa wykryje jakies urzadzenia bluetooth to ma za zadanie informacje o urzadzeniu wstawic do ComboBoxa
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(captureDeviceProperties(QBluetoothDeviceInfo)));

    //Jest to klasa ktora pozwala na polaczenie
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(this->socket, SIGNAL(connected()),this, SLOT(connectionEstablished()));

    //Dodanie tablicy na logi z urzadzenia
    text = new QTextEdit(this);
    text->setGeometry(400, 150, 340, 220);

    //W momencie gdy juz znajdziemy HC-06 to po przycisnieciu polacz ma sie wykonac metoda startConnectToDevice
    connect(button_connect, &QPushButton::clicked,this, &MainWindow::startConnectToDevice);
    //Polaczenie sluzace odbieraniu danych
    connect(socket, SIGNAL(readyRead()), this, SLOT(getData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::handleJoystickMoved(const QPoint &position)
{
    int x_value = position.x()-200;
    int y_value = -(position.y()-175);

    QString x_string = QString::number(x_value);
    button_x->setText("WSP. X="+QString(x_string));

    QString y_string = QString::number(y_value);
    button_y->setText("WSP. Y="+QString(y_string));
    //Decyduje o tym jakie ma byc sterowanie
    QString mes;
    QString mes_l=getModule(x_value, y_value);
    QString mes_p=getDirection(x_value, y_value);

    mes = mes_p+mes_l;
    //text->append(mes);
    int a = socket->write(mes.toStdString().c_str());
    //qDebug()<<"Ilosc znakow wynosi: "<<a;
}

void MainWindow::search()
{
    text->append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")+" Zaczynam poszukiwania");
    discoveryAgent->start();//Rozpoczynamy wyszukiwanie urządzeń
    combo_box->addItem("Rozpoczeto poszukiwania");
}

void MainWindow::startConnectToDevice() {
    text->append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")+"Rozpoczynam polaczenie: ");
    QString comboBoxQString = combo_box->currentText();
    QStringList portList = comboBoxQString.split(" ");
    QString deviceAddres = portList.last();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    this->socket->connectToService(QBluetoothAddress(deviceAddres), QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
    text->append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")+"Rozpoczęto łączenie z urządzeniem o nazwie: " + portList.first() + " i adresie: " + deviceAddres);
}

void MainWindow::captureDeviceProperties(const QBluetoothDeviceInfo &device) {
    combo_box->addItem(device.name() + " " + device.address().toString());
    //text->append("Znaleziono urządzenie o nazwie: " + device.name() + " i adresie: " + device.address().toString());
}
void MainWindow::succesfull_connect()
{
    combo_box->addItem("Udało nawiazac sie polaczenie");
}
void MainWindow::connectionEstablished()
{
    text->append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")+"Polaczenie ustawione");
}
void MainWindow::getData()
{
    while(socket->canReadLine())
    {
        QString line = socket->readLine();
        QString terminator = "/r";
        int pos = line.lastIndexOf(terminator);
        text->append(line.left(pos));
    }
}
void MainWindow::clean()
{
    text->clear();
}
void MainWindow::disconnect()
{
    this->socket->disconnectFromService();
    text->append(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")+"Przerywam połączenie");
}

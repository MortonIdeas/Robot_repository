#include "joystick.h"
#include <QPainter>
#include <QMouseEvent>

JoyStick::JoyStick(QWidget *parent) : QWidget(parent),
    m_center(0, 0),
    m_currentPosition(200, 175),
    m_pressed(false),
    m_radius(50),
    m_backgroundColor(Qt::yellow),
    m_handleColor(Qt::darkGray)
{
    //Ustawienie rozmiaru joysticka
    setFixedSize(400, 350);
    //Ustawiam co jaki czas timer ma emitowac sygnal do slotu sendJoystickPosition
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &JoyStick::sendJoystickPosition);
    m_timer.start();
}

void JoyStick::paintEvent(QPaintEvent *event)
{
    //Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  //Poprawienie grafiki
    int width = this->width();  //Pobiera dlugosc
    int heigh = this->height(); //pobiera wysokosc
    m_center = QPoint(width/2, heigh/2);
    drawBackground(&painter);   //Rysowanie tla joysticka
    drawHandle(&painter);   //Rysuje uchwyt joysticka
}

void JoyStick::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressed = true;
        m_currentPosition = event->pos();
        update();
    }
}

void JoyStick::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed) {
        m_currentPosition = event->pos();
        update();
    }
}

void JoyStick::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressed = false;
        m_currentPosition = m_center;
        update();
    }
}

void JoyStick::drawBackground(QPainter *painter)
{
    //painter->save();
    painter->setBrush(m_backgroundColor);
    //painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center, m_radius, m_radius);
    //painter->restore(); //Przywraca stan sprzed
}

void JoyStick::drawHandle(QPainter *painter)
{
    //painter->save();
    painter->setBrush(m_handleColor);
    //painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_currentPosition, m_radius, m_radius);
    //painter->restore();
}

void JoyStick::sendJoystickPosition()
{
    emit joystickMoved(m_currentPosition);
}


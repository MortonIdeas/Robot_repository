#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>
#include<QTimer>
class JoyStick : public QWidget
{
    Q_OBJECT
public:
    explicit JoyStick(QWidget *parent = nullptr);
signals:
    void joystickMoved(const QPoint &position);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void sendJoystickPosition();
private:
    QPoint m_center;
    QPoint m_currentPosition;
    bool m_pressed;
    int m_radius;
    QColor m_backgroundColor;
    QColor m_handleColor;
    QTimer m_timer;
    void drawBackground(QPainter *painter);
    void drawHandle(QPainter *painter);
};

#endif // JOYSTICK_H

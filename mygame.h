#ifndef MYGAME_H
#define MYGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPoint>
#include <QVector>

class MyGame : public QWidget
{
    Q_OBJECT
public:
    explicit MyGame(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void updateGameLogic();

private:

    bool collidesWithSnake(QPoint checkPosition);

    // game dependent variables
    static const int maxGridX = 20;
    static const int maxGridY = 15;

    QVector<QPoint> m_snake;
    QPoint m_foodPosition;
    QPoint m_direction;
    QPoint m_lastDirection;
};

#endif // MYGAME_H

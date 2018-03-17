#include "mygame.h"
#include <QPainter>
#include <QDebug>
#include <QtGlobal>

MyGame::MyGame(QWidget *parent) :
    QWidget(parent),
    m_direction(QPoint(1,0))
{
    m_snake.append(QPoint(4,maxGridY));
    m_snake.append(QPoint(3,maxGridY));
    m_snake.append(QPoint(2,maxGridY));
    m_snake.append(QPoint(1,maxGridY));
    m_snake.append(QPoint(0,maxGridY));

    m_foodPosition.setX(qrand() % maxGridX);
    m_foodPosition.setY(qrand() % maxGridY);
}

void MyGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // draw background
    painter.fillRect(this->rect(), Qt::black);

    float cellWidth = this->width() / maxGridX;
    float cellHeight = this->height() / maxGridY;

    // draw the snake
    for (int i = 0; i < m_snake.length(); i++)
    {
        painter.fillRect(m_snake.at(i).x() * cellWidth, m_snake.at(i).y() * cellHeight, cellWidth, cellHeight, Qt::green);
    }

    // draw the food
    painter.fillRect(m_foodPosition.x() * cellWidth, m_foodPosition.y() * cellHeight, cellWidth, cellHeight, Qt::red);

    // draw score
    painter.setPen(Qt::white);
    painter.drawText(20,20,QString("Score: %1").arg(m_snake.length()-5));
}

void MyGame::keyPressEvent(QKeyEvent *event)
{
    // change direction and make sure its not the direction we were comming from
    if((event->key() == Qt::Key_Left) and m_lastDirection.x() != 1)
    {
        m_direction = QPoint(-1, 0);
    }
    if((event->key() == Qt::Key_Right) and m_lastDirection.x() != -1)
    {
        m_direction = QPoint(1, 0);
    }
    if((event->key() == Qt::Key_Up) and m_lastDirection.y() != 1)
    {
        m_direction = QPoint(0, -1);
    }
    if((event->key() == Qt::Key_Down) and m_lastDirection.y() != -1)
    {
        m_direction = QPoint(0, 1);
    }
}

void MyGame::updateGameLogic()
{
    m_lastDirection = m_direction;

    // move the position of every part of the tail to its predecessors position
    for (int i = m_snake.length() - 1; i > 0; i--)
    {
        m_snake[i].setX(m_snake[i - 1].x());
        m_snake[i].setY(m_snake[i - 1].y());
    }

    // move the head according to the current direction
    QPoint nextPosition((m_snake[0].x() + m_direction.x()) % maxGridX,
                        (m_snake[0].y() + m_direction.y()) % maxGridY);

    //check for collision
    if(collidesWithSnake(nextPosition))
    {
        while(m_snake.size() > 5)
        {
            m_snake.removeLast();
        }
    }

    m_snake[0] = nextPosition;

    // wrap arround / collision with wall
    if(m_snake[0].x() < 0)
    {
        m_snake[0].setX(maxGridX - 1);
    }
    if(m_snake[0].y() < 0)
    {
        m_snake[0].setY(maxGridY - 1);
    }

    // eat the food
    if(m_snake[0] == m_foodPosition)
    {
        // respawn food
        bool foundFreeSpace = false;
        while (!foundFreeSpace)
        {
            m_foodPosition.setX(qrand() % maxGridX);
            m_foodPosition.setY(qrand() % maxGridY);
            foundFreeSpace = true;

            if(collidesWithSnake(m_foodPosition))
            {
                foundFreeSpace = false;
            }
        }

        //append tail of snake
        m_snake.append(QPoint(m_snake[m_snake.length()-1].x(), m_snake[m_snake.length()-1].y()));
    }

    // rerender
    this->update();
}

bool MyGame::collidesWithSnake(QPoint checkPosition)
{
    for (const QPoint partOfSnake : m_snake)
    {
        if (partOfSnake == checkPosition)
        {
            return true;
        }
    }
    return false;
}

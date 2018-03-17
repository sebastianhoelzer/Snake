#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, ui->myGame, &MyGame::updateGameLogic);
    m_timer->start(200);
}

MainWindow::~MainWindow()
{
    m_timer->stop();
    delete ui;
}

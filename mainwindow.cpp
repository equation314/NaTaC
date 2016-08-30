#include "player.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Player::SetCurrentPlayer(new Player(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

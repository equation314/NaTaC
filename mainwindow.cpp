#include "player.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Player::SetSelf(new Player(0));
    Player::SetCurrentPlayerId(0);
    updateResource();

    connect(ui->widget_map, &MapWidget::buildingBuilt, this, &MainWindow::onBuildingBuilt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateResource()
{
    ui->label_brick->setText(QString::number(Player::Self()->ResourceAt(0)));
    ui->label_lumber->setText(QString::number(Player::Self()->ResourceAt(1)));
    ui->label_wool->setText(QString::number(Player::Self()->ResourceAt(2)));
    ui->label_grain->setText(QString::number(Player::Self()->ResourceAt(3)));
    ui->label_ore->setText(QString::number(Player::Self()->ResourceAt(4)));

    if (Player::Self()->Id() == Player::CurrentPlayerId())
    {
        if (ui->pushButton_road->isChecked() && !Player::Self()->CanbuildRoad())
        {
            ui->widget_map->SetCurrentBuilding(Building::NoneType);
            ui->pushButton_road->setChecked(false);
        }
        if (ui->pushButton_village->isChecked() && !Player::Self()->CanbuildVillage())
        {
            ui->widget_map->SetCurrentBuilding(Building::NoneType);
            ui->pushButton_village->setChecked(false);
        }
        if (ui->pushButton_city->isChecked() && !Player::Self()->CanbuildCity())
        {
            ui->widget_map->SetCurrentBuilding(Building::NoneType);
            ui->pushButton_city->setChecked(false);
        }
        ui->pushButton_road->setEnabled(Player::Self()->CanbuildRoad());
        ui->pushButton_village->setEnabled(Player::Self()->CanbuildVillage());
        ui->pushButton_city->setEnabled(Player::Self()->CanbuildCity());
        ui->pushButton_dev->setEnabled(Player::Self()->CanUseDevelopmentCard());
    }
    else
    {
        ui->widget_map->SetCurrentBuilding(Building::NoneType);
        ui->pushButton_road->setEnabled(false);
        ui->pushButton_village->setEnabled(false);
        ui->pushButton_city->setEnabled(false);
        ui->pushButton_dev->setEnabled(false);
        ui->pushButton_road->setChecked(false);
        ui->pushButton_village->setChecked(false);
        ui->pushButton_city->setChecked(false);
    }
}



void MainWindow::onBuildingBuilt(Building* building, int id)
{
    updateResource();
}

void MainWindow::on_pushButton_road_clicked(bool checked)
{
    if (!checked)
        ui->widget_map->SetCurrentBuilding(Building::NoneType);
    else
    {
        ui->widget_map->SetCurrentBuilding(Building::RoadType);
        ui->pushButton_village->setChecked(false);
        ui->pushButton_city->setChecked(false);
    }
}

void MainWindow::on_pushButton_village_clicked(bool checked)
{
    if (!checked)
        ui->widget_map->SetCurrentBuilding(Building::NoneType);
    else
    {
        ui->widget_map->SetCurrentBuilding(Building::VillageType);
        ui->pushButton_road->setChecked(false);
        ui->pushButton_city->setChecked(false);
    }
}

void MainWindow::on_pushButton_city_clicked(bool checked)
{
    if (!checked)
        ui->widget_map->SetCurrentBuilding(Building::NoneType);
    else
    {
        ui->widget_map->SetCurrentBuilding(Building::CityType);
        ui->pushButton_road->setChecked(false);
        ui->pushButton_village->setChecked(false);
    }
}

void MainWindow::on_pushButton_dev_clicked()
{

}

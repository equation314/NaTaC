#include "player.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMimeData>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dice_time_elapsed(0)
{
    ui->setupUi(this);
    Player::SetSelf(new Player(0));
    Player::SetCurrentPlayerId(0);
    updateResource();

    connect(ui->widget_map, &MapWidget::buildingBuilt, this, &MainWindow::onBuildingBuilt);
    connect(&m_dice_timer, &QTimer::timeout, this, [this]()
    {
        m_dice_time_elapsed += 10;
        bool ok;
        if (m_dice_time_elapsed <= 500)
            ok = true;
        else if (m_dice_time_elapsed <= 1000)
            ok = m_dice_time_elapsed % 50 == 0;
        else if (m_dice_time_elapsed <= 2000)
            ok = m_dice_time_elapsed % 100 == 0;
        else
            ok = m_dice_time_elapsed % 200 == 0;
        //qDebug()<<m_dice_time_elapsed<<' '<<ok;
        if (ok)
        {
            int x = rand() % 6 + 1, y = rand() % 6 + 1;
            ui->label_dice_1->setPixmap(QString(":/img/img/%1.png").arg(x));
            ui->label_dice_2->setPixmap(QString(":/img/img/%1.png").arg(y));
            m_current_number = x + y;
        }
        if (m_dice_time_elapsed >= 3600)
        {
            m_dice_timer.stop();
            m_dice_time_elapsed = 0;
            emit onDiceFinished();
        }
    });
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



void MainWindow::onDiceFinished()
{
    qDebug()<<m_current_number;
}

void MainWindow::onBuildingBuilt(Building* building, int id)
{
    updateResource();

    ui->label_road_count->setText(QString::number(Player::Self()->RoadCount()));
    ui->label_village_count->setText(QString::number(Player::Self()->VillageCount()));
    ui->label_city_count->setText(QString::number(Player::Self()->CityCount()));
    ui->label_score->setText(QString::number(Player::Self()->Score()));
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

void MainWindow::on_pushButton_dice_clicked()
{
    m_dice_timer.start(10);
}

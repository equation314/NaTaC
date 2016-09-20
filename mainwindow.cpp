#include "player.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMimeData>
#include <QMouseEvent>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dice_time_elapsed(0)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(1, 1);

    Player::SetSelf(new Player(0, "Player0"));
    Player::SetCurrentPlayerId(0);
    ui->label_user->setText(Player::Self()->ColorName());

    updateResource();
    loadMap();

    connect(&m_dice_timer, &QTimer::timeout, this, &MainWindow::onDiceTimerTimout);
    connect(Player::Self(), &Player::ready, this, &MainWindow::on_pushButton_finish_clicked);
    connect(ui->widget_map, &MapWidget::obtainedResources, this, &MainWindow::onObtainedResources);
    connect(ui->widget_map, &MapWidget::buildingBuilt, this, &MainWindow::onBuildingBuilt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage(const QString& message)
{
    QString text = QString("[%1]%2").arg(QTime::currentTime().toString("hh:mm:ss")).arg(Player::Self()->ColorName()) + message;
    ui->textEdit->append(text);
}

void MainWindow::loadMap()
{
    Const::Resource type[Const::TILE_COUNT];
    int num[Const::TILE_COUNT] = {0};

    for (int i = 0; i < Const::TILE_COUNT; i++)
    {
        type[i] = Const::Resource(rand() % 6);
        if (type[i] != Const::Desert) num[i] = rand()%3+6;//rand() % 12 + 1;
    }
    ui->widget_map->Load(type, num);
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

void MainWindow::onDiceTimerTimout()
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
    if (ok)
    {
        int x = rand() % 6 + 1, y = rand() % 6 + 1;
        ui->label_dice_1->setPixmap(QString(":/img/img/%1.png").arg(x));
        ui->label_dice_2->setPixmap(QString(":/img/img/%1.png").arg(y));
        m_current_number = x + y;
    }
    if (m_dice_time_elapsed >= 3000)
    {
        m_dice_timer.stop();
        m_dice_time_elapsed = 0;
        emit onDiceFinished();
    }
}

void MainWindow::onDiceFinished()
{
    qDebug()<<m_current_number;
    sendMessage(tr(" rolled the number <strong>%1</strong>.").arg(m_current_number));
    ui->widget_map->ObtainResources(m_current_number);
    ui->pushButton_trade->setEnabled(true);
    ui->pushButton_finish->setEnabled(true);
    updateResource();
}

void MainWindow::onObtainedResources(int cnt[])
{
    bool ok = false;
    QString message = tr(" obtained ");
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (cnt[i])
        {
            ok = true;
            message += QString("<span style=\"color:%1\">%2</span> x%3, ").arg(Const::RESOURCE_COLOR[i].name()).arg(Const::RESOURCE_NAME[i]).arg(cnt[i]);
        }
    message.replace(message.length() - 2, 2, ".");
    if (ok) sendMessage(message);
}

void MainWindow::onBuildingBuilt(Building* building, int /*id*/)
{
    updateResource();

    ui->label_road_count->setText(QString::number(Player::Self()->RoadCount()));
    ui->label_village_count->setText(QString::number(Player::Self()->VillageCount()));
    ui->label_city_count->setText(QString::number(Player::Self()->CityCount()));
    ui->label_score->setText(QString::number(Player::Self()->Score()));

    switch (building->Type())
    {
    case Building::RoadType:
        sendMessage(tr(" built a road."));
        break;
    case Building::VillageType:
        sendMessage(tr(" built a village."));
        sendMessage(tr(" got 1 point."));
        break;
    case Building::CityType:
        sendMessage(tr(" upgraded a village to a city."));
        sendMessage(tr(" got 1 point."));
        break;
    default:
        break;
    }
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
    sendMessage(tr(" bought a development card."));
    Player::Self()->BuyDevelopmentCard();
    updateResource();
}

void MainWindow::on_pushButton_dice_clicked()
{
    m_dice_timer.start(10);
    ui->pushButton_dice->setEnabled(false);
}

void MainWindow::on_pushButton_finish_clicked()
{
    ui->widget_map->SetCurrentBuilding(Building::NoneType);
    ui->pushButton_road->setEnabled(false);
    ui->pushButton_village->setEnabled(false);
    ui->pushButton_city->setEnabled(false);
    ui->pushButton_dev->setEnabled(false);
    ui->pushButton_trade->setEnabled(false);
    ui->pushButton_dice->setEnabled(true);
    ui->pushButton_finish->setEnabled(false);
    ui->pushButton_road->setChecked(false);
    ui->pushButton_village->setChecked(false);
    ui->pushButton_city->setChecked(false);
}

void MainWindow::on_pushButton_send_clicked()
{
    QString message = ui->lineEdit->text();
    if (message.trimmed().isEmpty()) return;
    ui->lineEdit->clear();
    sendMessage(": " + message.toHtmlEscaped());
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_send_clicked();
}

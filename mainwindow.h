#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QTimer>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class Tile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void onPrepareFinished();
    void onDiceTimerTimout();
    void onDiceFinished();
    void onObtainedResources(int cnt[Const::RESOURCE_COUNT]);
    void onRobberMoved(Tile* tile);
    void onBuildingBuilt(Building* building);

    void on_pushButton_road_clicked(bool checked);
    void on_pushButton_village_clicked(bool checked);
    void on_pushButton_city_clicked(bool checked);
    void on_pushButton_trade_clicked();
    void on_pushButton_dev_clicked();
    void on_pushButton_dice_clicked();
    void on_pushButton_finish_clicked();
    void on_pushButton_send_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow* ui;
    int m_dice_time_elapsed, m_current_number;
    QTimer m_dice_timer;

    void sendMessage(const QString& message);
    void loadMap();
    void updateResource();
};

#endif // MAINWINDOW_H

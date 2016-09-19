#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QTimer>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onBuildingBuilt(Building* building, int id);

private slots:
    void onDiceFinished();

    void on_pushButton_road_clicked(bool checked);
    void on_pushButton_village_clicked(bool checked);
    void on_pushButton_city_clicked(bool checked);
    void on_pushButton_dev_clicked();
    void on_pushButton_dice_clicked();

private:
    Ui::MainWindow *ui;
    int m_dice_time_elapsed, m_current_number;
    QTimer m_dice_timer;

    void updateResource();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

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
    void on_pushButton_road_clicked(bool checked);
    void on_pushButton_village_clicked(bool checked);
    void on_pushButton_city_clicked(bool checked);
    void on_pushButton_dev_clicked();

private:
    Ui::MainWindow *ui;

    void updateResource();
};

#endif // MAINWINDOW_H

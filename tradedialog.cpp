#include "tradedialog.h"
#include "ui_tradedialog.h"

#include <QDebug>

TradeDialog::TradeDialog(Player* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TradeDialog),
    m_player(player)
{
    ui->setupUi(this);

    list_user = new QListWidget(ui->comboBox_user);
    list_1 = new QListWidget(ui->comboBox_1);
    list_2 = new QListWidget(ui->comboBox_2);

    ui->label_user->setText(player->ColorName());

    m_user_list.append(Player::Self());
    //ui->comboBox_user->addItem("Bank", 0);
    QListWidgetItem* item = new QListWidgetItem("Bank", list_user);
    item->setData(Qt::UserRole, 0);
    list_user->addItem(item);
    for (int i = 0; i < m_user_list.size(); i++)
    {
        Player* user = m_user_list[i];
        QListWidgetItem* item = new QListWidgetItem(user->Name(), list_user);
        item->setData(Qt::UserRole, -(i + 1));
        item->setTextColor(user->Color());
        list_user->addItem(item);
    }

    for (int i = 0 ; i < Const::RESOURCE_COUNT; i++)
        if (player->ResourceAt(i)) addComboBoxItem(i, list_1);

    ui->comboBox_user->setModel(list_user->model());
    ui->comboBox_1->setModel(list_1->model());
    ui->comboBox_2->setModel(list_2->model());
    ui->comboBox_user->setView(list_user);
    ui->comboBox_1->setView(list_1);
    ui->comboBox_2->setView(list_2);

    ui->comboBox_user->setCurrentIndex(0);
}

TradeDialog::~TradeDialog()
{
    delete ui;
}

void TradeDialog::addComboBoxItem(int id, QListWidget* list)
{
    QString text = Const::RESOURCE_NAME[id];
    text[0] = text[0].toUpper();
    QListWidgetItem* item = new QListWidgetItem(text, list);
    item->setData(Qt::UserRole, id);
    item->setTextColor(Const::RESOURCE_COLOR[id]);
    list->addItem(item);
}

void TradeDialog::on_comboBox_user_currentIndexChanged(int /*index*/)
{
    list_2->clear();
    int id = ui->comboBox_user->currentData(Qt::UserRole).toInt();
    if (id >= 0) // bank, ports
    {
        ui->comboBox_user->setStyleSheet("");
        for (int i = 0 ; i < Const::RESOURCE_COUNT; i++)
            addComboBoxItem(i, list_2);
    }
    else // users
    {
        ui->comboBox_user->setStyleSheet("color:" + m_user_list[-id - 1]->Color().name());
        for (int i = 0 ; i < Const::RESOURCE_COUNT; i++)
            addComboBoxItem(i, list_2);
    }
    ui->comboBox_1->setCurrentIndex(-1);
    ui->comboBox_1->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(0);
}

void TradeDialog::on_comboBox_1_currentIndexChanged(int index)
{
    if (index < 0) return;
    int resId = ui->comboBox_1->currentData(Qt::UserRole).toInt();
    ui->comboBox_1->setStyleSheet("color:" + Const::RESOURCE_COLOR[resId].name());
    ui->spinBox_1->setMaximum(m_player->ResourceAt(resId));
    ui->spinBox_1->setValue(1);
    ui->spinBox_1->setReadOnly(false);
    if (ui->comboBox_user->currentData(Qt::UserRole).toInt() >= 0)
    {
        ui->spinBox_1->setReadOnly(true);
        ui->spinBox_1->setMaximum(4);
        ui->spinBox_1->setValue(4);
    }
}

void TradeDialog::on_comboBox_2_currentIndexChanged(int index)
{
    if (index < 0) return;
    int resId = ui->comboBox_2->currentData(Qt::UserRole).toInt();
    ui->comboBox_2->setStyleSheet("color:" + Const::RESOURCE_COLOR[resId].name());
    ui->spinBox_2->setMaximum(9);
    ui->spinBox_2->setValue(1);
    ui->spinBox_2->setReadOnly(false);
    if (ui->comboBox_user->currentData(Qt::UserRole).toInt() >= 0)
    {
        ui->spinBox_2->setReadOnly(true);
        ui->spinBox_2->setValue(1);
    }
}

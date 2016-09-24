#include "tradedialog.h"
#include "ui_tradedialog.h"

#include <QDebug>
#include <QMessageBox>

TradeDialog::TradeDialog(Player* player, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::TradeDialog),
    m_player(player)
{
    ui->setupUi(this);
    ui->label_user->setText(player->ColorName());

    list_user = new QListWidget(ui->comboBox_user);
    list_1 = new QListWidget(ui->comboBox_1);
    list_2 = new QListWidget(ui->comboBox_2);

    m_user_list.append(Player::Self());
    m_port_list.append(std::make_tuple(tr("Bank"), 4, -1));
    m_port_list.append(std::make_tuple(tr("Port1"), 3, -1));
    m_port_list.append(std::make_tuple(tr("Port2"), 2, (int)Const::Lumber));
    for (int i = 0; i < m_port_list.size(); i++)
    {
        auto tuple = m_port_list[i];
        QListWidgetItem* item = new QListWidgetItem(std::get<0>(tuple), list_user);
        item->setData(Qt::UserRole, i);
        item->setTextColor(Qt::black);
        list_user->addItem(item);
    }
    for (int i = 0; i < m_user_list.size(); i++)
    {
        Player* user = m_user_list[i];
        QListWidgetItem* item = new QListWidgetItem(user->Name(), list_user);
        item->setData(Qt::UserRole, -(i + 1));
        item->setTextColor(user->Color());
        list_user->addItem(item);
    }

    for (int i = 0 ; i < Const::RESOURCE_COUNT; i++)
        addComboBoxItem(i, list_2);

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

void TradeDialog::setResourceTableHidden(bool hidden)
{
    ui->resourceTable_1->setHidden(hidden);
    ui->resourceTable_2->setHidden(hidden);
    ui->comboBox_1->setHidden(!hidden);
    ui->comboBox_2->setHidden(!hidden);
    ui->spinBox_1->setHidden(!hidden);
    ui->spinBox_2->setHidden(!hidden);
    this->adjustSize();
    this->resize(0, 0);
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
    int id = ui->comboBox_user->currentData(Qt::UserRole).toInt();
    if (id >= 0) // bank, ports
    {
        setResourceTableHidden(true);
        ui->comboBox_user->setStyleSheet("");
        list_1->clear();
        if (std::get<2>(m_port_list[id]) == -1)
        {
            for (int i = 0 ; i < Const::RESOURCE_COUNT; i++)
                addComboBoxItem(i, list_1);
        }
        else
            addComboBoxItem(std::get<2>(m_port_list[id]), list_1);

        ui->comboBox_1->setCurrentIndex(-1);
        ui->spinBox_1->setMaximum(std::get<1>(m_port_list[id]));
        ui->spinBox_1->setValue(ui->spinBox_1->maximum());
    }
    else // users
    {
        setResourceTableHidden(false);
        ui->comboBox_user->setStyleSheet("color:" + m_user_list[-id - 1]->Color().name());
        QList<QPair<int, int>> ranges;
        for (int i = 0; i < Const::RESOURCE_COUNT; i++)
            ranges.append(qMakePair(0, m_player->ResourceAt(i)));
        ui->resourceTable_1->SetRanges(ranges);
    }
    ui->comboBox_1->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
}

void TradeDialog::on_comboBox_1_currentIndexChanged(int index)
{
    if (index < 0) return;

    int resId = ui->comboBox_1->currentData(Qt::UserRole).toInt();
    ui->comboBox_1->setStyleSheet("color:" + Const::RESOURCE_COLOR[resId].name());
}

void TradeDialog::on_comboBox_2_currentIndexChanged(int /*index*/)
{
    int resId = ui->comboBox_2->currentData(Qt::UserRole).toInt();
    ui->comboBox_2->setStyleSheet("color:" + Const::RESOURCE_COLOR[resId].name());
}

void TradeDialog::on_pushButton_trade_clicked()
{
    int id = ui->comboBox_user->currentData(Qt::UserRole).toInt();
    if (id >= 0)
    {
        int resId1 = ui->comboBox_1->currentData(Qt::UserRole).toInt();
        int resId2 = ui->comboBox_2->currentData(Qt::UserRole).toInt();
        if (resId1 == resId2)
        {
            QMessageBox::information(this, tr("Fail to Trade"), tr("You cannot trade the same resources."));
            return;
        }
        if (m_player->ResourceAt(resId1) < ui->spinBox_1->value())
        {
            QMessageBox::information(this, tr("Fail to Trade"), tr("You don't have enough resources."));
            return;
        }
    }
    else
    {
        int s1 = 0, s2 = 0;
        for (int i = 0; i < Const::RESOURCE_COUNT; i++)
            s1 += ui->resourceTable_1->ResourceAt(i);
        for (int i = 0; i < Const::RESOURCE_COUNT; i++)
            s2 += ui->resourceTable_2->ResourceAt(i);
        if (!s1)
        {
            QMessageBox::information(this, tr("Cannot Give Away Resources"), tr("Please change your resource amount."));
            return;
        }
        else if (!s2)
        {
            QMessageBox::information(this, tr("Cannot Give Away Resources"), tr("Please change %1's resource amount.").arg(ui->comboBox_user->currentText()));
            return;
        }
    }
}

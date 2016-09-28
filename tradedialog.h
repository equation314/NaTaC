#ifndef TRADEDIALOG_H
#define TRADEDIALOG_H

#include "player.h"

#include <QDialog>
#include <QListWidget>

namespace Ui
{
class TradeDialog;
}

class TradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TradeDialog(Player* player, QWidget* parent = nullptr);
    ~TradeDialog();

    QString TraderName() const { return m_trader_name; }
    int InResourceAt(int p) const { return m_in[p]; }
    int OutResourceAt(int p) const { return m_out[p]; }

private slots:
    void on_comboBox_user_currentIndexChanged(int index);
    void on_comboBox_1_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_pushButton_trade_clicked();

private:
    Ui::TradeDialog* ui;
    Player* m_player;
    QString m_trader_name;
    int m_in[Const::RESOURCE_COUNT];
    int m_out[Const::RESOURCE_COUNT];

    QListWidget* m_listWidget_user, *m_listWidget_1, *m_listWidget_2;
    QList<Player*> m_user_list;
    QList<std::tuple<QString, int, int>> m_harbor_list;

    void setResourceTableHidden(bool hidden);
    void addComboBoxItem(int id, QListWidget* list);
};

#endif // TRADEDIALOG_H

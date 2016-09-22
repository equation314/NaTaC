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


private slots:
    void on_comboBox_user_currentIndexChanged(int index);
    void on_comboBox_1_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_trade_clicked();

private:
    Ui::TradeDialog *ui;
    Player* m_player;

    QListWidget *list_user, *list_1, *list_2;
    QList<Player*> m_user_list;

    void setResourceTableHidden(bool hidden);
    void addComboBoxItem(int id, QListWidget* list);
};

#endif // TRADEDIALOG_H

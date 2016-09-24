#ifndef DEVLOPMENTCARDDIALOG_H
#define DEVLOPMENTCARDDIALOG_H

#include "const.h"

#include <QDialog>

namespace Ui
{
class DevlopmentCardDialog;
}

class DevlopmentCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DevlopmentCardDialog(Const::DevelopmentCardType type, bool canUse, QWidget* parent = 0);
    ~DevlopmentCardDialog();

private:
    Ui::DevlopmentCardDialog* ui;
};

#endif // DEVLOPMENTCARDDIALOG_H

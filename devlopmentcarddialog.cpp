#include "devlopmentcarddialog.h"
#include "ui_devlopmentcarddialog.h"

DevlopmentCardDialog::DevlopmentCardDialog(Const::DevelopmentCardType type, bool canUse, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::DevlopmentCardDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setFixedSize(this->sizeHint());
    ui->pushButton_use->setEnabled(canUse);
    ui->label_card->setText(Const::DEV_CARD_NAME[(size_t)type]);
}

DevlopmentCardDialog::~DevlopmentCardDialog()
{
    delete ui;
}

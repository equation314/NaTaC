#include "const.h"
#include "resourcetable.h"

#include <QHeaderView>
#include <QSpinBox>
#include <QDebug>

ResourceTableItemDelegate::ResourceTableItemDelegate(QObject* parent) :
    QItemDelegate(parent)
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        m_ranges.append(qMakePair(0, 9));
}

QWidget* ResourceTableItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
    if (index.row() != 1) return nullptr;

    QSpinBox* editor = new QSpinBox(parent);
    editor->setAlignment(Qt::AlignCenter);
    editor->setMinimum(m_ranges[index.column()].first);
    editor->setMaximum(m_ranges[index.column()].second);
    return editor;
}

void ResourceTableItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (index.row() != 1) return;

    QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(index.model()->data(index, Qt::DisplayRole).toInt());
}

void ResourceTableItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (index.row() != 1) return;

    QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
    model->setData(index, spinBox->value(), Qt::DisplayRole);
    model->setData(index, spinBox->value(), Qt::ToolTipRole);
}

bool ResourceTableItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (!index.row()) return false;

    return QItemDelegate::editorEvent(event, model, option, index);
}






ResourceTable::ResourceTable(QWidget* parent) :
    QTableView(parent),
    m_model(new QStandardItemModel(this)), m_item_delegate(new ResourceTableItemDelegate(this))
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    this->setSelectionMode(QAbstractItemView::NoSelection);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setMinimumSectionSize(60);
    this->horizontalHeader()->setDefaultSectionSize(60);

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    this->verticalHeader()->setHighlightSections(false);
    this->verticalHeader()->setFixedWidth(60);

    this->setModel(m_model);
    this->setItemDelegate(m_item_delegate);

    m_model->setRowCount(2);
    m_model->setColumnCount(Const::RESOURCE_COUNT);
    m_model->setVerticalHeaderLabels({tr("Resource"), tr("Amount")});
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
    {
        QString text = Const::RESOURCE_NAME[i];
        text[0] = text[0].toUpper();
        setItemData(0, i, text);
        setItemData(1, i, 0);
        m_model->setData(m_model->index(0, i), Const::RESOURCE_COLOR[i], Qt::TextColorRole);
    }

    this->setMinimumWidth(Const::RESOURCE_COUNT * 60 + this->verticalHeader()->width() + 2 * this->frameWidth());
}

#ifndef RESOURCETABLE_H
#define RESOURCETABLE_H

#include <QTableView>
#include <QStandardItemModel>
#include <QItemDelegate>

class ResourceTableItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ResourceTableItemDelegate(QObject* parent = nullptr);
    ~ResourceTableItemDelegate() {}

    void SetRanges(const QList<QPair<int, int>>& ranges) { m_ranges = ranges; }

protected:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

private:
    QList<QPair<int, int>> m_ranges;
};



class ResourceTable : public QTableView
{
public:
    explicit ResourceTable(QWidget* parent = nullptr);
    ~ResourceTable() {}

    // Getter member functions
    int ResourceAt(int p) { return m_model->item(1, p)->data(Qt::DisplayRole).toInt(); }

    // Setter member functions
    void SetRanges(const QList<QPair<int, int>>& ranges) { m_item_delegate->SetRanges(ranges); }

private:
    QStandardItemModel* m_model;
    ResourceTableItemDelegate* m_item_delegate;

    void setItemData(int r, int c, const QVariant& value)
    {
        m_model->setData(m_model->index(r, c), value, Qt::DisplayRole);
        m_model->setData(m_model->index(r, c), Qt::AlignCenter, Qt::TextAlignmentRole);
        m_model->setData(m_model->index(r, c), value.toString(), Qt::ToolTipRole);
    }
};

#endif // RESOURCETABLE_H

#ifndef QUANTITYDELEGATE_H
#define QUANTITYDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>

class QuantityDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QuantityDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // QUANTITYDELEGATE_H

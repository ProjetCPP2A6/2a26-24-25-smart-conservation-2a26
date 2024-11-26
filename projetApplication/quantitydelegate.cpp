#include "QuantityDelegate.h"

QuantityDelegate::QuantityDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* QuantityDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setValidator(new QIntValidator(0, 10000, editor));  // Permet uniquement les entiers positifs
    return editor;
}

void QuantityDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        lineEdit->setText(value);
    }
}

void QuantityDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }
}

void QuantityDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
    editor->setGeometry(option.rect);
}

#ifndef NUMERICDELEGATE_H
#define NUMERICDELEGATE_H

#include <QStyledItemDelegate>

class NumericDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
private:
    void forceKeyboard(QWidget *widget) const;

};

#endif // NUMERICDELEGATE_H

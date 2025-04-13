#include "NumericDelegate.h"

#include <QGuiApplication>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QTimer>

QWidget *NumericDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    forceKeyboard(editor);
    editor->setInputMethodHints(Qt::ImhDigitsOnly);
    return editor;
}

// void NumericDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
//     QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//     if (lineEdit)
//         model->setData(index, lineEdit->text());

//     QAbstractItemView *view = qobject_cast<QAbstractItemView *>(editor->parentWidget()->parent());
//     if (view) {
//         int nextRow = index.row() + 1;
//         if (nextRow < model->rowCount()) {
//             QModelIndex nextIndex = model->index(nextRow, index.column());
//             QTimer::singleShot(0, view, [view, nextIndex]() {
//                 view->setCurrentIndex(nextIndex);
//                 view->edit(nextIndex);
//                 QGuiApplication::inputMethod()->show();
//             });
//         }
//     }
// }

void NumericDelegate::forceKeyboard(QWidget *widget) const
{
    widget->setFocus();
    QTimer::singleShot(00, []() {
        QInputMethod *im = QGuiApplication::inputMethod();
        if (im)
            im->hide();
    });
}

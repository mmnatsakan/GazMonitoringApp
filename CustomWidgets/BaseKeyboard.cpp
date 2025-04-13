#include "BaseKeyboard.h"

#include <QPushButton>
#include <QBoxLayout>


BaseKeyboard::BaseKeyboard(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setSpacing(2);
    layout->setContentsMargins(2, 2, 2, 2);
}

void BaseKeyboard::createButtons(const QList<QStringList> &rows) {
    int row = 0;
    for (const QStringList &keys : rows) {
        int col = 0;
        for (const QString &key : keys) {
            if (key.trimmed().isEmpty())
                continue;
            QPushButton *button = new QPushButton(key, this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            layout->addWidget(button, row, col);
            connect(button, &QPushButton::clicked, this, [=](){ emit keyPressed(button->text()); });
            col++;
        }
        row++;
    }
}

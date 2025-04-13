#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);
    void setLabelText(const QString& text);
    QString getTextValue() const;

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();

    QWidget* m_mainWidget;

    QLineEdit* m_lineEdit;
    QLabel* m_label;

    QPushButton* m_acceptButton;
    QPushButton* m_cancelButton;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // INPUTDIALOG_H

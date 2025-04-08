#ifndef CHECKLISTTEXTEDITOR_H
#define CHECKLISTTEXTEDITOR_H

#include <QDialog>

class QCheckBox;
class QTextEdit;
class QPushButton;

class CheckListTextEditor : public QDialog
{
    Q_OBJECT
public:
    explicit CheckListTextEditor(QWidget *parent = nullptr);
    void setData(const QString &data);
    QString getData() const;

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();

    QWidget* m_mainWidget;

    QList<QCheckBox*> m_checkBoxes;
    QTextEdit *m_textEdit;

    QPushButton* m_acceptButton;
    QPushButton* m_cancelButton;
};

#endif // CHECKLISTTEXTEDITOR_H

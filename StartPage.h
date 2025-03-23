#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;

class StartPage : public QWidget
{
    Q_OBJECT
public:
    explicit StartPage(QWidget *parent = nullptr);
    QMap<QString, QString> getMainData() const;

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();

    QWidget* m_mainWidget;
    QWidget* m_centralWidget;

    QLabel* m_ttLabel;
    QLabel* m_hskichLabel;

    QComboBox* m_ttComboBox;
    QComboBox* m_hskichComboBox;

    QPushButton* m_enterButton;
    QPushButton* m_cancelButton;

    QString m_mkod;
    QString m_hskichkod;

signals:
    void mainDataReady();
};

#endif // STARTPAGE_H

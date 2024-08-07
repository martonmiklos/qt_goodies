#pragma once

#include <QTableView>

class QSettings;

class TableViewWithSettings : public QTableView
{
    Q_OBJECT
public:
    TableViewWithSettings(QWidget *parent = nullptr);

    void loadSettings(QSettings *settings);
    void saveSettings(QSettings *settings);
    void addHiddenColumn(int column);

private:
    QList<int> m_hiddenColumns;
};

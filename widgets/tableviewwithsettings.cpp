#include "tableviewwithsettings.h"

#include <QAction>
#include <QHeaderView>
#include <QSettings>

TableViewWithSettings::TableViewWithSettings(QWidget *parent) :
    QTableView(parent)
{

}

void TableViewWithSettings::loadSettings(QSettings *settings)
{
    if (!model())
        return;
    horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
    settings->beginGroup(this->objectName());
    int settingsColCount = settings->beginReadArray("columns");
    for (int col = 0; col<model()->columnCount(); col++) {
        if (m_hiddenColumns.contains(col)) {
            setColumnHidden(col, true);
            continue;
        }
        settings->setArrayIndex(col);
        if (col < settingsColCount) {
            if (horizontalHeader()->sectionResizeMode(col) == QHeaderView::Interactive)
                setColumnWidth(col, settings->value("width").toInt());
            setColumnHidden(col, settings->value("hidden", false).toBool());
        }
        auto actionTitle = model()->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
        if (actionTitle.isEmpty())
            actionTitle = model()->headerData(col, Qt::Horizontal, Qt::ToolTipRole).toString();
        auto showColumnAction = new QAction(actionTitle, this);
        showColumnAction->setCheckable(true);
        showColumnAction->setChecked(!isColumnHidden(col));
        horizontalHeader()->addAction(showColumnAction);
        connect(showColumnAction, &QAction::triggered, this, [=](bool checked) {
            setColumnHidden(col, !checked);
        });
    }
    settings->endArray();
    settings->endGroup();
}

void TableViewWithSettings::saveSettings(QSettings *settings)
{
    if (!model())
        return;

    settings->beginGroup(this->objectName());
    settings->beginWriteArray("columns");
    for (int col = 0; col<model()->columnCount(); col++) {
        settings->setArrayIndex(col);
        if (horizontalHeader()->sectionResizeMode(col) == QHeaderView::Interactive && !isColumnHidden(col)) {
            int width = columnWidth(col);
            if (width < 50)
                width = 50;
            settings->setValue("width", width);
        }
        settings->setValue("hidden", isColumnHidden(col));
    }
    settings->endArray();
    settings->endGroup();
}

void TableViewWithSettings::addHiddenColumn(int column)
{
    if (!m_hiddenColumns.contains(column))
        m_hiddenColumns.append(column);
    setColumnHidden(column, true);
}

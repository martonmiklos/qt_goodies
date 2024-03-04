#pragma once

#include <QAction>
#include <QHeaderView>
#include <QList>
#include <QWidget>
#include <QSettings>

template <class T>
class RestorableHeaderWidget : public T
{
public:
    RestorableHeaderWidget(QWidget *parent) :
        T(parent)
    {
        this->horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
        this->horizontalHeader()->setSectionsMovable(true);
    }

    void saveHeaderSettings(QSettings &settings)
    {
        settings.setValue("HeaderState", this->horizontalHeader()->saveState());
        settings.beginGroup("ColumnsWidths");
        for (int col = 0; col<this->model()->columnCount(); col++) {
            settings.setValue(QString::number(col), this->columnWidth(col));
        }
        settings.endGroup();

        settings.beginGroup("ColumnsVisiblity");
        for (int col = 0; col<this->model()->columnCount(); col++) {
            settings.setValue(QString::number(col), this->isColumnHidden(col));
        }
        settings.endGroup();
    }

    void restoreHeaderSettings(QSettings &settings)
    {
        this->horizontalHeader()->restoreState(settings.value("HeaderState").toByteArray());
        settings.beginGroup("ColumnsWidths");
        for (int col = 0; col<this->model()->columnCount(); col++) {
            int width = settings.value(QString::number(col), 0).toInt();
            if (width)
                this->setColumnWidth(col, width);
        }
        settings.endGroup();

        settings.beginGroup("ColumnsVisiblity");
        for (int col = 0; col<this->model()->columnCount(); col++) {
            bool hidden = settings.value(QString::number(col), false).toBool();
            this->setColumnHidden(col, hidden);

            auto actionText = this->model()->headerData(col, Qt::Horizontal, Qt::ToolTipRole).toString();
            if (actionText.isEmpty())
                actionText = this->model()->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
            auto *action = new QAction(actionText, this);
            action->setCheckable(true);
            action->setChecked(!hidden);
            action->setData(col);
            this->horizontalHeader()->addAction(action);
            this->connect(action, &QAction::triggered, this, [this, col](bool checked) {
                this->setColumnHidden(col, !checked);
            });
        }
        settings.endGroup();

    }
};

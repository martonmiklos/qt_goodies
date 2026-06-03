#pragma once

#include <QAction>
#include <QHeaderView>
#include <QList>
#include <QWidget>
#include <QSettings>
#include <QTreeWidget>

template <class T>
class RestorableHeaderWidget : public T
{
public:
    RestorableHeaderWidget(QWidget *parent) :
        T(parent)
    {
    }

    void init(QHeaderView *header)
    {
        m_header = header;
        m_header->setContextMenuPolicy(Qt::ActionsContextMenu);
        m_header->setSectionsMovable(true);
    }

    void saveHeaderSettings(QSettings &settings)
    {
        settings.setValue("HeaderState", m_header->saveState());
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
        m_header->restoreState(settings.value("HeaderState").toByteArray());
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
            m_header->addAction(action);
            this->connect(action, &QAction::triggered, this, [this, col](bool checked) {
                this->setColumnHidden(col, !checked);
            });
        }
        settings.endGroup();
    }
private:
    QHeaderView *m_header = nullptr; // set this to the header in the constructor
};


class RestorableTreeWidget : public RestorableHeaderWidget<QTreeWidget>
{
public:
    RestorableTreeWidget(QWidget *parent = nullptr) :
        RestorableHeaderWidget<QTreeWidget>(parent)
    {
        init(header());
    }
};
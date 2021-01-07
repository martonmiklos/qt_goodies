#pragma once

#include <QAction>
#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QMenu>
#include <QMetaEnum>


template<typename EnumType>
class QMetaEnumMenu : public QMenu
{
public:
    QMetaEnumMenu(QWidget *parent = nullptr) :
        QMenu(parent)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<EnumType>();
        for(int i = 0; i<metaEnum.keyCount();  i++) {
            auto *action = new QAction(metaEnum.valueToKey(metaEnum.value(i)));
            action->setData(metaEnum.value(i));
            addAction(action);
            m_actions.append(action);
            connect(action, &QAction::toggled, this, &QMetaEnumMenu<EnumType>::enumActionToggled);
        }
    }
    
    QMetaEnumMenu(int leftOffset = -1, int rightOffset = -1, bool orderByEnumName = false, QWidget *parent = nullptr) :
        QMenu(parent)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<EnumType>();
        if (!orderByEnumName) {
            for(int i = 0; i<metaEnum.keyCount();  i++) {
                auto *action = new QAction(trimEnumName(metaEnum.valueToKey(metaEnum.value(i)), leftOffset, rightOffset));
                action->setCheckable(true);
                action->setData(metaEnum.value(i));
                addAction(action);
                m_actions.append(action);
                connect(action, &QAction::toggled, this, &QMetaEnumMenu<EnumType>::enumActionToggled);
            }
        } else {
            QMap<QString, int> map;
            for(int i = 0; i<metaEnum.keyCount();  i++) {
                QString text = trimEnumName(metaEnum.valueToKey(metaEnum.value(i)), leftOffset, rightOffset);
                map[text] = metaEnum.value(i);
            }

            for (const auto key : map.keys()) {
                auto *action = new QAction(key);
                action->setCheckable(true);
                action->setData(map.value(key));
                addAction(action);
                m_actions.append(action);
                connect(action, &QAction::toggled, this, &QMetaEnumMenu<EnumType>::enumActionToggled);
            }
        }
    }

    virtual void setCurrentEnumValue(EnumType value)
    {
        for (auto *action : m_actions) {
            if (action->data().toInt() == value) {
                action->setChecked(true);
                break;
            }
        }
    }

    EnumType currentEnumValue(EnumType notFoundValue, bool *found = nullptr) const
    {
        for (auto *action : m_actions) {
            if (action->isChecked()) {
                if (found) *found = true;
                return static_cast<EnumType>(action->data().toInt());
            }
        }
        if (found) *found = false;
        return notFoundValue;
    }

protected:
    QList<QAction*> m_actions;

protected slots:
    virtual void enumActionToggled(bool checked)
    {
        const auto action = static_cast<QAction*>(sender());
        if (checked) {
            for (auto *other : m_actions) {
                if (other != action && other->isChecked()) {
                    other->setChecked(false);
                    return;
                }
            }
        }
    }

private:
    QString trimEnumName(const QString enumName, int leftOffset = -1, int rightOffset = -1)
    {
        QString ret = enumName;
        if (leftOffset != -1)
            ret = ret.mid(leftOffset);
        if (rightOffset != -1)
            ret = ret.mid(0, ret.length() - rightOffset);
        return ret;
    }
};


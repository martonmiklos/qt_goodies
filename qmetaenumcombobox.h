#pragma once

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QComboBox>
#include <QDebug>
#include <QMetaEnum>


template<typename EnumType>
class QMetaEnumComboBox : public QComboBox
{
public:
    enum SortMode {
        Index,
        Name
    };

    QMetaEnumComboBox(QWidget *parent = nullptr) :
        QComboBox(parent)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<EnumType>();
        for(int i = 0; i<metaEnum.keyCount();  i++)
            addItem(metaEnum.valueToKey(metaEnum.value(i)), metaEnum.value(i));
    }
    
    QMetaEnumComboBox(int leftOffset = -1, int rightOffset = -1, SortMode sortMode = Index, bool humanize = false, QWidget *parent = nullptr) :
        QComboBox(parent)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<EnumType>();
        QMultiMap<QString, EnumType> items;
        for(int i = 0; i<metaEnum.keyCount();  i++) {
            QString text = QString(metaEnum.valueToKey(metaEnum.value(i)));
            if (leftOffset != -1)
                text = text.mid(leftOffset);
            if (rightOffset != -1)
                text = text.mid(0, text.length() - rightOffset);
            if (humanize)
                text = text.replace('_', ' ');
            if (sortMode == Index)
                addItem(text, metaEnum.value(i));
            else
                items.insert(text, static_cast<EnumType>(metaEnum.value(i)));
        }

        if (sortMode == Name) {
            for(auto item = items.begin(); item != items.end(); item++)
                addItem(item.key(), item.value());
        }
    }

    void setCurrentEnumValue(EnumType value)
    {
        setCurrentIndex(findData(static_cast<int>(value)));
    }

    int findEnumValue(EnumType value)
    {
        return findData(static_cast<int>(value));
    }

    EnumType currentEnumValue() const
    {
        return static_cast<EnumType>(currentData().toInt());
    }
};


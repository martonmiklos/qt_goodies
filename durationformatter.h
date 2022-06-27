#pragma once

#include <QObject>
#include <QString>

class DurationFormatter
{
    Q_GADGET
public:
    enum TimeUnit {
        Millisec = 0,
        Sec = 1,
        Minute = 2,
        Hour = 3,
        Day = 4
    };

    enum DisplayMode {
        Textual,
        DoubleDot
    };

    Q_INVOKABLE static QString formatDuration(qreal duration, TimeUnit precision, TimeUnit inputUnit = Millisec);
    Q_INVOKABLE static QString doubleDotDuration(qreal duration, TimeUnit firstUnit, TimeUnit lastUnit, TimeUnit inputUnit = Millisec);
private:
    static quint64 DAY_IN_MS;
    static quint64 HOUR_IN_MS;
    static quint64 MINUTE_IN_MS;
};
Q_DECLARE_METATYPE(DurationFormatter)

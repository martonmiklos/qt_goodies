#ifndef DURATIONFORMATTER_H
#define DURATIONFORMATTER_H

#include <QString>

class DurationFormatter
{
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

    static QString formatDuration(qreal duration, TimeUnit precision, TimeUnit inputUnit = Millisec);
    static QString doubleDotDuration(qreal duration, TimeUnit firstUnit, TimeUnit lastUnit, TimeUnit inputUnit = Millisec);
    static quint64 DAY_IN_MS;
    static quint64 HOUR_IN_MS;
    static quint64 MINUTE_IN_MS;
};

#endif // DURATIONFORMATTER_H

#include "durationformatter.h"

#include <QObject>

quint64 DurationFormatter::MINUTE_IN_MS = 1000 * 60;
quint64 DurationFormatter::HOUR_IN_MS = 60 * 1000 * 60;
quint64 DurationFormatter::DAY_IN_MS = 24 * 60 * 1000 * 60;

QString DurationFormatter::formatDuration(qreal duration, DurationFormatter::TimeUnit precision, DurationFormatter::TimeUnit inputUnit)
{
    if (duration == 0) {
        switch (precision) {
        case DurationFormatter::Millisec:
            return QObject::tr("0 ms");
        case DurationFormatter::Sec:
            return QObject::tr("0 mp");
        case DurationFormatter::Minute:
            return QObject::tr("0 perc");
        case DurationFormatter::Hour:
            return QObject::tr("0 óra");
        case DurationFormatter::Day:
            return QObject::tr("0 nap");
        }
    }

    QString ret;
    quint64 durationInMs = 0, remaining = 0;
    switch (inputUnit) {
    case DurationFormatter::Millisec:
        durationInMs = duration;
        break;
    case DurationFormatter::Sec:
        durationInMs = duration * 1000;
        break;
    case DurationFormatter::Minute:
        durationInMs = duration * 1000 * 60;
        break;
    case DurationFormatter::Hour:
        durationInMs = duration * 1000 * 60 * 60;
        break;
    case DurationFormatter::Day:
        durationInMs = duration * 1000 * 60 * 60 * 24;
        break;
    }

    remaining = durationInMs;

    if (durationInMs >= DAY_IN_MS) {
        int days = (durationInMs / DAY_IN_MS);
        ret = QObject::tr("%1 nap").arg(days);
        if (precision == Day)
            return ret;
        remaining -= days * DAY_IN_MS;
    } else {
        if (precision == Day)
            return ret;
    }

    if (remaining >= HOUR_IN_MS) {
        int hours = (remaining / HOUR_IN_MS);
        if (!ret.isEmpty())
            ret.append(QStringLiteral(" "));
        ret.append(QObject::tr("%1 óra").arg(hours));
        if (precision == Hour)
            return ret;
        remaining -= hours * HOUR_IN_MS;
    } else {
        if (precision == Hour)
            return ret;
    }

    if (remaining >= MINUTE_IN_MS) {
        int mins = (remaining / MINUTE_IN_MS);
        if (!ret.isEmpty())
            ret.append(QStringLiteral(" "));
        ret.append(QObject::tr("%1 perc").arg(mins));
        if (precision == Minute)
            return ret;
        remaining -= mins * MINUTE_IN_MS;
    } else {
        if (precision == Minute)
            return ret;
    }

    if (remaining > 1000) {
        int secs = (remaining / 1000);
        if (!ret.isEmpty())
            ret.append(QStringLiteral(" "));
        ret.append(QObject::tr("%1 mp").arg(secs));
        if (precision == Sec)
            return ret;
        remaining -= secs * 1000;
    } else {
        if (precision == Sec)
            return ret;
    }

    if (remaining) {
        if (!ret.isEmpty())
            ret.append(QStringLiteral(" "));
        ret.append(QObject::tr("%1 ms").arg(remaining));
    }

    if (ret.isEmpty()) {
        switch (precision) {
        case DurationFormatter::Millisec:
            return QObject::tr("0 ms");
        case DurationFormatter::Sec:
            return QObject::tr("0 mp");
        case DurationFormatter::Minute:
            return QObject::tr("0 perc");
        case DurationFormatter::Hour:
            return QObject::tr("0 óra");
        case DurationFormatter::Day:
            return QObject::tr("0 nap");

        }
    }
    return ret;
}

QString DurationFormatter::doubleDotDuration(qreal duration, DurationFormatter::TimeUnit firstUnit, TimeUnit lastUnit, DurationFormatter::TimeUnit inputUnit)
{
    QString ret;
    if (duration == 0) {
        int zeroCount = firstUnit - lastUnit + 1;
        for (int i = 0; i<zeroCount; i++) {
            ret.append(QStringLiteral("00"));
            if (i != zeroCount - 1)
                ret.append(QStringLiteral(":"));
        }
        return ret;
    }

    quint32 durationInMs, remaining;
    switch (inputUnit) {
    case DurationFormatter::Millisec:
        durationInMs = duration;
        break;
    case DurationFormatter::Sec:
        durationInMs = duration * 1000;
        break;
    case DurationFormatter::Minute:
        durationInMs = duration * 1000 * 60;
        break;
    case DurationFormatter::Hour:
        durationInMs = duration * 1000 * 60 * 60;
        break;
    case DurationFormatter::Day:
        durationInMs = duration * 1000 * 60 * 60 * 24;
        break;
    }

    remaining = durationInMs;

    if (firstUnit >= Day) {
        if (durationInMs >= DAY_IN_MS) {
            int days = (durationInMs / DAY_IN_MS);
            ret.append(QString::number(days).rightJustified(2, QChar('0')));
            remaining -= days * DAY_IN_MS;
        } else {
            ret = QStringLiteral("00");
        }
        if (lastUnit == Day)
            return ret;
    }

    if (firstUnit >= Hour) {
        if (remaining >= HOUR_IN_MS) {
            int hours = (remaining / HOUR_IN_MS);
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QString::number(hours).rightJustified(2, QChar('0')));
            remaining -= hours * HOUR_IN_MS;
        } else {
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QStringLiteral("00"));
        }
        if (lastUnit == Hour)
            return ret;
    }

    if (firstUnit >= Minute) {
        if (remaining >= MINUTE_IN_MS) {
            int mins = (remaining / MINUTE_IN_MS);
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QString::number(mins).rightJustified(2, QChar('0')));
            remaining -= mins * MINUTE_IN_MS;
        } else {
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QStringLiteral("00"));
        }
        if (lastUnit == Minute)
            return ret;
    }

    if (firstUnit >= Sec) {
        if (remaining > 1000) {
            int secs = (remaining / 1000);
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QString::number(secs).rightJustified(2, QChar('0')));
            if (lastUnit == Sec)
                return ret;
            remaining -= secs * 1000;
        } else {
            if (!ret.isEmpty())
                ret.append(QStringLiteral(":"));
            ret.append(QStringLiteral("00"));
        }
        if (lastUnit == Sec)
            return ret;
    }

    if (remaining) {
        if (!ret.isEmpty())
            ret.append(QStringLiteral(":"));
        ret.append(QString::number(remaining).rightJustified(3, QChar('0')));
    } else {
        if (!ret.isEmpty())
            ret.append(QStringLiteral(":"));
        ret.append(QStringLiteral("000"));
    }
    return ret;
}

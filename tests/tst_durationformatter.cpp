#include <QtTest>

#include "../durationformatter.h"

#include <QDebug>

class TestDurationFormatter : public QObject
{
    Q_OBJECT

public:

private slots:
    void testDurationFormatter()
    {
        qreal duration = 3600;
        auto durationStr = DurationFormatter::formatDuration(duration, DurationFormatter::Sec, DurationFormatter::Sec);
        QCOMPARE(durationStr, tr("1 óra"));
    }

    void testDoubleDotFormatter()
    {
        qreal duration = 3600;
        auto durationStr = DurationFormatter::doubleDotDuration(duration, DurationFormatter::Hour, DurationFormatter::Sec, DurationFormatter::Sec);
        QCOMPARE(durationStr, tr("01:00:00"));

        duration = 3599;
        durationStr = DurationFormatter::doubleDotDuration(duration, DurationFormatter::Hour, DurationFormatter::Sec, DurationFormatter::Sec);
        QCOMPARE(durationStr, tr("00:59:59"));

        duration = 3599000;
        durationStr = DurationFormatter::doubleDotDuration(duration, DurationFormatter::Hour, DurationFormatter::Sec, DurationFormatter::Millisec);
        QCOMPARE(durationStr, tr("00:59:59"));

        durationStr = DurationFormatter::doubleDotDuration(duration, DurationFormatter::Hour, DurationFormatter::Millisec, DurationFormatter::Millisec);
        QCOMPARE(durationStr, tr("00:59:59:000"));
    }
};


QTEST_APPLESS_MAIN(TestDurationFormatter)

#include "tst_durationformatter.moc"

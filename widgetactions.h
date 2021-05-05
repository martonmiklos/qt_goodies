#ifndef WIDGETACTIONS_H
#define WIDGETACTIONS_H

#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidgetAction>

class SpinBoxAction : public QWidgetAction
{
    Q_OBJECT
public:
    SpinBoxAction(QObject *parent = nullptr) : QWidgetAction(parent) {}
    SpinBoxAction(int value, int min = 0, int max = 99, const QString & suffix = QString(), QObject *parent = nullptr);

    QWidget* createWidget(QWidget *parent) override;
    void deleteWidget(QWidget *widget) override;

    int value();
    void setValue(int value);
    void setSuffix(const QString & suffix);

    int miniumum() const;
    void setMiniumum(int miniumum);

    int maximum() const;
    void setMaximum(int maximum);

    void setRange(int minimum, int maximum);
signals:
    void valueChanged(int value);
    void editingFinished();

private slots:
    void valueChangedSlot(int value);

private:
    QSpinBox *m_spinBox = nullptr;
    int m_value = 0;
    int m_minimum = 0, m_maximum = 99;
    QString m_suffix;
};

class LineEditAction : public QWidgetAction
{
    Q_OBJECT
public:
    LineEditAction(QObject *parent = nullptr) : QWidgetAction(parent) {}

    QWidget* createWidget(QWidget *parent) override;
    void deleteWidget(QWidget *widget) override;

    QString text() const;
    void setText(const QString & text);
private:
    QLineEdit *m_lineEdit = nullptr;
    QString m_text;
};

class PushButtonAction : public QWidgetAction
{
    Q_OBJECT
public:
    PushButtonAction(QObject *parent = nullptr) : QWidgetAction(parent) {}
    PushButtonAction(const QString& text, QObject *parent = nullptr) : QWidgetAction(parent), m_text(text) {}

    QWidget* createWidget(QWidget *parent) override;
    void deleteWidget(QWidget *widget) override;

private:
    QPushButton *m_button = nullptr;
    QString m_text;

signals:
    void clicked();
};

#endif // WIDGETACTIONS_H

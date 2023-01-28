#pragma once

#include <QWidget>

namespace Ui {
class TouchAidedSpinBox;
}

class TouchAidedSpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit TouchAidedSpinBox(QWidget *parent = nullptr);
    ~TouchAidedSpinBox();

    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER true)

    QString suffix() const;
    void setSuffix(const QString &newSuffix);

    int minimum() const;
    void setMinimum(int newMinimum);

    int maximum() const;
    void setMaximum(int newMaximum);

    int value() const;
    void setValue(int newValue);

private slots:
    void on_toolButtonIncrease_clicked();
    void on_toolButtonDecrease_clicked();

private:
    Ui::TouchAidedSpinBox *ui;
    int m_minimum = 0, m_maximum = 100, m_value = 0;

signals:
    void valueChanged(int value);
};


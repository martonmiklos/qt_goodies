#include "widgetactions.h"


SpinBoxAction::SpinBoxAction(int value, int min, int max, const QString &suffix, QObject *parent) :
    QWidgetAction(parent),
    m_value(value),
    m_minimum(min),
    m_maximum(max),
    m_suffix(suffix)
{

}

QWidget *SpinBoxAction::createWidget(QWidget *parent)
{
    m_spinBox = new QSpinBox(parent);
    m_spinBox->setMinimum(1);
    m_spinBox->setSuffix(m_suffix);
    m_spinBox->setMinimum(m_minimum);
    m_spinBox->setMaximum(m_maximum);
    m_spinBox->setValue(m_value);
    // oldschool connect for reason!
    connect(m_spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueChangedSlot(int)));
    connect(m_spinBox, SIGNAL(editingFinished()), this, SIGNAL(editingFinished()));
    return m_spinBox;
}

void SpinBoxAction::deleteWidget(QWidget *widget)
{
    Q_UNUSED(widget)
    if (m_spinBox != nullptr) {
        m_spinBox->deleteLater();
        m_spinBox = nullptr;
    }
}

int SpinBoxAction::value()
{
    if (m_spinBox != nullptr)
        return m_spinBox->value();
    return 0;
}

void SpinBoxAction::setValue(int value)
{
    m_value = value;
    if (m_spinBox != nullptr)
        m_spinBox->setValue(value);
}

void SpinBoxAction::setSuffix(const QString &suffix)
{
    m_suffix = suffix;
    if (m_spinBox)
        m_spinBox->setSuffix(suffix);
}

int SpinBoxAction::miniumum() const
{
    return m_minimum;
}

void SpinBoxAction::setMiniumum(int miniumum)
{
    m_minimum = miniumum;
    if (m_spinBox)
        m_spinBox->setMinimum(m_minimum);
}

int SpinBoxAction::maximum() const
{
    return m_maximum;
}

void SpinBoxAction::setMaximum(int maximum)
{
    m_maximum = maximum;
    if (m_spinBox)
        m_spinBox->setMaximum(m_maximum);
}

void SpinBoxAction::setRange(int minimum, int maximum)
{
    if (m_spinBox) {
        m_spinBox->setRange(minimum, maximum);
    } else {
        m_minimum = minimum;
        m_maximum = maximum;
    }
}

void SpinBoxAction::valueChangedSlot(int value)
{
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}



QWidget *LineEditAction::createWidget(QWidget *parent)
{
    m_lineEdit = new QLineEdit(m_text, parent);
    return m_lineEdit;
}

void LineEditAction::deleteWidget(QWidget *widget)
{
    Q_UNUSED(widget)
    if (m_lineEdit != nullptr) {
        m_lineEdit->deleteLater();
        m_lineEdit = nullptr;
    }
}

QString LineEditAction::text() const
{
    if (m_lineEdit != nullptr)
        return m_lineEdit->text();
    return QString();
}

void LineEditAction::setText(const QString &text)
{
    if (m_lineEdit != nullptr)
        m_lineEdit->setText(text);
    else
        m_text = text;
}

QWidget *PushButtonAction::createWidget(QWidget *parent)
{
    m_button = new QPushButton(m_text, parent);
    connect(m_button, &QPushButton::clicked, this, &PushButtonAction::clicked);
    return m_button;
}

void PushButtonAction::deleteWidget(QWidget *widget)
{
    Q_UNUSED(widget)
    if (m_button != nullptr) {
        m_button->deleteLater();
        m_button = nullptr;
    }
}

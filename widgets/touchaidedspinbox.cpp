#include "touchaidedspinbox.h"
#include "ui_touchaidedspinbox.h"

TouchAidedSpinBox::TouchAidedSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchAidedSpinBox)
{
    ui->setupUi(this);
    connect(ui->spinBoxValue, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

TouchAidedSpinBox::~TouchAidedSpinBox()
{
    delete ui;
}

void TouchAidedSpinBox::on_toolButtonIncrease_clicked()
{
    ui->spinBoxValue->setValue(ui->spinBoxValue->value() + 1);
}

void TouchAidedSpinBox::on_toolButtonDecrease_clicked()
{
    ui->spinBoxValue->setValue(ui->spinBoxValue->value() - 1);
}

int TouchAidedSpinBox::value() const
{
    return m_value;
}

void TouchAidedSpinBox::setValue(int newValue)
{
    if (ui->spinBoxValue->value() == newValue)
        return;
    ui->spinBoxValue->setValue(newValue);
}

int TouchAidedSpinBox::maximum() const
{
    return ui->spinBoxValue->maximum();
}

void TouchAidedSpinBox::setMaximum(int newMaximum)
{
    ui->spinBoxValue->setMaximum(newMaximum);
}

int TouchAidedSpinBox::minimum() const
{
    return ui->spinBoxValue->minimum();
}

void TouchAidedSpinBox::setMinimum(int newMinimum)
{
    ui->spinBoxValue->setMinimum(newMinimum);
}

QString TouchAidedSpinBox::suffix() const
{
    return ui->spinBoxValue->suffix();
}

void TouchAidedSpinBox::setSuffix(const QString &newSuffix)
{
    ui->spinBoxValue->setSuffix(suffix());
}


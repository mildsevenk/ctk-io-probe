#include "recvwidget.h"

#include "ui_RecvWidget.h"   // 由 AUTOUIC 自动生成
#include <QDebug>

RecvWidget::RecvWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RecvWidget)
{
    ui->setupUi(this);
    ui->rbASCII->setCheckable(true);
    ui->rbHEX->setCheckable(true);
    ui->cbAutoLine->setCheckable(true);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->rbASCII);
    m_buttonGroup->addButton(ui->rbHEX);
    connect(m_buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &RecvWidget::onButtonClicked);
    connect(ui->cbAutoLine, SIGNAL(toggled(bool)),
            this,          SLOT(onWrapCheckChanged(bool)));
    connect(this, &RecvWidget::activeModeStatusChanged,
            ui->rbASCII, &QCheckBox::setChecked,Qt::QueuedConnection);
    connect(this, &RecvWidget::activeWrapStatusChanged,
            ui->cbAutoLine, &QRadioButton::setChecked,Qt::QueuedConnection);
}

RecvWidget::~RecvWidget() = default;

QWidget* RecvWidget::getWidget()
{
    return this;
}

bool RecvWidget::setParent(QWidget* pParent)
{
    if(nullptr == pParent)
    {
        return false;
    }
    else
    {
        this->setParent(pParent);
        return true;
    }
}

void RecvWidget::onButtonClicked(QAbstractButton *button)
{

    if(button == ui->rbASCII)
    {
        if(ui->rbASCII->isChecked())
        {
            emit modeStatusChanged(true);
        }
        else
        {
            emit modeStatusChanged(false);
        }
    }
    else if(button == ui->rbHEX)
    {
        if(ui->rbHEX->isChecked())
        {
            emit modeStatusChanged(false);
        }
        else
        {
            emit modeStatusChanged(true);
        }
    }
}

void RecvWidget::onWrapCheckChanged(bool checked)
{
    emit wrapStatusChanged(checked);
}

void RecvWidget::setShowMode(bool bMode)
{
    emit activeModeStatusChanged(bMode);
}

void RecvWidget::setLineWrap(bool bWrap)
{
    emit activeWrapStatusChanged(bWrap);
}

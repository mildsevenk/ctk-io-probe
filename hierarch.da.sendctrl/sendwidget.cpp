#include "sendwidget.h"

#include "ui_SendWidget.h"   // 由 AUTOUIC 自动生成
#include <QButtonGroup>

SendWidget::SendWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SendWidget)
{
    ui->setupUi(this);
    ui->rbASCII->setCheckable(true);
    ui->rbHEX->setCheckable(true);
    this->m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->rbASCII);
    m_buttonGroup->addButton(ui->rbHEX);
    connect(m_buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &SendWidget::onButtonClicked);
    connect(this, &SendWidget::activeModeStatusChanged,
            ui->rbASCII, &QRadioButton::setChecked,
            Qt::QueuedConnection);
}

SendWidget::~SendWidget() = default;

QWidget* SendWidget::getWidget()
{
    return this;
}

bool SendWidget::setParent(QWidget* pParent)
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

void SendWidget::onButtonClicked(QAbstractButton *button)
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


void SendWidget::setShowMode(bool bMode)
{
    emit activeModeStatusChanged(bMode);
}


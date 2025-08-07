#include "sendwidget.h"

#include "ui_SendWidget.h"   // 由 AUTOUIC 自动生成

SendWidget::SendWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SendWidget)
{
    ui->setupUi(this);
    connect(ui->rbASCII, SIGNAL(toggled(bool)),
            this,          SLOT(onASCIICheckChanged(bool)));
    connect(ui->rbHEX, SIGNAL(toggled(bool)),
            this,          SLOT(onHEXCheckChanged(bool)));
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


void SendWidget::onASCIICheckChanged(bool checked)
{
    if(checked)
    {
        ui->rbHEX->setChecked(false);
        emit modeStatusChanged(true);
    }
    else
    {
        ui->rbHEX->setChecked(true);
        emit modeStatusChanged(false);
    }

}

void SendWidget::onHEXCheckChanged(bool checked)
{
    if(checked)
    {
        ui->rbASCII->setChecked(false);
        emit modeStatusChanged(false);
    }
    else
    {
        ui->rbASCII->setChecked(true);
        emit modeStatusChanged(true);
    }
}


void SendWidget::setShowMode(bool bMode)
{
    if(bMode)
    {
        ui->rbASCII->setChecked(true);
        ui->rbHEX->setChecked(false);
    }
    else
    {
        ui->rbASCII->setChecked(false);
        ui->rbHEX->setChecked(true);
    }
}


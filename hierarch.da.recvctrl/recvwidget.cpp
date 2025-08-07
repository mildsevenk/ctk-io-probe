#include "recvwidget.h"

#include "ui_RecvWidget.h"   // 由 AUTOUIC 自动生成

RecvWidget::RecvWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RecvWidget)
{
    ui->setupUi(this);
    connect(ui->rbASCII, SIGNAL(toggled(bool)),
            this,          SLOT(onASCIICheckChanged(bool)));
    connect(ui->rbHEX, SIGNAL(toggled(bool)),
            this,          SLOT(onHEXCheckChanged(bool)));
    connect(ui->cbAutoLine, SIGNAL(toggled(bool)),
            this,          SLOT(onWrapCheckChanged(bool)));
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


void RecvWidget::onASCIICheckChanged(bool checked)
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

void RecvWidget::onHEXCheckChanged(bool checked)
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

void RecvWidget::onWrapCheckChanged(bool checked)
{
    emit wrapStatusChanged(checked);
}

void RecvWidget::setShowMode(bool bMode)
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

void RecvWidget::setLineWrap(bool bWrap)
{
    ui->cbAutoLine->setChecked(bWrap);
}

#include "mainwindow.h"

#include "ui_MainWindow.h"   // 由 AUTOUIC 自动生成
#include <QDebug>

MainWindowe::MainWindowe(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbDeviceType->clear();
    if (ui->deviceSetStackedWidget->count() > 0)
    {
        QWidget* defaultPage = ui->deviceSetStackedWidget->widget(0);
        ui->deviceSetStackedWidget->removeWidget(defaultPage);
        delete defaultPage; // 确保删除页面以释放内存
    }
    ui->btnSend->setCheckable(true);
    QObject::connect(ui->btnSend, &QPushButton::toggled,
                     this, &MainWindowe::onBtnClicked);
}

MainWindowe::~MainWindowe() = default;


bool MainWindowe::setParent(QWidget* pParent)
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

QMainWindow* MainWindowe::getMainWindow()
{
    return this;
}

void MainWindowe::addDeviceType(QString strDeviceName, QWidget* pWidget)
{
    ui->cbDeviceType->addItem(strDeviceName);
    m_hs.insert(strDeviceName, pWidget);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->deviceSetStackedWidget->addWidget(pWidget);
}

void MainWindowe::initRecvSet(QWidget* pWidget)
{    
    QVBoxLayout* layout = new QVBoxLayout(ui->recvSetWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 去掉布局的边距
    layout->setSpacing(0);
    layout->addWidget(pWidget);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lstWidget.append(pWidget);
}

void MainWindowe::initSendSet(QWidget* pWidget)
{
    QVBoxLayout* layout = new QVBoxLayout(ui->sendSetWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 去掉布局的边距
    layout->setSpacing(0);
    layout->addWidget(pWidget);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lstWidget.append(pWidget);
}

void MainWindowe::initRecvViewSet(QWidget* pWidget)
{
    QVBoxLayout* layout = new QVBoxLayout(ui->recvViewWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 去掉布局的边距
    layout->setSpacing(0);
    layout->addWidget(pWidget);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lstWidget.append(pWidget);
}

void MainWindowe::initSendViewSet(QWidget* pWidget)
{
    QVBoxLayout* layout = new QVBoxLayout(ui->sendViewWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 去掉布局的边距
    layout->setSpacing(0);
    layout->addWidget(pWidget);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lstWidget.append(pWidget);
}

void MainWindowe::uninitWidget()
{
    for(QWidget* widget : m_lstWidget)
    {
        widget->setParent(nullptr);
    }
}

void MainWindowe::removeDeviceType()
{
    foreach (QWidget* widget, m_hs.values())
    {
        widget->setParent(nullptr);
    }
}

void MainWindowe::onBtnClicked()
{
    qDebug() << "MainWindowe::onBtnClicked()";
    emit sendButtonClicked();
}

void MainWindowe::closeEvent(QCloseEvent*)
{
    removeDeviceType();
    uninitWidget();
}




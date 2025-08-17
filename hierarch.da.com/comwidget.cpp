#include "comwidget.h"
#include <QSerialPortInfo>

#include "ui_ComWidget.h"   // 由 AUTOUIC 自动生成
#include <QDebug>

ComWidget::ComWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ComWidget)
{
    ui->setupUi(this);
    m_pSerialPort = new QSerialPort();
    resetComNo();
    initBaudBits();
    initParityBits();
    initDataBits();
    initStopBits();
    ui->btnOpenClose->setCheckable(true);
    QObject::connect(ui->btnOpenClose, &QPushButton::clicked,
                     this, &ComWidget::onButtonClicked);
    QObject::connect(this, &ComWidget::acvticeSendData,
                     this, &ComWidget::sendDataContent);

}

ComWidget::~ComWidget() = default;

const QString ComWidget::getDeviceName()
{
    return tr("COM");
}

//波特率
void ComWidget::initBaudBits()
{
    ui->cbBaudBits->clear();
    QStringList baudBits;
    //QSerialPort::Baud1200
    baudBits.append("1200");
    //QSerialPort::Baud2400
    baudBits.append("2400");
    //QSerialPort::Baud4800
    baudBits.append("4800");
    //QSerialPort::Baud9600
    baudBits.append("9600");
    //QSerialPort::Baud19200
    baudBits.append("19200");
    //QSerialPort::Baud38400
    baudBits.append("38400");
    //QSerialPort::Baud57600
    baudBits.append("57600");
    //QSerialPort::Baud115200
    baudBits.append("115200");
    ui->cbBaudBits->addItems(baudBits);
    ui->cbBaudBits->setCurrentIndex(3);
}
//数据位
void ComWidget::initDataBits()
{
    ui->cbDataBits->clear();
    QStringList DataBits;
    //QSerialPort::Data5
    DataBits.append("5");
    //QSerialPort::Data6
    DataBits.append("6");
    //QSerialPort::Data7
    DataBits.append("7");
    //QSerialPort::Data8
    DataBits.append("8");
    ui->cbDataBits->addItems(DataBits);
    ui->cbDataBits->setCurrentIndex(3);
}
//校验位
void ComWidget::initParityBits()
{
    ui->cbParityBits->clear();
    QStringList ParityBits;
    //QSerialPort::NoParity 无校验位
    ParityBits.append("NONE");
    //QSerialPort::EvenParity 数据位和校验位的总和为偶数
    ParityBits.append("EVEN");
    //QSerialPort::OddParity 数据位和校验位的总和为奇数
    ParityBits.append("ODD");
    //QSerialPort::SpaceParity 校验位始终为 0
    ParityBits.append("SPACE");
    //QSerialPort::MarkParity 校验位始终为 1
    ParityBits.append("MASK");
    ui->cbParityBits->addItems(ParityBits);
    ui->cbParityBits->setCurrentIndex(0);
}
//停止位
void ComWidget::initStopBits()
{
    ui->cbStopBits->clear();
    QStringList StopBits;
    //QSerialPort::OneStop
    StopBits.append("1");
    //QSerialPort::OneAndHalfStop
    StopBits.append("1.5");
    //QSerialPort::TwoStop
    StopBits.append("2");
    ui->cbStopBits->addItems(StopBits);
    ui->cbStopBits->setCurrentIndex(0);
}
//刷新串口
void ComWidget::resetComNo()
{
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    ui->cbComNo->clear();
    foreach (const QSerialPortInfo &portInfo, availablePorts) {
        ui->cbComNo->addItem(portInfo.portName());
    }
    if(ui->cbComNo->count() > 0)
    {
        ui->cbComNo->setCurrentIndex(0);
    }
}

QWidget* ComWidget::getWidget()
{
    return this;
}

bool ComWidget::setParent(QWidget* pParent)
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

const QSerialPort::BaudRate ComWidget::getCurBaudRate()
{
    QSerialPort::BaudRate baudRate = QSerialPort::Baud9600;
    switch(ui->cbBaudBits->currentIndex())
    {
    case 0:
        baudRate = QSerialPort::Baud1200;
        break;
    case 1:
        baudRate = QSerialPort::Baud2400;
        break;
    case 2:
        baudRate = QSerialPort::Baud4800;
        break;
    case 3:
        baudRate = QSerialPort::Baud9600;
        break;
    case 4:
        baudRate = QSerialPort::Baud19200;
        break;
    case 5:
        baudRate = QSerialPort::Baud38400;
        break;
    case 6:
        baudRate = QSerialPort::Baud57600;
        break;
    case 7:
        baudRate = QSerialPort::Baud115200;
        break;
    }
    return baudRate;
}

const QSerialPort::Parity ComWidget::getCurParity()
{
    QSerialPort::Parity parity = QSerialPort::NoParity;
    switch(ui->cbParityBits->currentIndex())
    {
    case 0:
        parity = QSerialPort::NoParity;
        break;
    case 1:
        parity = QSerialPort::EvenParity;
        break;
    case 2:
        parity = QSerialPort::OddParity;
        break;
    case 3:
        parity = QSerialPort::SpaceParity;
        break;
    case 4:
        parity = QSerialPort::MarkParity;
        break;
    }
    return parity;
}

const QSerialPort::DataBits ComWidget::getCurDataBits()
{
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    switch(ui->cbDataBits->currentIndex())
    {
    case 0:
        dataBits = QSerialPort::Data5;
        break;
    case 1:
        dataBits = QSerialPort::Data6;
        break;
    case 2:
        dataBits = QSerialPort::Data7;
        break;
    case 3:
        dataBits = QSerialPort::Data8;
        break;
    }
    return dataBits;
}

const QSerialPort::StopBits ComWidget::getCurStopBits()
{
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    switch(ui->cbDataBits->currentIndex())
    {
    case 0:
        stopBits = QSerialPort::OneStop;
        break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop;
        break;
    case 2:
        stopBits = QSerialPort::TwoStop;
    }
    return stopBits;
}

void ComWidget::onButtonClicked()
{
    qDebug() << "ComWidget::onButtonClicked start";
    if(!m_pSerialPort->isOpen())
    {
        if(ui->cbComNo->count() > 0)
        {
            qDebug() << "PortName:"<<ui->cbComNo->currentText();
            m_pSerialPort->setPortName(ui->cbComNo->currentText());
            // 设置波特率
            m_pSerialPort->setBaudRate(getCurBaudRate());
            // 设置数据位、校验位、停止位等参数
            m_pSerialPort->setDataBits(getCurDataBits());
            m_pSerialPort->setParity(getCurParity());
            m_pSerialPort->setStopBits(getCurStopBits());
            m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "open begin";
            if (m_pSerialPort->open(QIODevice::ReadWrite))
            {
                qDebug() << "open success";
                connect(m_pSerialPort, &QSerialPort::readyRead, this, &ComWidget::readData);
                ui->btnOpenClose->setText(u8"关闭串口");
            }
            else
            {
                qDebug() << "open failed";
                emit notifyMessage("打开端口失败");
            }
            qDebug() << "open end";
        }
        else
        {
            emit notifyMessage("打开端口失败");
        }
    }
    else
    {
        if (m_pSerialPort->isOpen()) {
            m_pSerialPort->close();
            ui->btnOpenClose->setText(u8"打开串口");
        }
    }
}

void ComWidget::readData()
{
    QByteArray data = m_pSerialPort->readAll();
    emit dataMessage(data);
}

void ComWidget::sendData(QByteArray data)
{
    emit acvticeSendData(data);
}

void ComWidget::sendDataContent(QByteArray data)
{
    if(m_pSerialPort->isOpen())
    {
        m_pSerialPort->write(data);
    }
}

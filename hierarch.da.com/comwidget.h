#ifndef COMWIDGET_H
#define COMWIDGET_H

#include "IDACIFD.h"
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class ComWidget; }
QT_END_NAMESPACE
class ComWidget : public QWidget, public hierarch::da::IDACIFD
{
    Q_OBJECT
    Q_INTERFACES(hierarch::da::IDACIFD)
public:
    explicit ComWidget(QWidget *parent = nullptr);
    ~ComWidget();
    virtual const QString getDeviceName();
    virtual QWidget* getWidget();
    virtual bool setParent(QWidget* pParent);
private:
    const QSerialPort::BaudRate getCurBaudRate();
    const QSerialPort::Parity getCurParity();
    const QSerialPort::DataBits getCurDataBits();
    const QSerialPort::StopBits getCurStopBits();
    void initBaudBits();
    //数据位
    void initDataBits();
    //校验位
    void initParityBits();
    //停止位
    void initStopBits();
    //刷新串口
    void resetComNo();
private:
    QSerialPort* m_pSerialPort  = nullptr;
private:
    Ui::ComWidget *ui;
signals:
    void notifyMessage(QString strInfo);
    void dataMessage(QByteArray data);
private slots:
    void onButtonClicked();
    void readData();
};

#endif // COMWIDGET_H

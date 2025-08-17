#ifndef QDAVIEWSHOW_H
#define QDAVIEWSHOW_H

#include <QPlainTextEdit>
#include "IDADataShowCtrl.h"

class QDAViewShow : public QPlainTextEdit, public IDADataShowCtrl
{
    Q_OBJECT
public:
    explicit QDAViewShow(QWidget* parent = nullptr);
    virtual bool addData(QByteArray) override;
    virtual bool clearData() override;
    virtual ~QDAViewShow() = default;
    void sendData();
signals:
    void addDataLine(const QString& text);
    void insertData(const QString& text);
    void sendDataContent(QByteArray data);
    void activeSendData();
public slots:
    void getData();
};

#endif // QDAVIEWSHOW_H

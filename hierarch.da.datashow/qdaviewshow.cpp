#include "qdaviewshow.h"
#include <QRegularExpression>

QDAViewShow::QDAViewShow(QWidget* parent)
    : QPlainTextEdit(parent) {
    this->document()->setMaximumBlockCount(100000);
    connect(this, &QDAViewShow::addDataLine, this, &QPlainTextEdit::appendPlainText, Qt::QueuedConnection);
    connect(this, &QDAViewShow::insertData, this, &QPlainTextEdit::insertPlainText, Qt::QueuedConnection);
    connect(this, &QDAViewShow::activeSendData, this, &QDAViewShow::getData, Qt::QueuedConnection);
}

bool QDAViewShow::addData(QByteArray str)
{
    QString text;
    if(this->getShowMode() == Mode::HEX)
    {
        for (int i = 0; i < str.size(); ++i) {
            text.append(QString("%1 ").arg(static_cast<quint8>(str.at(i)), 2, 16, QLatin1Char('0')).toUpper());
        }
    }
    else
    {
        for (char c : str) {
            uchar uc = static_cast<uchar>(c);
            text.append((uc >= 32 && uc < 127) ? QChar(uc) : QChar('.'));
        }
    }
    if(text.isNull())
    {
        return false;
    }
    //this->appendPlainText(text);
    if(this->getIsWrapLine())
    {
        emit addDataLine(text);
    }
    else
    {
        emit insertData(text);
    }
    return true;
}

bool QDAViewShow::clearData()
{
    this->clearData();
    return true;
}

void QDAViewShow::sendData()
{
    emit activeSendData();
}

void QDAViewShow::getData()
{
    QString strData = this->toPlainText();
    if(getShowMode() == IDADataShowCtrl::HEX)
    {
        strData.remove(QRegularExpression("\\s"));
        if (strData.size() % 2)        // 奇数个字符补 0
        {
            strData = "0" + strData;
        }
        QByteArray data = QByteArray::fromHex(strData.toUtf8());
        emit sendDataContent(data);
    }
    else
    {
        QByteArray data = this->toPlainText().toUtf8();
        emit sendDataContent(data);
    }
}

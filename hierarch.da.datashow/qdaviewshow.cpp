#include "qdaviewshow.h"

QDAViewShow::QDAViewShow(QWidget* parent)
    : QPlainTextEdit(parent) {
    this->document()->setMaximumBlockCount(100000);
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
    this->appendPlainText(text);
    return true;
}

bool QDAViewShow::clearData()
{
    this->clearData();
    return true;
}

QByteArray QDAViewShow::getData() const
{
    return this->toPlainText().toLatin1();
}

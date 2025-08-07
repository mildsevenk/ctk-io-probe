#ifndef QDAVIEWSHOW_H
#define QDAVIEWSHOW_H

#include <QPlainTextEdit>
#include "IDADataShowCtrl.h"

class QDAViewShow : public QPlainTextEdit, IDADataShowCtrl
{
public:
    explicit QDAViewShow(QWidget* parent = nullptr);
    virtual bool addData(QByteArray) override;
    virtual bool clearData() override;
    virtual QByteArray getData() const;
    virtual ~QDAViewShow() = default;
};

#endif // QDAVIEWSHOW_H



#ifndef __IDADataShow_h
#define __IDADataShow_h

#include <QByteArray>

class IDADataShowCtrl {
public:
    enum Mode { ASCII = 0, HEX };

    virtual bool addData(QByteArray)      = 0;
    virtual bool clearData()         = 0;
    virtual QByteArray getData() const = 0;

    // 非纯虚：提供默认实现
    virtual void setShowMode(Mode m) { m_eMode = m; }
    virtual Mode getShowMode() const { return m_eMode; }
    virtual void setIsRecv(bool v){ m_bIsRecv = v;}
    virtual bool getIsRecv() const {return m_bIsRecv;}

    virtual ~IDADataShowCtrl() = default;

protected:          // 或 private，但派生类需用 set/get 访问
    Mode m_eMode = ASCII;
    bool m_bIsRecv = true;
};

#endif

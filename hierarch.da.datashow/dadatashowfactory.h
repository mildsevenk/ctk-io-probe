#ifndef DADATASHOWFACTORY_H
#define DADATASHOWFACTORY_H
#include "IDADataShowFactory.h"
#include <ctkPluginContext.h>
#include "service/event/ctkEventHandler.h"

class QDAViewShow;
class ctkPluginContext;
class DADataShowFactory : public QObject, public hierarch::da::IDADataShowFactory
{
    Q_OBJECT
    Q_INTERFACES(hierarch::da::IDADataShowFactory)
public:
    explicit DADataShowFactory(ctkPluginContext* context);
    virtual ~DADataShowFactory();
    virtual QWidget* createView(bool bRecv) override;
    virtual void clearView() override;
private:
    QList<QDAViewShow*> m_lstSendWidget;
    QList<QDAViewShow*> m_lstRecvWidget;
    ctkPluginContext* m_pContext = nullptr;
};

class RecvDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit RecvDataHandler(QDAViewShow* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    QDAViewShow* m_pWidget;
};

class ViewRecvStateDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)
public:
    explicit ViewRecvStateDataHandler(QDAViewShow* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    QDAViewShow* m_pWidget = nullptr;
};

class ViewSendStateDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)
public:
    explicit ViewSendStateDataHandler(QDAViewShow* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    QDAViewShow* m_pWidget = nullptr;
};

class AutoLineDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)
public:
    explicit AutoLineDataHandler(QDAViewShow* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    QDAViewShow* m_pWidget = nullptr;
};

class SendDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit SendDataHandler(QDAViewShow* pWidget, ctkPluginContext* context);
    void handleEvent(const ctkEvent& event) override;

private:
    QDAViewShow* m_pWidget = nullptr;
    ctkPluginContext* m_pContext = nullptr;
};

#endif // DADATASHOWFACTORY_H

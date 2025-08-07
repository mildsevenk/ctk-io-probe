#ifndef QPLUGINACTIVATOR_H
#define QPLUGINACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"
#include "service/event/ctkEventHandler.h"
class RecvWidget;

class QPluginActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hierarch.da.recvctrl")
    Q_INTERFACES(ctkPluginActivator)
public:
    QPluginActivator();
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);
};

class RecvDataShowModeHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit RecvDataShowModeHandler(RecvWidget* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    RecvWidget* m_pWidget;
};

class RecvDataAutoWrapHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit RecvDataAutoWrapHandler(RecvWidget* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    RecvWidget* m_pWidget;
};


#endif // QPLUGINACTIVATOR_H

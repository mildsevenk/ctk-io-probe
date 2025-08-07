#ifndef QPLUGINACTIVATOR_H
#define QPLUGINACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"
#include "service/event/ctkEventHandler.h"
class SendWidget;

class QPluginActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hierarch.da.sendctrl")
    Q_INTERFACES(ctkPluginActivator)
public:
    QPluginActivator();
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);
};

class SendDataShowModeHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit SendDataShowModeHandler(SendWidget* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    SendWidget* m_pWidget;
};

#endif // QPLUGINACTIVATOR_H

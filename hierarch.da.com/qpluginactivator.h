#ifndef QPLUGINACTIVATOR_H
#define QPLUGINACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"
#include "service/event/ctkEventHandler.h"
class ComWidget;

class QPluginActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hierarch.da.com")
    Q_INTERFACES(ctkPluginActivator)
public:
    QPluginActivator();
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);
};

class SendDataHandler : public QObject, public ctkEventHandler
{
    Q_OBJECT
    Q_INTERFACES(ctkEventHandler)

public:
    explicit SendDataHandler(ComWidget* pWidget);
    void handleEvent(const ctkEvent& event) override;

private:
    ComWidget* m_pWidget;
};

#endif // QPLUGINACTIVATOR_H

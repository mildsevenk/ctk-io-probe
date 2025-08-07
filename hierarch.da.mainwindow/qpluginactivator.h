#ifndef QPLUGINACTIVATOR_H
#define QPLUGINACTIVATOR_H

#include <QObject>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"
class MainWindowe;
class QPluginActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hierarch.da.com")
    Q_INTERFACES(ctkPluginActivator)
public:
    QPluginActivator();
    void start(ctkPluginContext* context);
    void stop(ctkPluginContext* context);
private:
    QList<ctkServiceReference> m_lstRef;
    ctkServiceReference m_factory;
    MainWindowe* m_mainWindow = nullptr;
};

#endif // QPLUGINACTIVATOR_H

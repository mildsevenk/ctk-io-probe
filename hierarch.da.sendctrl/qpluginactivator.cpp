#include "qpluginactivator.h"
#include "service/event/ctkEventHandler.h"
#include "service/event/ctkEventAdmin.h"
#include <ctkDictionary.h>
#include <QDebug>
#include <QCoreApplication>
#include "sendwidget.h"
#include "DAEventNames.h"

SendDataShowModeHandler::SendDataShowModeHandler(SendWidget* pWidget)
    : m_pWidget(pWidget)
{
}

void SendDataShowModeHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_SEND_DATA_SHOW_MODE)
        return;

    bool bMode = event.getProperty(DAEventNames::DA_SEND_DATA_SHOW_MODE_VALUE).toBool();
    if (m_pWidget != nullptr)
    {
        m_pWidget->setShowMode(bMode);
    }
}

QPluginActivator::QPluginActivator() {}


void QPluginActivator::start(ctkPluginContext *context)
{
    SendWidget* impl = new SendWidget();
    context->registerService<hierarch::da::IDAWidget>(impl);
    ctkDictionary props_mode;
    props_mode["event.topics"] = DAEventNames::DA_SEND_DATA_SHOW_MODE ;
    context->registerService<ctkEventHandler>(new SendDataShowModeHandler(impl), props_mode);
    //绑定信号
    connect(impl, &SendWidget::modeStatusChanged, this,
            [=](bool bMode){
                ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
                if (!ref) {
                    qWarning() << "EventAdmin not available";
                    return;
                }
                ctkEventAdmin* ea = context->getService<ctkEventAdmin>(ref);

                // 构造数据
                ctkDictionary props;
                props[DAEventNames::DA_BOOLEAN] = bMode;

                // 异步发送（立即返回）
                ea->postEvent(ctkEvent(DAEventNames::DA_SEND_DATA_MODE_CHANGED, props));
    });
}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("I'm appinfo plugin, now stop.");
}


#include "qpluginactivator.h"
#include "service/event/ctkEventHandler.h"
#include "service/event/ctkEventAdmin.h"
#include <ctkDictionary.h>
#include <QDebug>
#include <QCoreApplication>
#include "recvwidget.h"
#include "DAEventNames.h"

RecvDataShowModeHandler::RecvDataShowModeHandler(RecvWidget* pWidget)
    : m_pWidget(pWidget)
{
}

void RecvDataShowModeHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA_SHOW_MODE)
        return;

    bool bMode = event.getProperty(DAEventNames::DA_RECV_DATA_SHOW_MODE_VALUE).toBool();
    if (m_pWidget != nullptr)
    {
        m_pWidget->setShowMode(bMode);
    }
}

RecvDataAutoWrapHandler::RecvDataAutoWrapHandler(RecvWidget* pWidget)
    : m_pWidget(pWidget)
{
}

void RecvDataAutoWrapHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA_AUTO_WRAP)
        return;

    bool bMode = event.getProperty(DAEventNames::DA_RECV_DATA_AUTO_WRAP_VALUE).toBool();
    if (m_pWidget != nullptr)
    {
        m_pWidget->setLineWrap(bMode);
    }
}

QPluginActivator::QPluginActivator() {}


void QPluginActivator::start(ctkPluginContext *context)
{
    RecvWidget* impl = new RecvWidget();   //
    context->registerService<hierarch::da::IDAWidget>(impl);
    ctkDictionary props_mode;
    props_mode["event.topics"] = DAEventNames::DA_RECV_DATA_SHOW_MODE ;
    context->registerService<ctkEventHandler>(new RecvDataShowModeHandler(impl), props_mode);
    ctkDictionary props_auto_wrap;
    props_auto_wrap["event.topics"] = DAEventNames::DA_RECV_DATA_AUTO_WRAP ;
    context->registerService<ctkEventHandler>(new RecvDataAutoWrapHandler(impl), props_auto_wrap);
    //绑定信号
    connect(impl, &RecvWidget::modeStatusChanged, this,
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
                ea->postEvent(ctkEvent(DAEventNames::DA_RECV_DATA_MODE_CHANGED, props));
    });

    connect(impl, &RecvWidget::wrapStatusChanged, this,
            [=](bool bWrap){
                ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
                if (!ref) {
                    qWarning() << "EventAdmin not available";
                    return;
                }
                ctkEventAdmin* ea = context->getService<ctkEventAdmin>(ref);

                // 构造数据
                ctkDictionary props;
                props[DAEventNames::DA_BOOLEAN] = bWrap;
                qDebug() << "DAEventNames::DA_RECV_DATA_WRAP_CHANGED";
                // 异步发送（立即返回）
                ea->postEvent(ctkEvent(DAEventNames::DA_RECV_DATA_WRAP_CHANGED, props));
            });
}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("I'm appinfo plugin, now stop.");
}



#include "qpluginactivator.h"
#include <ctkDictionary.h>
#include <QDebug>
#include <QCoreApplication>
#include "IDACIFD.h"
#include "comwidget.h"
#include "DAEventNames.h"
#include "service/event/ctkEventAdmin.h"

QPluginActivator::QPluginActivator() {}


void QPluginActivator::start(ctkPluginContext *context)
{
    ComWidget* impl = new ComWidget();   //
    context->registerService<hierarch::da::IDACIFD>(impl);
    ctkDictionary props;
    props["event.topics"] = DAEventNames::DA_SEND_DATA ;
    context->registerService<ctkEventHandler>(new SendDataHandler(impl), props);
    connect(impl, &ComWidget::notifyMessage, this,
            [=](QString strInfo){
                // 构造数据
                ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
                if (!ref) {
                    qWarning() << "EventAdmin not available";
                    return;
                }
                ctkEventAdmin* ea = context->getService<ctkEventAdmin>(ref);
                ctkDictionary props;
                props[DAEventNames::DA_DIALOG_SHOW_TITLE] = tr("提示");
                props[DAEventNames::DA_DIALOG_SHOW_INFO] = strInfo;
                // 异步发送（立即返回）
                ea->postEvent(ctkEvent(DAEventNames::DA_DIALOG_SHOW, props));
    });

    connect(impl, &ComWidget::dataMessage, this,
            [=](QByteArray data){
                // 构造数据
                ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
                if (!ref) {
                    qWarning() << "EventAdmin not available";
                    return;
                }
                ctkEventAdmin* ea = context->getService<ctkEventAdmin>(ref);
                ctkDictionary props;
                props[DAEventNames::DA_RECV_DATA_VALUE] = data;
                // 异步发送（立即返回）
                ea->postEvent(ctkEvent(DAEventNames::DA_RECV_DATA, props));
            });

}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("I'm appinfo plugin, now stop.");
}

SendDataHandler::SendDataHandler(ComWidget* pWidget)
    : m_pWidget(pWidget)
{
}

void SendDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_SEND_DATA)
        return;

    QByteArray data = event.getProperty(DAEventNames::DA_SEND_DATA_VALUE).toByteArray();
    if (m_pWidget != nullptr && data.count() > 0)
    {
        m_pWidget->sendData(data);
    }
}



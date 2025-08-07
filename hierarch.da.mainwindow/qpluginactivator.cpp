#include "qpluginactivator.h"
#include <ctkDictionary.h>
#include <QDebug>
#include <QCoreApplication>
#include "IDACIFD.h"
#include "IDAWidget.h"
#include "IDADataShowFactory.h"
#include "mainwindow.h"
#include "DAEventNames.h"
#include "service/event/ctkEventAdmin.h"

QPluginActivator::QPluginActivator() {}


void QPluginActivator::start(ctkPluginContext *context)
{
    MainWindowe* impl = new MainWindowe();
    m_mainWindow = impl;
    context->registerService<hierarch::da::IDAMainWindow>(impl);
    //初始化
    QList<ctkServiceReference> references = context->getServiceReferences<hierarch::da::IDACIFD>();

    if (!references.isEmpty()) {
        qDebug() << "Found" << references.size() << "services implementing IDACIFD:";

        foreach (const ctkServiceReference& reference, references)
        {
            // 获取指定 ctkServiceReference 引用的服务对象
            hierarch::da::IDACIFD* service = qobject_cast<hierarch::da::IDACIFD*>(context->getService(reference));
            if (service != Q_NULLPTR)
            {
                // 调用服务的接口函数
                QWidget* pWidget = service->getWidget();
                impl->addDeviceType(service->getDeviceName(), pWidget);
            } else {
                qDebug() << "Failed to cast the service to IDACIFD.";
            }
        }
    }

    QList<ctkServiceReference> refWidgets = context->getServiceReferences<hierarch::da::IDAWidget>();
    if (!refWidgets.isEmpty())
    {
        foreach (ctkServiceReference widget, refWidgets)
        {
            hierarch::da::IDAWidget* service = qobject_cast<hierarch::da::IDAWidget*>(context->getService(widget));
            QString strName = service->getWidgetName();
            QWidget* pWidget = service->getWidget();
            if(pWidget != nullptr)
            {
                if(strName == tr("hierarch.da.sendctrl"))
                {
                    impl->initSendSet(pWidget);
                    m_lstRef.append(widget);
                }
                else if(strName == tr("hierarch.da.datashow"))
                {
                    impl->initRecvViewSet(pWidget);
                    m_lstRef.append(widget);
                }
                else if(strName == tr("hierarch.da.recvctrl"))
                {
                    impl->initRecvSet(pWidget);
                    m_lstRef.append(widget);
                }
                else
                {
                    context->ungetService(widget);
                }
            }
            else
            {
                context->ungetService(widget);
            }

        }
    }
    ctkServiceReference refView = context->getServiceReference<hierarch::da::IDADataShowFactory>();
    {
        hierarch::da::IDADataShowFactory* service = qobject_cast<hierarch::da::IDADataShowFactory*>(context->getService(refView));
        if(service != nullptr)
        {
            QWidget* pRecv = service->createView(true);
            QWidget* pSend = service->createView(false);
            impl->initRecvViewSet(pRecv);
            impl->initSendViewSet(pSend);
            m_factory = refView;
        }
    }

    connect(impl, &MainWindowe::sendButtonClicked, this,
            [=](){
                ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
                if (!ref) {
                    qWarning() << "EventAdmin not available";
                    return;
                }
                ctkEventAdmin* ea = context->getService<ctkEventAdmin>(ref);

                // 构造数据
                ctkDictionary props;
                ea->postEvent(ctkEvent(DAEventNames::DA_SEND_DATA_COMMAND, props));
            });
}

void QPluginActivator::stop(ctkPluginContext *context)
{
    if(m_mainWindow)
    {
        m_mainWindow->uninitRecvViewSet();
        m_mainWindow->uninitSendViewSet();
    }
    context->ungetService(m_factory);
    if(m_mainWindow)
    {
        m_mainWindow->uninitRecvSet();
        m_mainWindow->uninitSendSet();
        m_mainWindow->removeDeviceType();
    }
    foreach (const ctkServiceReference& ref, m_lstRef)
    {
        context->ungetService(ref);
    }
    m_lstRef.clear();

    qDebug() << QString("I'm appinfo plugin, now stop.");
}



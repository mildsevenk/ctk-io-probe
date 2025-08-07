#include "dadatashowfactory.h"
#include "qdaviewshow.h"
#include "DAEventNames.h"
#include "ctkPluginContext.h"
#include "service/event/ctkEventAdmin.h"

RecvDataHandler::RecvDataHandler(QDAViewShow* pWidget)
    : m_pWidget(pWidget)
{
}

void RecvDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA)
        return;

    QByteArray data = event.getProperty(DAEventNames::DA_RECV_DATA_VALUE).toByteArray();
    if (m_pWidget != nullptr && data.count() > 0)
    {
        m_pWidget->addData(data);
    }
}

SendDataHandler::SendDataHandler(QDAViewShow* pWidget, ctkPluginContext* context)
    : m_pWidget(pWidget), m_pContext(context)
{
}

void SendDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA)
        return;
    if (m_pWidget != nullptr)
    {
        QByteArray data =  m_pWidget->getData();
        if(data.count() > 0 && m_pContext)
        {
            ctkServiceReference ref = m_pContext->getServiceReference<ctkEventAdmin>();
            if (!ref) {
                qWarning() << "EventAdmin not available";
                return;
            }
            ctkEventAdmin* ea = m_pContext->getService<ctkEventAdmin>(ref);
            ctkDictionary props;
            props[DAEventNames::DA_SEND_DATA_VALUE] = data;
            ea->postEvent(ctkEvent(DAEventNames::DA_SEND_DATA, props));
        }
    }
}


DADataShowFactory::DADataShowFactory(ctkPluginContext* context) :m_pContext(context) {
}

QWidget* DADataShowFactory::createView(bool bRecv)
{
    if(m_pContext)
    {
        QDAViewShow* view = new QDAViewShow();
        if(bRecv)
        {
            view->setReadOnly(true);
            m_lstRecvWidget.append(view);
            ctkDictionary props;
            props["event.topics"] = DAEventNames::DA_RECV_DATA ;
            m_pContext->registerService<ctkEventHandler>(new RecvDataHandler(view), props);

        }
        else
        {
            m_lstSendWidget.append(view);
            ctkDictionary props;
            props["event.topics"] = DAEventNames::DA_SEND_DATA_COMMAND ;
            m_pContext->registerService<ctkEventHandler>(new SendDataHandler(view, m_pContext), props);

        }
        return view;
    }
    else
    {
        return nullptr;
    }
}

void DADataShowFactory::clearView()
{
    foreach (QWidget* widget, m_lstRecvWidget)
    {
        delete widget;
    }

    foreach (QWidget* widget, m_lstSendWidget)
    {
        delete widget;
    }
}

DADataShowFactory::~DADataShowFactory()
{
    clearView();
}

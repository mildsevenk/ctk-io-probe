#include "dadatashowfactory.h"
#include "qdaviewshow.h"
#include "DAEventNames.h"
#include "ctkPluginContext.h"
#include "service/event/ctkEventAdmin.h"
#include <QDebug>

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
    if (event.getTopic() != DAEventNames::DA_SEND_DATA_COMMAND)
        return;
    if (m_pWidget != nullptr)
    {
        qDebug() << "SendDataHandler::handleEvent";
        m_pWidget->getData();
    }
}

ViewRecvStateDataHandler::ViewRecvStateDataHandler(QDAViewShow* pWidget)
    : m_pWidget(pWidget)
{
}

void ViewRecvStateDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA_MODE_CHANGED)
        return;

    bool data = event.getProperty(DAEventNames::DA_BOOLEAN).toBool();
    if (m_pWidget != nullptr)
    {
        IDADataShowCtrl::Mode mode = IDADataShowCtrl::ASCII;
        if(!data)
        {
            qDebug() << "recv IDADataShowCtrl::HEX";
            mode = IDADataShowCtrl::HEX;
        }
        else
        {
            qDebug() << "recv IDADataShowCtrl::ASCII";
        }
        m_pWidget->setShowMode(mode);
    }
}

ViewSendStateDataHandler::ViewSendStateDataHandler(QDAViewShow* pWidget)
    : m_pWidget(pWidget)
{
}

void ViewSendStateDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_SEND_DATA_MODE_CHANGED)
        return;

    bool data = event.getProperty(DAEventNames::DA_BOOLEAN).toBool();
    if (m_pWidget != nullptr)
    {
        IDADataShowCtrl::Mode mode = IDADataShowCtrl::ASCII;
        if(!data)
        {
            qDebug() << "recv IDADataShowCtrl::HEX";
            mode = IDADataShowCtrl::HEX;
        }
        else
        {
            qDebug() << "recv IDADataShowCtrl::ASCII";
        }
        m_pWidget->setShowMode(mode);
    }
}

AutoLineDataHandler::AutoLineDataHandler(QDAViewShow* pWidget)
    : m_pWidget(pWidget)
{
}

void AutoLineDataHandler::handleEvent(const ctkEvent& event)
{
    if (event.getTopic() != DAEventNames::DA_RECV_DATA_WRAP_CHANGED)
        return;

    bool data = event.getProperty(DAEventNames::DA_BOOLEAN).toBool();
    if (m_pWidget != nullptr)
    {
        m_pWidget->setIsWrapLine(data);
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
            ctkDictionary propMode;
            propMode["event.topics"] = DAEventNames::DA_RECV_DATA_MODE_CHANGED ;
            m_pContext->registerService<ctkEventHandler>(new ViewRecvStateDataHandler(view), propMode);
            ctkDictionary propWrap;
            propWrap["event.topics"] = DAEventNames::DA_RECV_DATA_WRAP_CHANGED ;
            m_pContext->registerService<ctkEventHandler>(new AutoLineDataHandler(view), propWrap);
        }
        else
        {
            m_lstSendWidget.append(view);
            ctkDictionary props;
            props["event.topics"] = DAEventNames::DA_SEND_DATA_COMMAND ;
            m_pContext->registerService<ctkEventHandler>(new SendDataHandler(view, m_pContext), props);
            ctkDictionary propMode;
            propMode["event.topics"] = DAEventNames::DA_SEND_DATA_MODE_CHANGED;
            m_pContext->registerService<ctkEventHandler>(new ViewSendStateDataHandler(view), propMode);
            connect(view, &QDAViewShow::sendDataContent, this,
                    [=](QByteArray data){
                        ctkServiceReference ref = m_pContext->getServiceReference<ctkEventAdmin>();
                        if (!ref) {
                            qWarning() << "EventAdmin not available";
                            return;
                        }
                        ctkEventAdmin* ea = m_pContext->getService<ctkEventAdmin>(ref);

                        // 构造数据
                        ctkDictionary props;
                        props[DAEventNames::DA_SEND_DATA_VALUE] = data;
                        ea->postEvent(ctkEvent(DAEventNames::DA_SEND_DATA, props));
                        qDebug() << "(DAEventNames::DA_SEND_DATA";
                        //测试数据发送
                    });

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

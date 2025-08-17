#include <QTest>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginContext.h>
#include <QDir>
#include <IDAWidget.h>
#include <IDACIFD.h>
#include <IDADataShowFactory.h>
#include <QThread>
#include <QTimer>
#include <ctkPluginFrameworkLauncher.h>

class AllPluginsTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void test_sendctrl();
    void test_recvctrl();
    void test_com();
    void test_datashow();
    void cleanupTestCase();
private:
    ctkPluginContext* ctx = nullptr;
    QWidget* m_sendWidget = nullptr;
    QWidget* m_recvWidget = nullptr;
    QWidget* m_comWidget = nullptr;
    QWidget* m_showdataWidget = nullptr;

};

void AllPluginsTest::initTestCase()
{
    qputenv("CTK_DEBUG", "1");          // 打开 CTK 调试
    qputenv("QT_LOGGING_RULES", "*.debug=true");
    ctkPluginFrameworkLauncher::addSearchPath(QCoreApplication::applicationDirPath() + "/plugins");
    ctkPluginFrameworkLauncher::start();
    ctx = ctkPluginFrameworkLauncher::getPluginContext();
    const QStringList pluginNames = {
        "hierarch_da_sendctrl",
        "hierarch_da_recvctrl",
        "hierarch_da_com",
        "hierarch_da_datashow"};
    QDir pluginDir(QCoreApplication::applicationDirPath() + "/plugins");
    for (const QString& name : pluginNames)
    {
        QString path = pluginDir.absoluteFilePath(name + ".dll");       // win
        auto plugin = ctx->installPlugin(QUrl::fromLocalFile(path));
        try
        {
            plugin->start(ctkPlugin::START_TRANSIENT);
        }
        catch(ctkException ex)
        {
            qDebug() << "Failed "<<ex.what();
        }
    }
}

void AllPluginsTest::test_sendctrl()
{
    try {
        //auto refs = ctx->getServiceReferences<hierarch::da::IDAWidget>();
        QList<ctkServiceReference> refs =
            ctx->getServiceReferences("hierarch.da.IDAWidget");
        for(const ctkServiceReference& ref : refs)
        {
            if (ref)
            {
                hierarch::da::IDAWidget* service = qobject_cast<hierarch::da::IDAWidget*>(ctx->getService(ref));
                if(service)
                {
                    QWidget* widget = service->getWidget();
                    if(widget)
                    {
                        if(service->getWidgetName() == QObject::tr("hierarch.da.sendctrl"))
                        {
                            m_sendWidget = widget;
                            widget->show();
                        }

                    }
                }
            }
        }

    } catch (const ctkRuntimeException& e) {
        QFAIL(qPrintable(QString("CTK: ") + e.what()));
    } catch (const std::exception& e) {
        QFAIL(qPrintable(QString("STD: ") + e.what()));
    }
}

void AllPluginsTest::test_recvctrl()
{
    try {
        //auto refs = ctx->getServiceReferences<hierarch::da::IDAWidget>();
        QList<ctkServiceReference> refs =
            ctx->getServiceReferences("hierarch.da.IDAWidget");
        for(const ctkServiceReference& ref : refs)
        {
            if (ref)
            {
                hierarch::da::IDAWidget* service = qobject_cast<hierarch::da::IDAWidget*>(ctx->getService(ref));
                if(service)
                {
                    QWidget* widget = service->getWidget();
                    if(widget)
                    {
                        if(service->getWidgetName() == QObject::tr("hierarch.da.recvctrl"))
                        {
                            m_recvWidget = widget;
                            widget->show();
                        }

                    }
                }
            }
        }

    } catch (const ctkRuntimeException& e) {
        QFAIL(qPrintable(QString("CTK: ") + e.what()));
    } catch (const std::exception& e) {
        QFAIL(qPrintable(QString("STD: ") + e.what()));
    }
}

void AllPluginsTest::test_com()
{
    try {
        QList<ctkServiceReference> refs =
            ctx->getServiceReferences("hierarch.da.IDACIFD");
        for(const ctkServiceReference& ref : refs)
        {
            if (ref)
            {
                hierarch::da::IDACIFD* service = qobject_cast<hierarch::da::IDACIFD*>(ctx->getService(ref));
                if(service)
                {
                    QWidget* widget = service->getWidget();
                    if(widget)
                    {
                        if(service->getDeviceName() == QObject::tr("COM"))
                        {
                            m_comWidget = widget;
                            widget->show();
                        }

                    }
                }
            }
        }

    } catch (const ctkRuntimeException& e) {
        QFAIL(qPrintable(QString("CTK: ") + e.what()));
    } catch (const std::exception& e) {
        QFAIL(qPrintable(QString("STD: ") + e.what()));
    }
}

void AllPluginsTest::test_datashow()
{
    try {
        QList<ctkServiceReference> refs =
            ctx->getServiceReferences("hierarch.da.IDADataShowFactory");
        for(const ctkServiceReference& ref : refs)
        {
            if (ref)
            {
                hierarch::da::IDADataShowFactory* service = qobject_cast<hierarch::da::IDADataShowFactory*>(ctx->getService(ref));
                if(service)
                {
                    QWidget* widget = service->createView(true);
                    //QWidget* widget = service->getWidget();
                    if(widget)
                    {
                        m_showdataWidget = widget;
                        widget->show();
                    }
                }
            }
        }

    } catch (const ctkRuntimeException& e) {
        QFAIL(qPrintable(QString("CTK: ") + e.what()));
    } catch (const std::exception& e) {
        QFAIL(qPrintable(QString("STD: ") + e.what()));
    }
}

void AllPluginsTest::cleanupTestCase()
{
    if(m_sendWidget)
    {
        m_sendWidget->close();
    }
    if(m_recvWidget)
    {
        m_recvWidget->close();
    }
    if(m_comWidget)
    {
        m_comWidget->close();
    }
    if(m_showdataWidget)
    {
        m_showdataWidget->close();
    }
    //QCoreApplication::processEvents();
    const QStringList pluginSymbolicNames = {
        "hierarch.da.sendctrl",
        "hierarch.da.recvctrl",
        "hierarch.da.com",
        "hierarch.da.datashow"
    };
    try {
        QList<QSharedPointer<ctkPlugin>> plugins = ctx->getPlugins();
        for(QSharedPointer<ctkPlugin> plugin : plugins)
        {
            QString sn = plugin->getSymbolicName();
            if (pluginSymbolicNames.contains(sn)) {
                plugin->stop();
                plugin->uninstall();
            }
        }
    } catch (const ctkRuntimeException& e) {
        QFAIL(qPrintable(QString("CTK: ") + e.what()));
    } catch (const std::exception& e) {
        QFAIL(qPrintable(QString("STD: ") + e.what()));
    }
    //fw->stop();
    //fw.clear();
}

QTEST_MAIN(AllPluginsTest)
#include "tst_allplugins.moc"

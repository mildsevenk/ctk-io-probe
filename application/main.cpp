
#include <QApplication>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include <QtDebug>
#include <QDirIterator>
#include <QUrl>
#include "IDAMainWindow.h"
#include <QString>

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    ctkPluginFrameworkFactory frameworkFactory;
    QSharedPointer<ctkPluginFramework> framework = frameworkFactory.getFramework();
    qDebug() << "App dir:" << QCoreApplication::applicationDirPath();
    // 初始化并启动插件框架
    try {
        framework->init();
        framework->start();
        qDebug() << "CTK plugin framework start...";
    } catch (const ctkPluginException &e) {
        qDebug() << "CTK plugin framework init err: " << e.what();
        return -1;
    }

    // 获取插件服务的contex
    QString programPath = QApplication::applicationDirPath();
    QString pluginPath = programPath + QObject::tr("/plugins");
    //QDir dir(pluginPath);
    QStringList pluginFiles;
    QDirIterator it(pluginPath, QStringList() << "*.dll" << "*.so", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString filePath = it.next();
        pluginFiles.append(filePath);
    }
    if(pluginFiles.count() > 0)
    {
        ctkPluginContext* pluginContext = framework->getPluginContext();
        QString strMainPluginName = QObject::tr("hierarch.da.mainwindow");
        QSharedPointer<ctkPlugin> mainPlugin = nullptr;
        foreach (const QString &pluginFile, pluginFiles)
        {
            try
            {
                QSharedPointer<ctkPlugin> plugin = pluginContext->installPlugin(QUrl::fromLocalFile(pluginFile));
                if(strMainPluginName == plugin->getSymbolicName())
                {
                    mainPlugin = plugin;
                }
                else
                {
                    plugin->start(ctkPlugin::START_TRANSIENT);
                    qDebug() << "Plugin started success:" << plugin->getSymbolicName();
                }
                qDebug() << "Plugin loaded and started:" << pluginFile;
            }
            catch (const ctkPluginException &e)
            {
                qDebug() << "Failed to load plugin:" << pluginFile << "Error:" << e.what();
            }
        }
        if(mainPlugin)
        {
            try
            {
                for (auto p : framework->getPluginContext()->getPlugins())
                    qDebug() << p->getSymbolicName() << p->getVersion() << p->getLocation() << p->getState();
                mainPlugin->start(ctkPlugin::START_TRANSIENT);
                ctkServiceReference ref = pluginContext->getServiceReference<hierarch::da::IDAMainWindow>();
                hierarch::da::IDAMainWindow* service =
                    qobject_cast<hierarch::da::IDAMainWindow*>(pluginContext->getService(ref));
                if(service)
                {
                    QMainWindow* pMain = service->getMainWindow();
                    pMain->show();
                }
            }
            catch (const ctkPluginException &e)
            {
                qDebug() << "Error:" << e.what();
            }
        }
    }

    return a.exec();
}

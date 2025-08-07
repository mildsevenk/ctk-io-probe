#include "qpluginactivator.h"
#include <QDebug>
#include <QCoreApplication>
#include "dadatashowfactory.h"
#include "qdaviewshow.h"
#include <ctkDictionary.h>
#include "DAEventNames.h"

QPluginActivator::QPluginActivator() {}

void QPluginActivator::start(ctkPluginContext *context)
{
    DADataShowFactory* impl = new DADataShowFactory(context);
    context->registerService<hierarch::da::IDADataShowFactory>(impl);
    qDebug() << QString("hierach.da.datshow plugin start");
}

void QPluginActivator::stop(ctkPluginContext *)
{
    qDebug() << QString("hierach.da.datshow plugin stop");
}

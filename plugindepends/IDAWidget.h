#ifndef __HIERARCH_DA_IDAWIDGET_H
#define __HIERARCH_DA_IDAWIDGET_H

#include <QWidget>

namespace hierarch{
    namespace da {
        class IDAWidget{
        public:
            virtual QWidget* getWidget() = 0;
            virtual bool setParent(QWidget* pParent) = 0;
            virtual const QString getWidgetName() = 0;
            virtual ~IDAWidget() = default;
        };
    }
}
#define Hierarch_DA_IDAWidget_IID "hierarch.da.IDAWidget"
Q_DECLARE_INTERFACE(hierarch::da::IDAWidget, Hierarch_DA_IDAWidget_IID)
#endif

#ifndef HIERARCH_DA_IDATASHOWFACTORY_H
#define HIERARCH_DA_IDATASHOWFACTORY_H

#include <QWidget>
namespace hierarch {
    namespace da {
        class IDADataShowFactory{
        public:
            virtual ~IDADataShowFactory() = default;
            virtual QWidget* createView(bool bRecv) = 0;
            virtual void clearView() = 0;
        };
    }
}

#define Hierarch_DA_IDADataShowFactory_IID "hierarch.da.IDADataShowFactory"
Q_DECLARE_INTERFACE(hierarch::da::IDADataShowFactory, Hierarch_DA_IDADataShowFactory_IID)

#endif // IDATASHOWFACTORY_H

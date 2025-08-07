

#ifndef HIERARCH_DA__IDACIFD_h
#define HIERARCH_DA__IDACIFD_h

#include <QWidget>
namespace hierarch {
    namespace da {
        class IDACIFD{
        public:
            virtual QWidget* getWidget() = 0;
            virtual bool setParent(QWidget* pParent) = 0;
            virtual const QString getDeviceName() = 0;
            virtual ~IDACIFD() = default;
        };
    }
}

#define Hierarch_DA_IDACIFD_IID "hierarch.da.IDACIFD"
Q_DECLARE_INTERFACE(hierarch::da::IDACIFD, Hierarch_DA_IDACIFD_IID)
#endif



#ifndef HIERARCH_DA__IDAMAINWINDOW_h
#define HIERARCH_DA__IDAMAINWINDOW_h

#include <QMainWindow>
namespace hierarch {
    namespace da {
        class IDAMainWindow{
        public:
            virtual QMainWindow* getMainWindow() = 0;
            virtual bool setParent(QWidget* pParent) = 0;
            virtual ~IDAMainWindow() = default;
        };
    }
}

#define Hierarch_DA_IDAMainWindow_IID "hierarch.da.IDAMainWindow"
Q_DECLARE_INTERFACE(hierarch::da::IDAMainWindow, Hierarch_DA_IDAMainWindow_IID)

#endif

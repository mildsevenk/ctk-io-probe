TEMPLATE = subdirs
SUBDIRS +=  \
    application/Application.pro \
    hierarch.da.datashow/hierarch.da.datashow.pro \
    hierarch.da.recvctrl/hierarch.da.recvctrl.pro \
    hierarch.da.sendctrl/hierarch.da.sendctrl.pro \
    hierarch.da.com/hierarch.da.com.pro \
    hierarch.da.mainwindow/hierarch.da.mainwindow.pro \
    tests/tests.pro

CONFIG += ordered

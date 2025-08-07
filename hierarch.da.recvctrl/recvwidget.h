#ifndef RECVWIDGET_H
#define RECVWIDGET_H

#include <QWidget>
#include "IDAWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RecvWidget; }
QT_END_NAMESPACE

class RecvWidget : public QWidget, public hierarch::da::IDAWidget
{
    Q_OBJECT
    Q_INTERFACES(hierarch::da::IDAWidget)
public:
    explicit RecvWidget(QWidget *parent = nullptr);
    ~RecvWidget();
    virtual QWidget* getWidget();
    virtual bool setParent(QWidget* pParent);
    virtual const QString getWidgetName(){ return tr("hierarch.da.recvctrl"); }
    void setShowMode(bool bMode);
    void setLineWrap(bool bWrap);
private:
    Ui::RecvWidget *ui;
signals:
    void modeStatusChanged(bool bMode);
    void wrapStatusChanged(bool bWrap);
private slots:
    void onASCIICheckChanged(bool checked);
    void onHEXCheckChanged(bool checked);
    void onWrapCheckChanged(bool checked);
};

#endif // RECVWIDGET_H

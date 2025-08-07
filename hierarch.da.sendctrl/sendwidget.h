#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QWidget>
#include "IDAWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SendWidget; }
QT_END_NAMESPACE

class SendWidget : public QWidget, public hierarch::da::IDAWidget
{
    Q_OBJECT
    Q_INTERFACES(hierarch::da::IDAWidget)
public:
    explicit SendWidget(QWidget *parent = nullptr);
    ~SendWidget();
    virtual QWidget* getWidget();
    virtual bool setParent(QWidget* pParent);
    virtual const QString getWidgetName(){ return tr("hierarch.da.sendctrl"); }
    void setShowMode(bool bMode);
private:
    Ui::SendWidget *ui;
signals:
    void modeStatusChanged(bool bMode);
private slots:
    void onASCIICheckChanged(bool checked);
    void onHEXCheckChanged(bool checked);
};

#endif // SENDWIDGET_H

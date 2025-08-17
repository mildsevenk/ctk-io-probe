#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QWidget>
#include "IDAWidget.h"
#include <QButtonGroup>

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
    QButtonGroup* m_buttonGroup;
signals:
    void modeStatusChanged(bool bMode);
    void activeModeStatusChanged(bool bMode);
private slots:
    void onButtonClicked(QAbstractButton *button);
};

#endif // SENDWIDGET_H

#ifndef MAINWIDGETH_H
#define MAINWIDGETH_H

#include "IDAMainWindow.h"
#include <QHash>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindowe : public QMainWindow, public hierarch::da::IDAMainWindow
{
    Q_OBJECT
    Q_INTERFACES(hierarch::da::IDAMainWindow)
public:
    explicit MainWindowe(QWidget *parent = nullptr);
    ~MainWindowe();
    virtual QMainWindow* getMainWindow() override;
    virtual bool setParent(QWidget* pParent) override;
    void addDeviceType(QString strDeviceName, QWidget* pWidget);
    void initRecvSet(QWidget*);
    void initSendSet(QWidget*);
    void initRecvViewSet(QWidget*);
    void initSendViewSet(QWidget*);
    void uninitWidget();
    void removeDeviceType();
protected:
    virtual void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
private:
    QHash<QString, QWidget*> m_hs;
    QList<QWidget*> m_lstWidget;
signals:
    void sendButtonClicked();
private slots:
    void onBtnClicked();
};

#endif // MAINWIDGETH_H

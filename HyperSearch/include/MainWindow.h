#pragma once
#include <QObject>
#include <QtQml/QtQml>
#include "HostList.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HostModel* hostModel READ GetHostModel WRITE SetHostModel)

public:
    explicit MainWindow(QObject *parent = Q_NULLPTR);

    /** 网站列表 */
    HostModel* GetHostModel();
    void SetHostModel(HostModel* InModel);

public slots:
    
    QString openUrl();

private:

    HostModel* hostModel;
};

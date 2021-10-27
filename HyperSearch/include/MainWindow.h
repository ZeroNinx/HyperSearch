#pragma once
#include <QObject>
#include <QtQml/QtQml>
#include "QMLList.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMLListModel* hostModel READ GetHostModel WRITE SetHostModel)
    Q_PROPERTY(QMLListModel* resultModel READ GetResultModel WRITE SetResultModel)

public:
    explicit MainWindow(QObject *parent = Q_NULLPTR);

    /** 网站列表 */
    QMLListModel* GetHostModel();
    void SetHostModel(QMLListModel* InModel);

    /** 结果列表 */
    QMLListModel* GetResultModel();
    void SetResultModel(QMLListModel* InModel);

public slots:
    
    void copyText(QString KeyWord);
    void openUrl(QString KeyWord);

private:

    QMLListModel* hostModel;
    QMLListModel* resultModel;
};

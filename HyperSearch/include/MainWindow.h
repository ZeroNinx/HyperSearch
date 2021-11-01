#pragma once
#include <QObject>
#include <QtQml/QtQml>
#include <thread>
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

signals:
    
    /** 更新状态栏文本 */
    void updateStateBarText(QString newText);

public slots:
    
    /** QML槽函数 */
    void copyText(QString KeyWord);
    void search(QString KeyWord, int Site);
    void openUrl(QString Url);
    void enableHiddenMode();

    /** 多线程信号槽 */
    void onResultListUpdate();
    void onSearchHasNextPage(int SiteID, int NextPage);

private:

    /** QML变量 */
    QMLListModel* hostModel;
    QMLListModel* resultModel;
    
    /** 自定义 */
    QString KeyWord;
};

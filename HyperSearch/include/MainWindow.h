#pragma once
#include <QObject>
#include <QtQml/QtQml>
#include <thread>
#include "QMLList.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMLListModel* hostModel READ GetHostModel WRITE SetHostModel NOTIFY onHostModelChanged)
    Q_PROPERTY(QMLListModel* resultModel READ GetResultModel WRITE SetResultModel NOTIFY onResultModelChanged)

public:
    explicit MainWindow(QObject *parent = Q_NULLPTR);

    /** 网站列表 */
    QMLListModel* GetHostModel();
    void SetHostModel(QMLListModel* InModel);

    /** 结果列表 */
    QMLListModel* GetResultModel();
    void SetResultModel(QMLListModel* InModel);

signals:
    
    /** QML成员变量NOTIFY信号 */
    void onHostModelChanged();
    void onResultModelChanged();

    /** QML信号 */
    void updateUpdateCheckBarText(QString newText);
    void updateStateBarText(QString newText);
    void hideTerminateButton();
    void showTerminateButton();

public slots:

    /** QML槽函数 */
    void copyText(QString KeyWord);
    void search(QString KeyWord, int Site);
    void openUrl(QString Url);
    void enableHiddenMode();
    void terminateSearch();

    /** 多线程槽函数 */
    void onListModelUpdate(QMLListModel* Model);
    void onSearchHasNextPage(int SiteID, int NextPage);

private:

	/** 状态栏显示搜索完成 */
	void ShowSearhResultHint();

private:
 
    /** QML变量 */
    QMLListModel* hostModel;
    QMLListModel* resultModel;

private:

    /** 同一网站，间隔5秒搜索一次，防止被夹 */
    const int SearchInterval = 5000;

    /** 搜索线程数 */
    int SearchThreadCount = 0;

    /** 是否继续搜索 */
    bool bShouldContinueSearch = true;

    /** 当前搜索关键词 */
    QString CurrentKeyWord;

};

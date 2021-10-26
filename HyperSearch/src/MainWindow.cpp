#include "MainWindow.h"
#include "QMLListTypes.h"


MainWindow::MainWindow(QObject *parent)
{
	hostModel = new QMLListModel();
	hostModel->SetTemplate(Host());
	hostModel->AddItem(Host( QStringLiteral("搜索引擎"), 0 ));

	resultModel = new QMLListModel();
	resultModel->SetTemplate(Result());
}


QMLListModel* MainWindow::GetHostModel()
{
	return hostModel;
}

void MainWindow::SetHostModel(QMLListModel* InModel)
{
	if(hostModel)
		hostModel->disconnect(this);

	hostModel = InModel;
}

QMLListModel* MainWindow::GetResultModel()
{
	return resultModel;
}

void MainWindow::SetResultModel(QMLListModel* InModel)
{
	if (resultModel)
		resultModel->disconnect(this);

	resultModel = InModel;
}

void MainWindow::openUrl()
{
	resultModel->AddItem(Result(QStringLiteral("百度"), QStringLiteral("www.baidu.com")));
	resultModel->AddItem(Result(QStringLiteral("谷歌"), QStringLiteral("www.google.com")));
}

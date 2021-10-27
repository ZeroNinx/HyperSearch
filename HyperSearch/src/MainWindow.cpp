#include <QDebug>
#include <QGuiApplication>
#include <QClipboard>

#include "MainWindow.h"
#include "QMLListTypes.h"
#include "ResSite.h"

/** 构造函数 */
MainWindow::MainWindow(QObject *parent)
{
	/** 网站列表 */
	hostModel = new QMLListModel();
	hostModel->SetTemplate(Host());
	hostModel->AddItem(Host( QStringLiteral("搜索引擎"), 0 ));

	/** 结果列表 */
	resultModel = new QMLListModel();
	resultModel->SetTemplate(Result());
}

/** 网站列表 */
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

/** 结果列表 */
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

void MainWindow::copyText(QString KeyWord)
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	clipboard->setText(KeyWord);
}

void MainWindow::openUrl(QString InKeyWord)
{
	resultModel->Clear();

	TorrentSite_BTSOW btsow = TorrentSite_BTSOW();
	for (Resource& res: btsow.Search(InKeyWord.toStdString()))
	{
		resultModel->AddItem(Result(tr(res.Name.c_str()), tr(res.Url.c_str())));
	}

	resultModel->AddItem(Result(QStringLiteral("百度"), QStringLiteral("www.baidu.com")));
	resultModel->AddItem(Result(QStringLiteral("谷歌"), QStringLiteral("www.google.com")));
}

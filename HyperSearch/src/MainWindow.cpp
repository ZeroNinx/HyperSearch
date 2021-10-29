#include <QDebug>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QClipboard>

#include "MainWindow.h"
#include "QMLListTypes.h"
#include "ResSite/SiteFactory.h"

/** 构造函数 */
MainWindow::MainWindow(QObject *parent)
{
	/**
	 * 初始化基础列表
	 */

	/** 网站列表 */
	hostModel = new QMLListModel();
	hostModel->SetTemplate(Host());
	hostModel->AddItem(Host( QStringLiteral("BTSOW"), TorrentSite_BTSOW ));
	hostModel->AddItem(Host( QStringLiteral("EdgeEmu"), ConsoleRomSite_EdgeEmu));
	hostModel->AddItem(Host( QStringLiteral("CoolRom"), ConsoleRomSite_CoolRom ));

	/** 结果列表 */
	resultModel = new QMLListModel();
	resultModel->SetTemplate(Result());
	resultModel->AddItem(Result(QStringLiteral("搜索Start!")));
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

void MainWindow::search(QString InKeyWord, int SiteID)
{
	if (InKeyWord.isEmpty())
		return;

	ResSite* resSite = SiteFacory::GetSite(SiteID);
	if (resSite == nullptr)
		return;

	resultModel->Clear();
	
	auto asyncLoad = [=]()
	{
		std::vector<Resource>& searchResult = resSite->Search(InKeyWord.toStdString());
		if (searchResult.size())
		{
			QString hintText = QString("以下是 \"") + InKeyWord + "\" 的搜索结果：";
			resultModel->AddItem(Result(hintText));
			for (Resource& res : searchResult)
			{
				resultModel->AddItem(Result(res));
			}
			resultModel->AddItem(Result(QStringLiteral("搜索完成")));
		}
		else
		{
			QString hintText = QString("搜索失败！请检查网络链接或者关键字！");
			resultModel->AddItem(Result(hintText));
		}

		delete resSite;
	};
	
	std::thread loadThread(asyncLoad);
	loadThread.join();

}

void MainWindow::openUrl(QString InUrl)
{
	QDesktopServices::openUrl(InUrl);
}

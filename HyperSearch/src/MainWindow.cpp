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
	hostModel->AddItem(Host(QStringLiteral("搜索模拟Rom"), (int)SiteType::ConsoleRomSite));
	hostModel->AddItem(Host( QStringLiteral("搜索种子"), (int)SiteType::TorrentSite ));

	/** 结果列表 */
	resultModel = new QMLListModel();
	resultModel->SetTemplate(Result());
	resultModel->AddItem(Result(QStringLiteral("搜索Start!")));

	/** 连接多线程信号槽 */
	connect(resultModel, &QMLListModel::postEndAddItem, this, &MainWindow::onResultListUpdate);
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

void MainWindow::search(QString InKeyWord, int InSiteType)
{
	//获取网站列表
	int startID = 0, endID = 0;
	SiteFacory::GetAllSiteIndex(InSiteType, startID, endID);
	if (!startID || !endID || InKeyWord.isEmpty())
	{
		return;
	}
	startID++;
	endID--;

	//多线程搜索
	resultModel->Clear();
	for (int i = startID ; i <= endID; i++)
	{
		auto asyncLoad = [=]()
		{
			ResSite* site = SiteFacory::GetSite(i);
			if (site)
			{
				QVector<QMLListItem> vec;
				std::vector<Resource> searchResults = site->Search(InKeyWord.toStdString());
				for (Resource& res : searchResults)
				{
					vec.append(Result(res));
				}
				resultModel->DynamicAddItems(vec);
				delete site;
			}
		};

		std::thread thread(asyncLoad);
		thread.detach();
	}
}

void MainWindow::openUrl(QString InUrl)
{
	QDesktopServices::openUrl(InUrl);
}

void MainWindow::onResultListUpdate()
{
	resultModel->FinishDynamicAddItem();
}

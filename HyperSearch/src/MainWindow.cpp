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

	SiteFacory::InitSiteInfo();

	/** 网站列表 */
	hostModel = new QMLListModel();
	hostModel->SetTemplate(Host());
	hostModel->AddItem(Host(QStringLiteral("搜索模拟Rom"), ResSiteType::ConsoleRomSite));
	hostModel->AddItem(Host(QStringLiteral("搜索种子"), ResSiteType::TorrentSite ));

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


/** 自定义 */
void MainWindow::ShowSearhResultHint()
{
	int ResultSum = resultModel->GetListObject()->GetList().size();
	emit updateStateBarText(tr("搜索完成......找到结果：") + tr(to_string(ResultSum).c_str()));
}


/** 槽函数 */
void MainWindow::copyText(QString KeyWord)
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	clipboard->setText(KeyWord);
}

void MainWindow::search(QString InKeyWord, int InSiteType)
{
	KeyWord = InKeyWord;
	bShouldContinueSearch = true;
	emit showTerminateButton();

	//获取网站列表
	int startID = 0, endID = 0;
	SiteFacory::GetAllSiteIndex((ResSiteType)InSiteType, startID, endID);
	if (!startID || !endID || InKeyWord.isEmpty())
	{
		return;
	}
	startID++;
	endID--;

	//多线程搜索
	resultModel->Clear();
	for (int siteID = startID ; siteID <= endID; siteID++)
	{
		ResSite* site = SiteFacory::GetSite((ResSiteID)siteID);
		
		if (site)
		{
			SearchThreadCount++;
			connect(site, &ResSite::postFoundNextPage, this, &MainWindow::onSearchHasNextPage );
			auto asyncLoad = [=]()
			{
				std::this_thread::sleep_for(chrono::milliseconds(1000 * (siteID - startID)));
				emit updateStateBarText(tr(site->Name.c_str()) + "搜索中(1)...");

				QVector<QMLListItem> itemsToAdd;
				QVector<Resource> searchResults;

				site->Search(searchResults, KeyWord);
				for (Resource& res : searchResults)
				{
					itemsToAdd.append(Result(res));
				}
				resultModel->DynamicAddItems(itemsToAdd);
				delete site;

				this->SearchThreadCount--;
				if (this->SearchThreadCount == 0)
				{
					ShowSearhResultHint();
				}
			};

			std::thread thread(asyncLoad);
			thread.detach();
		}
	}
}

void MainWindow::openUrl(QString InUrl)
{
	QDesktopServices::openUrl(InUrl);
}

void MainWindow::enableHiddenMode()
{
	
}

void MainWindow::terminateSearch()
{
	bShouldContinueSearch = false;
	emit updateStateBarText(tr("搜索终止......"));
	emit hideTerminateButton();

	auto showResult = [=]()
	{
		//两秒后显示结果
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		ShowSearhResultHint();
	};

	std::thread thread(showResult);
	thread.detach();
}


/** 多线程 */
void MainWindow::onResultListUpdate()
{
	resultModel->FinishDynamicAddItem();
}

void MainWindow::onSearchHasNextPage(int InSiteID, int NextPage)
{
	ResSite* site = SiteFacory::GetSite((ResSiteID)InSiteID);
	if (site)
	{
		SearchThreadCount++;
		auto asyncLoadNextPage = [=]()
		{
			std::this_thread::sleep_for(chrono::milliseconds(SearchInterval));
			if (!this->bShouldContinueSearch)
			{
				this->SearchThreadCount--;
				return;
			}

			connect(site, &ResSite::postFoundNextPage, this, &MainWindow::onSearchHasNextPage);

			emit updateStateBarText(tr(site->Name.c_str()) + "搜索中(" + tr(to_string(NextPage).c_str()) + ")...");

			QVector<QMLListItem> itemsToAdd;
			QVector<Resource> searchResults;

			site->SearchPage(searchResults, KeyWord, NextPage);
			for (Resource& res : searchResults)
			{
				itemsToAdd.append(Result(res));
			}
			resultModel->DynamicAddItems(itemsToAdd);

			delete site;

			this->SearchThreadCount--;
			if (this->SearchThreadCount == 0)
			{
				ShowSearhResultHint();
			}

		};

		std::thread thread(asyncLoadNextPage);
		thread.detach();
	}
}

#pragma once

#include <string>
#include <vector>
#include <regex>
#include <QDebug>
#include "ToolBox.h"
#include "HttpConn.h"

using namespace std;
using namespace boost::beast::http;

#define UA_CHROME "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Safari/537.36"
#define TorrentHeader "magnet:?xt=urn:btih:"

//网站枚举
enum class ResSiteID : int
{
	None = Qt::UserRole + 1,

	//Rom网站
	Begin_ConsoleRomSite,
	ConsoleRomSite_EdgeEmu,
	ConsoleRomSite_CoolRom,
	End_ConsoleRomSite,

	//Torrent网站
	Begin_TorrentSite,
	TorrentSite_BTSOW,
	TorrentSite_SOBT,
	End_TorrentSite
};

enum class ResSiteType : int
{
	None = Qt::UserRole + 1,
	ConsoleRomSite,
	TorrentSite
};

//资源类
class Resource
{
public:

	Resource(std::string Text, std::string PageUrl = "", std::string DiskUrl = "", std::string DownloadUrl = "", ResSiteID ID = ResSiteID::None);

	std::string Text;
	std::string PageUrl;
	std::string DiskUrl;
	std::string DownloadUrl;
	ResSiteID SiteID;
};

//资源网站类 
class ResSite:public QObject
{
	Q_OBJECT
public:

	explicit ResSite() {};
	ResSite(
		std::string Name= "",
		std::string Url="",
		ResSiteType SiteType=ResSiteType::None,
		ResSiteID SiteID = ResSiteID::None);

	virtual void Search(QVector<Resource>& Result, QString& KeyWord);

	virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page);

signals:

	void postFoundNextPage(int Site, int NextPage);

protected:

	std::string Name;
	std::string Url;
	ResSiteID SiteID;
	ResSiteType SiteType;
};


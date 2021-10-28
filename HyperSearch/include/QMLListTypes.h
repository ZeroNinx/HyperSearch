#include "QMLList.h"
#include "ResSite.h"

//网站枚举
enum SiteName
{
	ConsoleRomSite_EdgeEmu = Qt::UserRole + 1,
	ConsoleRomSite_CoolRom,
	TorrentSite_BTSOW
};

//网站类
class Host:public QMLListItem
{
public:
	explicit Host()
	{
		roleNames[NameRole] = "name";
		roleNames[SiteRole] = "site";
	}

	Host(QString Name, SiteName Site)
	{
		roleProperty[NameRole] = Name;
		roleProperty[SiteRole] = QString::fromLocal8Bit(to_string(Site).c_str());
	};

	enum HostRoles
	{
		NameRole = Qt::UserRole + 1,
		SiteRole
	};
};


//搜索结果类
class Result :public QMLListItem
{
public:
	explicit Result()
	{
		roleNames[TextRole] = "text";
		roleNames[PageUrlRole] = "pageUrl";
		roleNames[DiskUrlRole] = "diskUrl";
		roleNames[DownloadUrlRole] = "downloadUrl";
	}

	Result(Resource& InResource):Result(QString(InResource.Text.c_str()), QString(InResource.PageUrl.c_str()), QString(InResource.DiskUrl.c_str()), QString(InResource.DownloadUrl.c_str()))
	{
		
	}

	Result(QString& Text, QString& PageUrl = QString(""), QString& DiskUrl = QString(""), QString& DownloadUrl = QString(""))
	{
		roleProperty[TextRole] = Text;
		roleProperty[PageUrlRole] = PageUrl;
		roleProperty[DiskUrlRole] = DiskUrl;
		roleProperty[DownloadUrlRole] = DownloadUrl;
	}

	enum ResultRoles
	{
		TextRole = Qt::UserRole + 1,
		PageUrlRole,
		DiskUrlRole,
		DownloadUrlRole
	};
};

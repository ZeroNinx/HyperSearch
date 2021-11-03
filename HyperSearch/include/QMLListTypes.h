#include "QMLList.h"
#include "ResSite/ResSite.h"
#include "ResSite/SiteFactory.h"

//网站类
class Host:public QMLListItem
{
public:
	explicit Host()
	{
		roleNames[NameRole] = "name";
		roleNames[SiteTypeRole] = "siteType";
	}

	Host(QString Name, ResSiteType SiteID)
	{
		roleProperty[NameRole] = Name;
		roleProperty[SiteTypeRole] = QString::fromLocal8Bit(to_string((int)SiteID).c_str());
	};

	enum HostRoles
	{
		NameRole = Qt::UserRole + 1,
		SiteTypeRole
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
		roleNames[SiteIconRole] = "siteIcon";
	}

	Result(Resource& InResource):Result(QString(InResource.Text.c_str()), QString(InResource.PageUrl.c_str()), QString(InResource.DiskUrl.c_str()), QString(InResource.DownloadUrl.c_str()), InResource.SiteID)
	{
		
	}

	Result(QString& Text, QString& PageUrl = QString(""), QString& DiskUrl = QString(""), QString& DownloadUrl = QString(""), ResSiteID SiteID = ResSiteID::None)
	{
		roleProperty[TextRole] = Text;
		roleProperty[PageUrlRole] = PageUrl;
		roleProperty[DiskUrlRole] = DiskUrl;
		roleProperty[DownloadUrlRole] = DownloadUrl;
		roleProperty[SiteIconRole] = SiteFacory::GetSiteIcon(SiteID);
	}

	enum ResultRoles
	{
		TextRole = Qt::UserRole + 1,
		PageUrlRole,
		DiskUrlRole,
		DownloadUrlRole,
		SiteIconRole
	};
};

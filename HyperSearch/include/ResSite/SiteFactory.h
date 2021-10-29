#pragma once
#include "ResSite/ConsoleRomSite.h"
#include "ResSite/TorrentSite.h"

using namespace ConsoleRomSite;
using namespace TorrentSite;

//网站枚举
enum class SiteID: int
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
	End_TorrentSite
};

enum class SiteType: int
{
	None = Qt::UserRole + 1,
	ConsoleRomSite,
	TorrentSite
};

namespace SiteFacory
{
	//根据ID取得网站
	inline ResSite* GetSite(int InSiteID)
	{
		switch (InSiteID)
		{
		case SiteID::ConsoleRomSite_EdgeEmu:
			return new EdgeEmu();

		case SiteID::ConsoleRomSite_CoolRom:
			return new CoolRom();

		case SiteID::TorrentSite_BTSOW:
			return new BTSOW();

		default:
			return nullptr;
		}
	}

	//搜索某类的所有网站
	inline void GetAllSiteIndex(int InSiteType, int& StartIndex, int& EndIndex)
	{
		switch (InSiteType)
		{
		case SiteType::ConsoleRomSite:
			StartIndex = (int)SiteID::Begin_ConsoleRomSite;
			EndIndex = (int)SiteID::End_ConsoleRomSite;
			break;

		case SiteType::TorrentSite:
			StartIndex = (int)SiteID::Begin_TorrentSite;
			EndIndex = (int)SiteID::End_TorrentSite;
			break;

		default:
			break;
		}

	}
}

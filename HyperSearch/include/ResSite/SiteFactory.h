#pragma once
#include "ResSite/ConsoleRomSite.h"
#include "ResSite/TorrentSite.h"

using namespace ConsoleRomSite;
using namespace TorrentSite;

namespace SiteFacory
{
	//根据ID取得网站
	inline ResSite* GetSite(int InSiteID)
	{
		switch (InSiteID)
		{
		case SiteID::ConsoleRomSite_EdgeEmu: return new EdgeEmu();

		case SiteID::ConsoleRomSite_CoolRom: return new CoolRom();

		case SiteID::TorrentSite_BTSOW: return new BTSOW();

		case SiteID::TorrentSite_SOBT: return new SOBT();

		default: return nullptr;
		}
	}

	inline QString GetSiteIcon(int InSiteID)
	{
		switch (InSiteID)
		{
		case SiteID::ConsoleRomSite_EdgeEmu: return QString("../Icon/EdgeEmu.ico");

		case SiteID::ConsoleRomSite_CoolRom: return QString("../Icon/CoolRom.ico");

		case SiteID::TorrentSite_BTSOW: return QString("../Icon/BTSOW.ico");

		case SiteID::TorrentSite_SOBT: return QString("../Icon/SOBT.ico");

		default: return QString();
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

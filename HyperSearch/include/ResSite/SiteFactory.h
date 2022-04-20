#pragma once
#include <unordered_map>
#include "ResSite/ConsoleRomSite.h"
#include "ResSite/TorrentSite.h"

using namespace ConsoleRomSite;
using namespace TorrentSite;

namespace SiteFacory
{
	struct SiteInfo
	{
		QString IconPath;
	};



	static std::unordered_map<ResSiteID, SiteInfo> SiteMap;

	static void InitSiteInfo()
	{
		SiteMap[ResSiteID::ConsoleRomSite_EdgeEmu]		=	{ QString("../Icon/EdgeEmu.ico") };
		SiteMap[ResSiteID::ConsoleRomSite_CoolRom]		=	{ QString("../Icon/CoolRom.ico") };
		SiteMap[ResSiteID::TorrentSite_BTSOW]			=	{ QString("../Icon/BTSOW.ico") };
		SiteMap[ResSiteID::TorrentSite_TorrentKitty]	=	{ QString("../Icon/TorrentKitty.ico") };
		SiteMap[ResSiteID::TorrentSite_SOBT]			=	{ QString("../Icon/SOBT.ico") };
	}

	//根据ID取得网站（单例模式）

	EdgeEmu* edgeEmu = new EdgeEmu();
	CoolRom* coolRom = new CoolRom();
	BTSOW* btsow = new BTSOW();
	TorrentKitty* torrentKitty = new TorrentKitty();
	SOBT* sobt = new SOBT();

	inline ResSite* GetSite(ResSiteID InSiteID)
	{
		switch (InSiteID)
		{
		case ResSiteID::ConsoleRomSite_EdgeEmu:		return edgeEmu;

		case ResSiteID::ConsoleRomSite_CoolRom:		return coolRom;

		case ResSiteID::TorrentSite_BTSOW:			return btsow;

		case ResSiteID::TorrentSite_TorrentKitty:	return torrentKitty;

		case ResSiteID::TorrentSite_SOBT:			return sobt;

		default: return nullptr;
		}
	}

	inline QString GetSiteIcon(ResSiteID InSiteID)
	{
		if (SiteMap.find(InSiteID) != SiteMap.end())
			return SiteMap[InSiteID].IconPath;
		return QString();
	}

	//搜索某类的所有网站
	inline void GetAllSiteIndex(ResSiteType InSiteType, int& StartIndex, int& EndIndex)
	{
		switch (InSiteType)
		{
		case ResSiteType::ConsoleRomSite:
			StartIndex = (int)ResSiteID::Begin_ConsoleRomSite + 1;
			EndIndex = (int)ResSiteID::End_ConsoleRomSite - 1;
			break;

		case ResSiteType::TorrentSite:
			StartIndex = (int)ResSiteID::Begin_TorrentSite + 1;
			EndIndex = (int)ResSiteID::End_TorrentSite - 1;
			break;

		default:
			break;
		}
	}

}

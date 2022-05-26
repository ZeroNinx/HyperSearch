#pragma once
#include <unordered_map>
#include "ResSite/ConsoleRomSite.h"
#include "ResSite/TorrentSite.h"

using namespace ConsoleRomSite;
using namespace TorrentSite;

namespace SiteFacory
{
	//网站信息结构体
	struct SiteInfo
	{
		ResSite* SiteInstance;	//网站实例指针，确保网站是单例模式
		QString IconPath;		//网站图标
	};

	//网站ID和网站信息的映射表
	static std::unordered_map<ResSiteID, SiteInfo> SiteMap;

	// 初始化网站图标和实例
	static void InitSiteInfo()
	{
		SiteMap[ResSiteID::ConsoleRomSite_EdgeEmu]		= { new EdgeEmu(),		QString("../Icon/EdgeEmu.ico") };
		SiteMap[ResSiteID::ConsoleRomSite_CoolRom]		= { new CoolRom(),		QString("../Icon/CoolRom.ico") };
		SiteMap[ResSiteID::TorrentSite_BTSOW]			= { new BTSOW(),		QString("../Icon/BTSOW.ico") };
		SiteMap[ResSiteID::TorrentSite_SOBT]			= { new SOBT(),			QString("../Icon/SOBT.ico") };
		SiteMap[ResSiteID::TorrentSite_TorrentKitty]	= { new TorrentKitty(), QString("../Icon/TorrentKitty.ico") };
		SiteMap[ResSiteID::TorrentSite_Comicat]			= { new Comicat(),		QString("../Icon/Comicat.ico") };
	}

	inline ResSite* GetSite(ResSiteID SiteID)
	{
		if (SiteMap.find(SiteID) != SiteMap.cend())
		{
			return SiteMap[SiteID].SiteInstance;
		}
		else
		{
			return nullptr;
		}
	}

	inline QString GetSiteIcon(ResSiteID InSiteID)
	{
		if (SiteMap.find(InSiteID) != SiteMap.end())
		{
			return SiteMap[InSiteID].IconPath;
		}
		else
		{
			return QString();
		}
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

#pragma once
#include "ResSite/ConsoleRomSite.h"
#include "ResSite/TorrentSite.h"

using namespace ConsoleRomSite;
using namespace TorrentSite;

//网站枚举
enum SiteID
{
	ConsoleRomSite_EdgeEmu = Qt::UserRole + 1,
	ConsoleRomSite_CoolRom,
	TorrentSite_BTSOW
};

namespace SiteFacory
{
	inline ResSite* GetSite(int SiteID)
	{
		switch (SiteID)
		{
		case ConsoleRomSite_EdgeEmu:
			return new EdgeEmu();

		case ConsoleRomSite_CoolRom:
			return new CoolRom();

		case TorrentSite_BTSOW:
			return new BTSOW();

		default:
			return nullptr;
		}

	}
}

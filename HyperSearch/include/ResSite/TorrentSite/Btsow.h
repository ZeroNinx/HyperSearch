#pragma once
#include "ResSite.h"

namespace TorrentSite
{
	//BTSOW
	class BTSOW :public ResSite
	{
	public:
		virtual std::vector<Resource>& Search(std::string KeyWord) override;
	};
}
#pragma once
#include "ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class EdgeEmu :public ResSite
	{
	public:
		virtual std::vector<Resource>& Search(std::string KeyWord) override;
	};

}

#pragma once
#include "ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class CoolRom :public ResSite
	{
	public:
		virtual std::vector<Resource>& Search(std::string KeyWord) override;
	};

}

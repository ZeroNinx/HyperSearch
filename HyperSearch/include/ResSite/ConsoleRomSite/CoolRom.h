#pragma once
#include "ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class CoolRom :public ResSite
	{
	public:
		virtual void Search(QVector<Resource>& Result, QString KeyWord) override;
	};

}

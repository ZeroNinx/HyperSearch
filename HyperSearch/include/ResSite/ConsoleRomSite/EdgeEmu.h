#pragma once
#include "ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class EdgeEmu :public ResSite
	{
	public:
		virtual void Search(QVector<Resource>& Result, QString KeyWord) override;
	};

}

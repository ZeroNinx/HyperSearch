#pragma once
#include "ResSite/ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class EdgeEmu :public ResSite
	{
	public:
		EdgeEmu();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;
	};

}

#pragma once
#include "ResSite/ResSite.h"

namespace ConsoleRomSite
{
	//BTSOW
	class CoolRom :public ResSite
	{
	public:
		CoolRom();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;
	};

}

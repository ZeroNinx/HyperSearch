#pragma once
#include "ResSite.h"

namespace TorrentSite
{
	//BTSOW
	class BTSOW :public ResSite
	{
	public:
		BTSOW();
		virtual void Search(QVector<Resource>& Result, QString KeyWord) override;
	};
}
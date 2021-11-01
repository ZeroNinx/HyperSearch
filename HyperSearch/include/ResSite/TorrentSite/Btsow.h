#pragma once
#include "ResSite.h"

namespace TorrentSite
{
	//BTSOW
	class BTSOW :public ResSite
	{
	public:
		BTSOW();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;

		virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page) override;
	};
}
#pragma once
#include "ResSite/ResSite.h"

namespace TorrentSite
{
	//Comicat
	class Comicat :public ResSite
	{
	public:
		Comicat();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;

		virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page) override;

	};
}

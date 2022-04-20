#pragma once
#include "ResSite/ResSite.h"

namespace TorrentSite
{
	//TorrentKitty
	class TorrentKitty :public ResSite
	{
	public:
		TorrentKitty();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;

		virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page) override;
	};
}

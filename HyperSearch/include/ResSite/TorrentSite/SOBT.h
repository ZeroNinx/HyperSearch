#pragma once
#include "ResSite/ResSite.h"

namespace TorrentSite
{
	//SOBT
	class SOBT :public ResSite
	{
	public:
		SOBT();

		virtual void Search(QVector<Resource>& Result, QString& KeyWord) override;

		virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page) override;

	private:

		void GetCookie();

		static std::string cookie;
	};
}

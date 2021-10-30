#pragma once
#include "ResSite.h"

namespace TorrentSite
{
	//SOBT
	class SOBT :public ResSite
	{
	public:

		virtual void Search(QVector<Resource>& Result, QString KeyWord) override;

		virtual void SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page) override;

	private:

		void GetCookie();
		void SearchRecuesive(std::string KeyWord,int page);

		static std::string cookie;
	};
}

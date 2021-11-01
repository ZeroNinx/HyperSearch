#include "ResSite/TorrentSite/BTSOW.h"

TorrentSite::BTSOW::BTSOW() : ResSite("BTSWO", "btsow.rest", ResSiteType::TorrentSite, ResSiteID::TorrentSite_BTSOW)
{

}

void TorrentSite::BTSOW::Search(QVector<Resource>& Result, QString& KeyWord)
{
	SearchPage(Result, KeyWord, 1);
}

void TorrentSite::BTSOW::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{
	//建立连接
	HttpsConn Btsow(Url);
	Btsow.Build("/search/" + KeyWord.toStdString() + "/page/" + to_string(Page));
	Btsow.Request.set(field::user_agent, UA_CHROME);
	Btsow.Connect();

	//数据处理
	string str = ToolBox::CutString(Btsow.GetResponseBody(), "<div class=\"col-sm-8 col-lg-9 field\">Torrent Description</div>", "<div type=\"text/data-position\"");
	if (str.size())
	{
		regex r("<a href=\"//btsow.rest/magnet/detail/hash/([^\"]+)\".*title=\"([^\"]+)\">");
		sregex_iterator pos = sregex_iterator(str.begin(), str.end(), r);
		sregex_iterator end;
		for (; pos != end; ++pos)
		{
			string& all = pos->str(0);
			string& hash = pos->str(1);
			string& name = pos->str(2);

			Result.push_back(Resource(name, "https://" + Url + "/magnet/detail/hash/" + hash, "", TorrentHeader + hash, SiteID));
		}
	}

	//检查下一页
	str = ToolBox::CutString(Btsow.GetResponseBody(), "<ul class=\"pagination pagination-lg\">", "<h3 class=\"visible-xs-block\">Latest Search:</h3>");
	regex e("<a name=\"nextpage\"  href=\".+page/([^\"]+)\">");
	smatch m;
	bool found = regex_search(str, m, e);
	if (found)
	{
		int next_page = QString(m.str(1).c_str()).toInt();
		emit postFoundNextPage((int)SiteID, next_page);
	}
}


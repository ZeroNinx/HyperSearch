#include "ResSite/TorrentSite/TorrentKitty.h"

TorrentSite::TorrentKitty::TorrentKitty() :ResSite("TorrentKitty", "torrentkitty.live", ResSiteType::TorrentSite, ResSiteID::TorrentSite_TorrentKitty)
{

}

void TorrentSite::TorrentKitty::Search(QVector<Resource>& Result, QString& KeyWord)
{
	SearchPage(Result, KeyWord, 1);
}

void TorrentSite::TorrentKitty::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{
	//搜索链接
	HttpsConn conn(Url);
	conn.Build("/search/" + KeyWord.toStdString() + "/" + to_string(Page), verb::get);
	conn.Request.set(http::field::user_agent, UA_CHROME);
	conn.Connect();

	//数据裁剪
	string str = ToolBox::CutString(conn.GetResponseBody(), "<table id=\"archiveResult\">", "<div class=\"pagination\">");
	if (str.length())
	{
		//数据提取
		regex r("<td class=\"action\"><a href=\"/information/(.+)\"[\\s]*title=\"(.+)\"[\\s]*rel=\".+\">.+</a><a href=\"(.+)\">");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;

		//生成结果
		for (; pos != end; ++pos)
		{
			string&& all = pos->str(0);
			string&& hash = pos->str(1);
			string&& name = pos->str(2);
			string&& download_link = pos->str(3);

			Result.push_back(Resource(name, "https://" + Url + "/information/" + hash, download_link, SiteID));
		}
	}

	//检查下一页
	str = ToolBox::CutString(conn.GetResponseBody(), "<div class=\"pagination\">", "<table id=\"archiveResult\">");
	regex e("<a href=\"([0-9]+)\">»</a>");
	smatch m;
	bool found = regex_search(str, m, e);
	if (found)
	{
		int next_page = QString(m.str(1).c_str()).toInt();
		emit postFoundNextPage((int)SiteID, next_page);
	}
}
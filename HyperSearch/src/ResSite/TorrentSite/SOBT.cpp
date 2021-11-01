#include "ResSite/TorrentSite/SOBT.h"

TorrentSite::SOBT::SOBT() :ResSite("SOBT", "sobt2.me", ResSiteType::TorrentSite, ResSiteID::TorrentSite_SOBT)
{

}

void TorrentSite::SOBT::Search(QVector<Resource>& Result, QString& KeyWord)
{
	//获得cookie
	if (cookie == "")
		GetCookie();

	SearchPage(Result, KeyWord, 1);
}

void TorrentSite::SOBT::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{
	//搜索链接
	HttpConn conn(Url);
	conn.Build("/q/" + KeyWord.toStdString() + ".html?sort=rel&page=" + to_string(Page), verb::post);
	conn.Request.set(http::field::user_agent, UA_CHROME);
	conn.Request.set(http::field::cookie, cookie);
	conn.Connect();

	//数据裁剪
	string str = ToolBox::CutString(conn.GetResponseBody(), "<div class=\"search-list", "<ul class=\"pagination\">");
	if (str.length())
	{
		//数据提取
		regex r("<h3><a href=\"/torrent/(.+).html\">(.+)</a></h3>");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;

		//生成结果
		for (; pos != end; ++pos)
		{
			string& all = pos->str(0);
			string& hash = pos->str(1);
			string& name = pos->str(2);

			//去除斜字体标识
			if (name.find("<em>") != name.npos)
			{
				name.replace(name.find("<em>"), 4, "");
				name.replace(name.find("</em>"), 5, "");
			}
			Result.push_back(Resource(name, "http://" + Url + "/torrent/" + hash + ".html", "", TorrentHeader + hash, SiteID));
		}
	}

	//检查下一页
	str = ToolBox::CutString(conn.GetResponseBody(), "<ul class=\"pagination\">", "<div class=\"search-tips");
	regex e("<li class=\"nextpage\"><a href=\".+page=([^\"]+)\">&raquo;</a></li>");
	smatch m;
	bool found = regex_search(str, m, e);
	if (found)
	{
		int next_page = QString(m.str(1).c_str()).toInt();
		emit postFoundNextPage((int)SiteID, next_page);
	}
}

void TorrentSite::SOBT::GetCookie()
{
	HttpConn conn("sobt2.me");
	conn.Build("/",verb::get);
	conn.Request.set(http::field::user_agent, UA_CHROME);
	conn.Connect();

	//遍历Header
	auto headerMap = conn.GetResponseHeader();
	if (headerMap.find(http::field::set_cookie)!=headerMap.end())
	{
		string str = headerMap[http::field::set_cookie];

		//提取Cookie
		regex r("([^=]+)=([^;]+);");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;
		for (; pos != end; ++pos)
		{
			string& all = pos->str(0);
			string& name = pos->str(1);
			string& value = pos->str(2);

			cookie.append(name + "=" + value + ";");
		}

		//对应Chrome的UA
		cookie.append("Challenge=9ceebc4ad83ababb94d4029b4dca4e66;");
	}
}

std::string TorrentSite::SOBT::cookie = "";

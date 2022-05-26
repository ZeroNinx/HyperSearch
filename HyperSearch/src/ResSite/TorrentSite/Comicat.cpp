#include "ResSite/TorrentSite/Comicat.h"

TorrentSite::Comicat::Comicat() :ResSite("Comicat", "www.comicat.org", ResSiteType::TorrentSite, ResSiteID::TorrentSite_Comicat)
{

}

void TorrentSite::Comicat::Search(QVector<Resource>& Result, QString& KeyWord)
{
	SearchPage(Result, KeyWord, 1);
}

void TorrentSite::Comicat::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{
	//搜索链接
	HttpConn conn(Url);
	conn.Build("/search.php?keyword=" + KeyWord.toStdString() + "&page=" + to_string(Page), verb::get);
	conn.Request.set(http::field::user_agent, UA_CHROME);
	conn.Connect();

	//数据裁剪
	string str = ToolBox::CutString(conn.GetResponseBody(), 
		"<table id=\"listTable\" class=\"list_style table_fixed\">", 
		"<div class=\"clear text_center\" style=\"margin-bottom:10px;\"></div>");

	if (str.length())
	{
		//数据提取
		regex r("<td style=\"text-align:left;\">[\\s]*<a href=\"show-(.+).html\" target=\"_blank\">[\\s]*(.+)<span class=\"keyword\">(.+)</span>(.+)</a>");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;

		//生成结果
		for (; pos != end; ++pos)
		{
			string&& all = pos->str(0);
			string&& hash = pos->str(1);
			string&& name_front = pos->str(2);
			string&& keyword = pos->str(3);
			string&& name_back = pos->str(4);

			string name = name_front + keyword + name_back;

			//去除斜字体标识
			if (name.find("<em>") != name.npos)
			{
				name.replace(name.find("<em>"), 4, "");
				name.replace(name.find("</em>"), 5, "");
			}
			Result.push_back(Resource(name, "http://" + Url + "/show-" + hash + ".html", TorrentHeader + hash, SiteID));
		}
	}

	//检查下一页
	str = ToolBox::CutString(conn.GetResponseBody(), 
		"<div class=\"pages clear\">",
		"<div class=\"clear text_center\" style=\"margin-bottom:10px;\"></div>");

	regex e("<a href=\".+page=([0-9]+)\" class=\"nextprev\" target=\"_self\">〉");
	smatch m;
	bool found = regex_search(str, m, e);
	if (found)
	{
		int next_page = QString(m.str(1).c_str()).toInt();
		emit postFoundNextPage((int)SiteID, next_page);
	}
}

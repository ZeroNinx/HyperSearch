#include "ResSite/ConsoleRomSite/CoolRom.h"

void ConsoleRomSite::CoolRom::Search(QVector<Resource>& Result, QString KeyWord)
{
	//建立连接
	HttpsConn Coolrom("coolrom.com.au");
	Coolrom.Build("/search?q=" + KeyWord.toStdString());
	Coolrom.Request.set(field::user_agent, UA_CHROME);
	Coolrom.Connect();

	//数据处理
	string str = ToolBox::CutString(Coolrom.GetResponseBody(), "Filter results:", "</font>");
	if (str.size())
	{
		//匹配提取
		regex r("<a href=\"[^\"]+\">([^<]+)</a> &raquo <a href=\"([^\"]+)\">([^<]+)</a>");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;

		//生成结果
		for (; pos != end; ++pos)
		{
			string& all = pos->str(0);
			string& platform = pos->str(1);
			string& url = pos->str(2);
			string& name = pos->str(3);

			string fullname = "[" + platform + "] " + name;
			string pageUrl = "https://coolrom.com.au" + url;

			Result.push_back(Resource(fullname, pageUrl, "", "", (int)SiteID::ConsoleRomSite_CoolRom));
		}
	}
}

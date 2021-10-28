#include "ResSite/ConsoleRomSite/CoolRom.h"

std::vector<Resource>& ConsoleRomSite::CoolRom::Search(std::string KeyWord)
{
	//建立连接
	HttpsConn Coolrom("coolrom.com.au");
	Coolrom.Build("/search?q=" + KeyWord);
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

			string fullname = "[" + platform + "]" + name;
			string pageurl = "https://coolrom.com.au" + url;

			resource_list.push_back(Resource(fullname, pageurl));
		}
	}
	return resource_list;
}

#include "ResSite/ConsoleRomSite/EdgeEmu.h"

std::vector<Resource>& ConsoleRomSite::EdgeEmu::Search(std::string KeyWord)
{
	//建立连接
	HttpsConn Edgeemu("edgeemu.net");
	Edgeemu.Build("/results.php?q=" + KeyWord+"&system=all");
	Edgeemu.Request.set(field::user_agent, UA_CHROME);
	Edgeemu.Connect();

	//数据处理
	string str = Edgeemu.GetResponseBody();
	if (str.size())
	{
		//匹配提取
		regex r("<td><a href=\"([^\"]+)\">([^<]+)</a></td><td>([^>]+)</td>");
		sregex_iterator pos = sregex_iterator(str.cbegin(), str.cend(), r);
		sregex_iterator end;

		//生成结果
		for (; pos != end; ++pos)
		{
			const string& all = pos->str(0);
			const string& platform = pos->str(3);
			const string& url = pos->str(1);
			const string& name = pos->str(2);

			string display_platform = platform.substr(0, platform.length() - 5);
			string fullname = "[" + display_platform + "]" + name;
			string pageurl = "https://edgeemu.net/" + url;
			string downloadurl = "https://edgeemu.net/down.php?id=" + ToolBox::CutString(url, "details-", ".htm");

			resource_list.push_back(Resource(fullname, pageurl, "",downloadurl));
		}
	}
	return resource_list;
}

#include "ResSite/ConsoleRomSite/EdgeEmu.h"

ConsoleRomSite::EdgeEmu::EdgeEmu():ResSite("EdgeEmu","edgeemu.net", ResSiteType::ConsoleRomSite, ResSiteID::ConsoleRomSite_EdgeEmu)
{

}

void ConsoleRomSite::EdgeEmu::Search(QVector<Resource>& Result, QString& KeyWord)
{
	//建立连接
	HttpsConn Edgeemu(Url);
	Edgeemu.Build("/results.php?q=" + KeyWord.toStdString() + "&system=all");
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
			string fullname = "[" + display_platform + "] " + name;
			string pageurl = "https://edgeemu.net/" + url;
			string downloadurl = "https://edgeemu.net/down.php?id=" + ToolBox::CutString(url, "details-", ".htm");

			Result.push_back(Resource(fullname, pageurl, "", downloadurl, SiteID));
		}
	}
}

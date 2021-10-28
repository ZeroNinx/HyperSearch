#include "ResSite/TorrentSite/Btsow.h"

vector<Resource>& TorrentSite::BTSOW::Search(string KeyWord)
{
	//建立连接
	HttpsConn Btsow("btsow.rest");
	Btsow.Build("/search/" + KeyWord);
	Btsow.Request.set(field::user_agent, UA_CHROME);
	Btsow.Connect();

	//数据处理
	string str = ToolBox::CutString(Btsow.GetResponseBody(), "<div class=\"col-sm-8 col-lg-9 field\">Torrent Description</div>", "<div type=\"text/data-position\"");
	if (str.size())
	{
		qDebug() << str.c_str();
		regex r("<a href=\"//btsow.rest/magnet/detail/hash/([^\"]+)\".*title=\"([^\"]+)\">");
		sregex_iterator pos = sregex_iterator(str.begin(), str.end(), r);
		sregex_iterator end;
		for (; pos != end; ++pos)
		{
			string& all = pos->str(0);
			string& hash = pos->str(1);
			string& name = pos->str(2);

			resource_list.push_back(Resource(name, "https://btsow.rest/magnet/detail/hash/" + hash, "", "magnet:?xt=urn:btih:" + hash));
		}
	}
	return resource_list;
}

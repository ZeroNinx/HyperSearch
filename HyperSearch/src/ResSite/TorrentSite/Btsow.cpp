#include "ResSite/TorrentSite/BTSOW.h"

TorrentSite::BTSOW::BTSOW(): ResSite("BTSWO", "btsow.rest")
{

}

void TorrentSite::BTSOW::Search(QVector<Resource>& Result, QString KeyWord)
{
	//建立连接
	HttpsConn Btsow("btsow.rest");
	Btsow.Build("/search/" + KeyWord.toStdString());
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

			Result.push_back(Resource(name, "https://btsow.rest/magnet/detail/hash/" + hash, "", TorrentHeader + hash, (int)SiteID::TorrentSite_BTSOW));
		}
	}
}


#include <QDebug>
#include <regex>

#include "ResSite.h"
#include "HttpConn.h"


using namespace std;
using namespace boost::beast::http;

//资源
Resource::Resource(string InName, string InUrl):Name(InName),Url(InUrl)
{


}

//资源网站
ResSite::ResSite(std::string Name, std::string Url):name(Name), url(Url)
{

}

std::vector<Resource>& ResSite::Search(std::string KeyWord)
{
	return resource_list;
}

//BTSOW
std::vector<Resource>& TorrentSite_BTSOW::Search(std::string KeyWord)
{
	//建立连接
	HttpsConn Btsow("btsow.rest");
	Btsow.Build("/search/" + KeyWord);
	Btsow.Request.set(field::user_agent, UA_CHROME);
	Btsow.Connect();

	//数据处理
	string& str = Btsow.GetResponseBody();
	regex r("<a href=\"//btsow.rest/magnet/detail/hash/(.*)\".*title=\"(.*)\">");
	sregex_iterator pos = sregex_iterator(str.begin(), str.end(), r);
	sregex_iterator end;
	for (; pos != end; ++pos)
	{
		//qDebug() << "Matched: " << pos->str(0).c_str() << endl;
		//qDebug() << "user name: " << pos->str(1).c_str() << endl;
		//qDebug() << "domain: " << pos->str(2).c_str() << endl;

		resource_list.push_back(Resource(pos->str(2).c_str(), (string("magnet:?xt=urn:btih:") + pos->str(1)).c_str()));
	}
	
	return resource_list;
}

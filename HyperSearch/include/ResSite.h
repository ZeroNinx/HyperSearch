#pragma once

#include <string>
#include <vector>
#include <regex>
#include <QDebug>
#include "ToolBox.h"
#include "HttpConn.h"

using namespace std;
using namespace boost::beast::http;

#define UA_CHROME "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Safari/537.36"

//资源类
class Resource
{
public:

	Resource(std::string Text, std::string PageUrl = "", std::string DiskUrl = "", std::string DownloadUrl = "");

	std::string Text;
	std::string PageUrl;
	std::string DiskUrl;
	std::string DownloadUrl;

};

//资源网站类 
class ResSite
{
public:
	explicit ResSite() {};
	ResSite(std::string Name, std::string Url);

	std::vector<Resource>& SafeSearch(std::string KeyWord);
	virtual std::vector<Resource>& Search(std::string KeyWord);

protected:

	std::vector<Resource> resource_list;
	std::string name;
	std::string url;

};



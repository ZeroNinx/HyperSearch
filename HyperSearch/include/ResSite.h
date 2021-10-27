#pragma once
#include <string>
#include <vector>

#define UA_CHROME "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Safari/537.36"

//资源类
class Resource
{
public:

	Resource(std::string Name, std::string Url);

	std::string Name;
	std::string Url;

};

//资源网站类 
class ResSite
{
public:
	explicit ResSite() {};
	ResSite(std::string Name, std::string Url);

	virtual std::vector<Resource>& Search(std::string KeyWord);

protected:

	std::vector<Resource> resource_list;
	std::string name;
	std::string url;

};

//种子网站
class TorrentSite: public ResSite
{

};

//BTSOW
class TorrentSite_BTSOW:TorrentSite
{
public:
	virtual std::vector<Resource>& Search(std::string KeyWord) override;
};


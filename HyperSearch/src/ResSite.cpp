#include "ResSite.h"


//资源
Resource::Resource(std::string InText, std::string InPageUrl, std::string InDiskUrl, std::string InDownloadUrl)
{
	this->Text = InText;
	this->PageUrl = InPageUrl;
	this->DiskUrl = InDiskUrl;
	this->DownloadUrl = InDownloadUrl;
}

//资源网站
ResSite::ResSite(std::string Name, std::string Url):name(Name), url(Url)
{

}

std::vector<Resource>& ResSite::SafeSearch(std::string KeyWord)
{
	try
	{
		return Search(KeyWord);
	}
	catch (const std::exception& e)
	{
		qDebug() << e.what();
		return resource_list;
	}
}

std::vector<Resource>& ResSite::Search(std::string KeyWord)
{
	return resource_list;
}



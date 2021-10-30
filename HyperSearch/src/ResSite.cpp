#include "ResSite.h"

//资源
Resource::Resource(std::string InText, std::string InPageUrl, std::string InDiskUrl, std::string InDownloadUrl, int SiteID)
{
	this->Text = InText;
	this->PageUrl = InPageUrl;
	this->DiskUrl = InDiskUrl;
	this->DownloadUrl = InDownloadUrl;
	this->SiteID = SiteID;
}

//资源网站
ResSite::ResSite(std::string Name, std::string Url) :name(Name), url(Url)
{

}

void ResSite::Search(QVector<Resource>& Result, QString KeyWord)
{

}

void ResSite::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{

}


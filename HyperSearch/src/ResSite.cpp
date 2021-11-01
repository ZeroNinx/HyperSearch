#include "ResSite.h"

//资源
Resource::Resource(std::string InText, std::string InPageUrl, std::string InDiskUrl, std::string InDownloadUrl, ResSiteID InSiteID)
{
	this->Text = InText;
	this->PageUrl = InPageUrl;
	this->DiskUrl = InDiskUrl;
	this->DownloadUrl = InDownloadUrl;
	this->SiteID = InSiteID;
}

//资源网站
ResSite::ResSite(
	std::string InName,
	std::string InUrl,
	ResSiteType InSiteType,
	ResSiteID InSiteID) :

	Name(InName), 
	Url(InUrl), 
	SiteType(InSiteType), 
	SiteID(InSiteID)
{

}

void ResSite::Search(QVector<Resource>& Result, QString& KeyWord)
{

}

void ResSite::SearchPage(QVector<Resource>& Result, QString& KeyWord, int Page)
{

}


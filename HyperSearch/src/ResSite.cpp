#include "ResSite.h"

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



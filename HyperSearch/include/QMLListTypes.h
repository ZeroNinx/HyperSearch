#include "QMLList.h"

//网站类
class Host:public QMLListItem
{
public:
	explicit Host()
	{
		roleNames[NameRole] = "name";
		roleNames[TypeRole] = "type";
	}

	Host(QString Name, int Type): Host()
	{
		roleProperty[NameRole] = Name;
		roleProperty[TypeRole] = QString::fromLocal8Bit(std::to_string(Type).c_str());
	};

	enum HostRoles
	{
		NameRole = Qt::UserRole + 1,
		TypeRole
	};
};

class Result :public QMLListItem
{
public:
	explicit Result()
	{
		roleNames[TextRole] = "text";
		roleNames[UrlRole] = "url";
	}

	Result(QString Text, QString Url)
	{
		roleProperty[TextRole] = Text;
		roleProperty[UrlRole] = Url;
	}

	enum ResultRoles
	{
		TextRole = Qt::UserRole + 1,
		UrlRole
	};
};

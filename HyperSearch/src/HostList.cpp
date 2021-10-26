#include "HostList.h"

HostList::HostList(QObject* parent)
{
	
}

QVector<Host>& HostList::GetList()
{
	return List;
}

HostModel::HostModel(QObject* parent)
{
	hostList = new HostList();
}



int HostModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() || !hostList)
		return 0;

	return hostList->GetList().size();
}

QVariant HostModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || !hostList)
		return QVariant();

	const Host item = hostList->GetList().at(index.row());
	switch (role) 
	{
	case NameRole:
		return QVariant(item.Name);
	case UrlRole:
		return QVariant(item.Url);
	case TypeRole:
		return QVariant(item.Type);
	}

	return QVariant();
}

bool HostModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	if (!hostList)
		return false;

	Host item = hostList->GetList().at(index.row());
	switch (role) 
	{
	case NameRole:
		item.Name = value.toString();
		break;
	case UrlRole:
		item.Url = value.toString();
		break;
	case TypeRole:
		item.Type = value.toInt();
		break;
	}

	return true;
}

Qt::ItemFlags HostModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable;
}

QHash<int, QByteArray> HostModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[NameRole] = "name";
	roles[UrlRole] = "url";
	roles[TypeRole] = "type";
	return roles;
}


HostList* HostModel::GetHostList() const
{
	return this->hostList;
}

void HostModel::SetHostList(HostList* InList)
{
	hostList = InList;
}

HostModel::~HostModel()
{
	delete hostList;
}

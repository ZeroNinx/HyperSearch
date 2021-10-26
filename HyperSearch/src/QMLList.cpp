#include "QMLList.h"

/** 列表项 */
QHash<int, QByteArray> QMLListItem::GetRoleNames()
{
	return roleNames;
}


/** 列表对象 */
QMLListObject::QMLListObject(QObject* parent)
{
	
}

QHash<int, QByteArray> QMLListObject::GetRoleNames()
{
	return TemplateObject.GetRoleNames();
}

QVector<QMLListItem>& QMLListObject::GetList()
{
	return List;
}

void QMLListObject::SetTemplate(QMLListItem& InTemplateObject)
{
	TemplateObject = InTemplateObject;
}

/** 列表模型 */
QMLListModel::QMLListModel( QObject* parent)
{
	listObject = new QMLListObject();
}

int QMLListModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() || !listObject)
		return 0;

	return listObject->GetList().size();
}

QVariant QMLListModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || !listObject)
		return QVariant();

	const QMLListItem item = listObject->GetList().at(index.row());
	if (item.roleProperty.contains(role))
		return QVariant(item.roleProperty[role]);
	return QVariant();
}

bool QMLListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!listObject)
		return false;

	QMLListItem item = listObject->GetList().at(index.row());
	item.roleProperty[role] = value.toString();
	return true;
}

Qt::ItemFlags QMLListModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable;
}

QHash<int, QByteArray> QMLListModel::roleNames() const 
{
	return listObject->GetRoleNames();
}

QMLListObject* QMLListModel::GetListObject() const
{
	return this->listObject;
}

void QMLListModel::SetListObject(QMLListObject* InList)
{
	listObject = InList;
}

void QMLListModel::SetTemplate(QMLListItem Template)
{
	GetListObject()->SetTemplate(Template);
}

QMLListModel::~QMLListModel()
{
	delete listObject;
}


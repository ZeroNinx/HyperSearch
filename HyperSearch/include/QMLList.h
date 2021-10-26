#pragma once
#include <QObject>
#include <QVector>
#include <QHash>
#include <QAbstractListModel>

/** 列表项基类 */
class QMLListItem
{
public:
	
	/** 构造函数 */
	explicit QMLListItem() {};

	QHash<int, QByteArray> GetRoleNames();
	QHash<int, QString> roleProperty;

protected:
	QHash<int, QByteArray> roleNames;
};

/** 列表对象 */
class QMLListObject: public QObject
{
	Q_OBJECT

public:
	explicit QMLListObject(QObject* parent = nullptr);

	QHash<int, QByteArray> GetRoleNames();
	QVector<QMLListItem>& GetList();
	void SetTemplate(QMLListItem& TemplateObject);

private:
	QVector<QMLListItem> List;

	/** 缓存对象 */
	QMLListItem TemplateObject;
};

/** 列表模型 */
class QMLListModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(QMLListObject* list READ GetListObject WRITE SetListObject)

public:

	explicit QMLListModel( QObject* parent = nullptr);
	~QMLListModel();

	/** 原生操作 */
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QHash<int, QByteArray> roleNames() const override;

	/** list操作 */
	QMLListObject* GetListObject() const;
	void SetListObject(QMLListObject* InList);

	/** 自定义 */
	void SetTemplate(QMLListItem Template);
	void AddItem(QMLListItem Item)
	{
		beginInsertRows(QModelIndex(), listObject->GetList().size(), listObject->GetList().size());
		listObject->GetList().append(Item);
		endInsertRows();
	}

private:
	QMLListObject* listObject;

};
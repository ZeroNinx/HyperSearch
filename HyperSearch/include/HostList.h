#pragma once
#include <QObject>
#include <QVector>
#include <QAbstractListModel>

//网站类
struct Host
{
	QString Name;
	QString Url;
	int Type;
};

//网站列表
class HostList: public QObject
{
	Q_OBJECT

public:
	explicit HostList(QObject* parent = nullptr);

	QVector<Host>& GetList();

private:
	QVector<Host> List;
};

//网站模型
class HostModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(HostList* list READ GetHostList WRITE SetHostList)

public:

	explicit HostModel(QObject* parent = nullptr);
	~HostModel();

	enum HostRoles 
	{
		NameRole = Qt::UserRole + 1,
		UrlRole,
		TypeRole
	};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	virtual QHash<int, QByteArray> roleNames() const override;

	/** HostList */
	HostList* GetHostList() const;
	void SetHostList(HostList* InList);

	void AddItem(Host host)
	{
		beginInsertRows(QModelIndex(), hostList->GetList().size(), hostList->GetList().size());
		hostList->GetList().append(host);
		endInsertRows();
	}

private:
	HostList* hostList;

};
#pragma once
#include <QObject>

class SubscribeSite: public QObject
{
public:

	SubscribeSite();

signals:

	void postFoundResult(QString Result);

};



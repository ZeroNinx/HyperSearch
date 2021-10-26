#include "MainWindow.h"



MainWindow::MainWindow(QObject *parent)
{
	hostModel = new HostModel();
	hostModel->GetHostList()->GetList().append({ QStringLiteral("百度"), QStringLiteral("www.Baidu.com"), 0 });
	hostModel->GetHostList()->GetList().append({ QStringLiteral("谷歌"), QStringLiteral("www.Google.com"), 0 });
}


HostModel* MainWindow::GetHostModel()
{
	return hostModel;
}

void MainWindow::SetHostModel(HostModel* InModel)
{
	if(hostModel)
		hostModel->disconnect(this);

	hostModel = InModel;
}

QString MainWindow::openUrl()
{
	hostModel->AddItem({ QStringLiteral("百度"), QStringLiteral("www.Baidu.com"), 0 });
	return tr("ZZZZZZZZZZZZZZZ");
}

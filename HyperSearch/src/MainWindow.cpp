#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent)
{
	Text = tr("���Ƿǵ�ʧ");
}

QString MainWindow::GetText()
{
	return Text;
}

void MainWindow::SetText(const QString& InText)
{
	if (Text == InText)
		return;

	Text = InText;
	emit OnTextChanged();
}

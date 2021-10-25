#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent)
{
	Text = tr("的是非得失");
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

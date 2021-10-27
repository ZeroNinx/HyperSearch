#define _WIN32_WINDOWS
#include <QGuiApplication>
#include <QtQml/QtQml>

#include "QMLList.h"
#include "MainWindow.h"

//注册变量类型
void RegistType()
{
	qmlRegisterType<MainWindow>("HS", 1, 0, "HSMainWindow");
	qmlRegisterType<QMLListModel>("HS", 1, 0, "QMLListModel");
	qmlRegisterUncreatableType<QMLListObject>("HS", 1, 0, "QMLListObject", QStringLiteral("QMLListObject should not be created in QML"));
}

int main(int argc, char* argv[])
{
	RegistType();

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);


	MainWindow mainWindow;
	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty(QStringLiteral("mainWindow"), &mainWindow);
	engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

#include <MainWindow.h>
#include <HostList.h>

#include <QGuiApplication>
#include <QtQml/QtQml>

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	//注册变量类型
	qmlRegisterType<MainWindow>("HS", 1, 0, "HSMainWindow");
	qmlRegisterType<HostModel>("HS", 1, 0, "HostModel");
	qmlRegisterUncreatableType<HostList>("HS", 1, 0, "HostList", QStringLiteral("HostList should not be created in QML"));

	MainWindow mainWindow;

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty(QStringLiteral("mainWindow"), &mainWindow);
	engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

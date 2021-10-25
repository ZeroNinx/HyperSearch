#include <MainWindow.h>

#include <QGuiApplication>
#include <QtQml/QtQml>

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qmlRegisterType<MainWindow>("HyperSearch.MainWindow", 1, 0, "MainWindow");

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/MainWindow.qml"));
	QObject::connect(
		&engine, 
		&QQmlApplicationEngine::objectCreated,
		&app, 
		[url](QObject* obj, const QUrl& objUrl) 
		{
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

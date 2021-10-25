#pragma once
#include <QObject>
#include <QtQml/QtQml>

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Text READ GetText WRITE SetText NOTIFY OnTextChanged)

public:
    explicit MainWindow(QObject *parent = Q_NULLPTR);

    QString GetText();
    void SetText(const QString& InText);

signals:
    
    void OnTextChanged();

private:

    QString Text;
};

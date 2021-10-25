#include "HyperSearch.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HyperSearch w;
    w.show();
    return a.exec();
}

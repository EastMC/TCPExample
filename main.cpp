#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}

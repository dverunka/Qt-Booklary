#include "window.h"

#include <QApplication>
#include <qfile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Veronika Dzúriková");
    QCoreApplication::setOrganizationDomain("verunkachu.cz");
    QCoreApplication::setApplicationName("Booklary");

    QFile file(":/style.qss");
    if (file.open(QFile::Text | QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
    }

    Window w;
    w.show();

    return a.exec();
}

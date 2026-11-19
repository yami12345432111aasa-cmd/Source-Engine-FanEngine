#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Fan Engine");
    QApplication::setOrganizationName("Fan Engine");
    MainWindow window;
    window.show();
    return app.exec();
}

#include <QtGui/QApplication>
#include <QPushButton>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainWindow window;
    window.show();

    return app.exec();

}

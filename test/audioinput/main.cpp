#include <QtGui>

#include "inputtest.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Audio Input Test");

    InputTest input;
    input.show();

    return app.exec();
}

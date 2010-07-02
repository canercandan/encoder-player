#include <QApplication>

#include "MoviePlayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MoviePlayer player;
    player.show();
    return app.exec();
}

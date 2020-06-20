#include <QApplication>
#include "Juego.h"

Juego *Game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game= new Juego;
    Game->show();
    Game->MenuInicial();
    return a.exec();
}

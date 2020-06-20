#include "Juego.h"


Juego::Juego(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    Pantalla = new QGraphicsScene;
    Pantalla->setSceneRect(0,0,1024,768);

    setScene(Pantalla);
}

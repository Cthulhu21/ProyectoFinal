#include "Mapa.h"
#include "Enemigo.h"
#include "Juego.h"

extern Juego *Game;

Mapa::Mapa(int _ID, QImage *_Fondo)
{
    ID=_ID;
    FondoMapa=*_Fondo;
}

QList<QPair<QGraphicsPixmapItem *, QPoint> > Mapa::ConseguirObjetos()
{
    return Objetos;
}

QBrush Mapa::ConseguirFondo()
{
    return FondoMapa;
}

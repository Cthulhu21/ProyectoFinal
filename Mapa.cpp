#include "Mapa.h"
#include "Enemigo.h"
#include "Juego.h"

extern Juego *Game;


QList<QPair<QGraphicsPixmapItem *, QPoint> > Mapa::ConseguirObjetos()
{
    return Objetos;
}

Mapa::Mapa(int _ID, QImage *_Fondo, QGraphicsPixmapItem *_Estructura)
{
    ID=_ID;
    FondoMapa=*_Fondo;
    Estructura=_Estructura;
}

QBrush Mapa::ConseguirFondo()
{
    return FondoMapa;
}

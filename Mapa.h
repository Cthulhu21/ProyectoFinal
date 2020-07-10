#ifndef MAPA_H
#define MAPA_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QBrush>
#include <QGraphicsScene>

class Mapa: public QBrush
{
public:

    Mapa(int _ID=0, QImage *_Fondo= new QImage, QGraphicsPixmapItem *_Estructura= new QGraphicsPixmapItem );

    QBrush ConseguirFondo();
    QList<QPair<QGraphicsPixmapItem *, QPoint> > ConseguirObjetos();
    int ID;
    QBrush FondoMapa;
    QGraphicsPixmapItem *Estructura;

private:

    QList<QPair<QGraphicsPixmapItem *, QPoint>> Objetos;
};

#endif // MAPA_H

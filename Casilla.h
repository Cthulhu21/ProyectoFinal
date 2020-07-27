#ifndef CASILLA_H
#define CASILLA_H

#include <QGraphicsRectItem>
#include <QObject>

class Casilla:public QObject, public QGraphicsPixmapItem
{
public:
    Casilla(int X, int Y, int W, int H, int ID);
private:
    void Imagen(int _ID);
};

#endif // CASILLA_H

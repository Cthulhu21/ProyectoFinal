#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Objeto.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Inventario
{
public:
    Inventario();
    void AgregarObjeto(Objeto * _Item);
    void MostrarInventario();
    void CerrarInventario();
    void DibujarInventario(bool);
    bool On=false;

private:

    QMap<int, int> Objetos; //<ID,Cantidad>

    int Max_Stack=10;//Maxima cantidad de objetos y montones
    QGraphicsRectItem *Fondo;
    QGraphicsTextItem *Titulo;
    QGraphicsRectItem *Casilla;
    QList<QGraphicsItem*> Casillas;
};

#endif // INVENTARIO_H

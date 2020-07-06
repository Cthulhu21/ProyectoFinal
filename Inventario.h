#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Objeto.h"
#include <QList>
#include <QGraphicsPixmapItem>

class Inventario
{
public:
    Inventario();
    void AgregarObjeto(Objeto * _Item);
    void MostrarInventario();
    void CerrarInventario();
private:
    QMap<int, Objeto> Objetos;

    int Max_Stack=10;//Maxima cantidad de objetos y montones
};

#endif // INVENTARIO_H

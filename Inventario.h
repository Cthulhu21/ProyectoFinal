#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Objeto.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "Casilla.h"

class Inventario
{
public:
    Inventario();
    // Métodos
    void AgregarObjeto(Objeto * _Item);
    void MostrarInventario();
    void CerrarInventario();
    void DibujarInventario(bool);
    //Atributos
    bool On=false;

private:

    QMap<int, int> Objetos; //<ID,Cantidad>
    QList<Casilla*> Casillas;
    QList<QGraphicsTextItem*> Numeros;
    int Max_Stack=10;//Maxima cantidad de objetos y montones
    QGraphicsRectItem *Fondo;
    QGraphicsTextItem *Titulo;
};

#endif // INVENTARIO_H

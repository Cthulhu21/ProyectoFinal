#ifndef MAPA_H
#define MAPA_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QBrush>
#include <QGraphicsScene>
#include <ObjetoDinamico.h>
#include "Enemigo.h"

class Mapa: public QBrush
{
public:

    Mapa(int _ID=0);

    QBrush ConseguirFondo();
    int ID;
    QBrush FondoMapa;
    QGraphicsPixmapItem *Estructura;
    QList<ObjetoDinamico*> ObjetosDinamicos;
    QList<Enemigo*> Enemigos;
    QList<int> Circundantes;
    //QMap<int, int> *MapasCircuncidantes= new QMap<int, int>;

private:
    void CargarMapas();

    //QList<QPair<QGraphicsPixmapItem *, QPair<int,int>>> Objetos;
};

#endif // MAPA_H

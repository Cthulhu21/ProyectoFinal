#ifndef MAPA_H
#define MAPA_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QBrush>
#include <QGraphicsScene>
#include <ObjetoDinamico.h>
#include "Enemigo.h"
#include <QPair>
#include "NPC.h"

class Mapa: public QBrush
{
public:

    Mapa(int _ID=0);

    QBrush ConseguirFondo();
    int ID;
    QBrush FondoMapa;
    QGraphicsPixmapItem *Estructura;
    QList<QList<float>> NPCs; //ID, PosX, PosY
    QList<ObjetoDinamico*> ObjetosDinamicos;
    QList<int> Circundantes;
    QList<QList<float>> Enemigos; //ID, PosX, PosY

private:
    void CargarMapas();
};

#endif // MAPA_H

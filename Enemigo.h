#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QTimer>
#include "Objeto.h"

class Enemigo: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigo(int _ID, int PosX, int PosY, QGraphicsItem *parent=NULL);
    void Hurt(int _Hurt);
    void Pausar();
    void Despausar();

    int ID;

private:
    int Ataque;
    int Defensa;
    int Vida;

    int FrameMovimiento=0;

    Objeto *Drop;
    QList<QPixmap> Sprite;

    QTimer *Movimiento;
    QTimer *Estado;
    QTimer *MoverEnemigo;

    void CargarDatos();


public slots:
    void Mover();
    void Animar();
    void EstadoActual();
};

#endif // ENEMIGO_H

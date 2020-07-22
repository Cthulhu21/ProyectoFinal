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

    int Frame=0;

    float PosX;
    float PosY;
    float VelocidadX=0;
    float VelocidadY=0;
    float Angulo;
    float AceleracionX=0;
    float AceleracionY=0;
    float ResistenciaAire=0.06;
    float VectorVelocidad;
    float DeltaTiempo=0.01;
    float PosicionJugadorX;
    float PosicionJugadorY;

    Objeto *Drop;
    QList<QPixmap> Sprite;
    QList<QPixmap> SpriteAtaque;
    QList<QPixmap> AtaqueArriba;
    QList<QPixmap> AtaqueDerecha;
    QList<QPixmap> AtaqueAbajo;
    QList<QPixmap> AtaqueIzquierda;
    QList<QPixmap> MoverDerecha;
    QList<QPixmap> MoverIzquierda;
    QList<QPixmap> Proyectil;

    QTimer *Movimiento;
    QTimer *Estado;
    QTimer *MoverEnemigo;
    QTimer *TimerAtaque;

    void CargarDatos();

    bool Atacando=false;
    bool SeguimientoY=false;
    bool SeguimientoX=false;

public slots:
    void Mover();
    void Animar();
    void EstadoActual();
    void EjecutarAtaque();
};

#endif // ENEMIGO_H

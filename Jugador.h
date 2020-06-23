#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QList>

enum Tecla {Derecha, Izquierda, Arriba, Abajo, Espacio, NULA};

class Jugador: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    Jugador(int X, int Y, QGraphicsItem *parent=NULL);
    void keyPressEvent(QKeyEvent *event);

    void Velocidad(float _VelocidadX, float _VelocidadY, float _AceleracionX=0, float _AceleracionY=0);

private:

    QTimer *TimerMovimiento= new QTimer;
    QTimer *TimerAtaque = new QTimer;
    QTimer *Animacion = new QTimer;
    QTimer *Delta = new QTimer;
    void Ataque();
    void Mover();
    QList<QPixmap> SpriteAtaque();
    void MoverDerecha();
    void MoverIzquierda();
    void MoverAbajo();
    void Estatica();
    QList<QPixmap> CargarMovimiento();

    //Atributos

    float PosX;
    float PosY;
    float VelocidadX;
    float VelocidadY;
    float Angulo;
    float AceleracionX;
    float AceleracionY;
    float ResistenciaAire;
    float VectorVelocidad;
    float DeltaTiempo;

    //Varios usos


    //Mover el frame

    int FrameMovimiento=0;
    int FrameAtaque=0;

    //Verificar si ataca o si está estatico
    bool Moviendose=false;
    bool Estatico=true;
    bool Atacando=false;
    bool FixAtaque=false;


    Tecla TeclaPresionada(QKeyEvent *event);
    Tecla Direccion=Abajo;
    Tecla _Direccion=Abajo;

    QList<QPixmap> ListaMovimiento;


public slots:

    void EjecutarMovimientos();
    void EjecutarAtaque();
    void Actualizar();
    void Movimiento();
};

#endif // JUGADOR_H

#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <Boton.h>
#include <Juego.h>
#include "Inventario.h"
#include "ObjetoDinamico.h"

//Una enumeracion de diferentes posibles teclas presionadas.
//Será útil para cambios de sprites de movimiento con switch
enum Tecla {Derecha, Izquierda, Arriba, Abajo,
            D_Derecha, A_Izquierda, W_Arriba, S_Abajo, Espacio,
            Esc, I,
            NULA};

//Enumerar primer o segundo jugador
enum NumeroJugador {Primero, Segundo};

class Jugador: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //Constructor
    Jugador(NumeroJugador _Jugador, int X, int Y, QGraphicsItem *parent=NULL);

    void CargarSprites();
    void Pausar();
    void Despausar();
    bool GetAtacando();
    void Hurt(int _Hurt);
    void AgregarAInventario(Objeto * _Objeto);

    void keyPressEvent(QKeyEvent *event);

    //Funcion para agregar velocidad y aceleracion a el objeto(Jugador)
    void Velocidad(float _VelocidadX, float _VelocidadY, float _AceleracionX=0, float _AceleracionY=0);

    //Atributos publicos
    int AtaqueJugador=10;
    int Defensa=10;
    int Vida=10;

    bool Chocando=false;

    Tecla Direccion=Abajo;

    Inventario InventarioJugadores;

private:

    //Timers para : Mover al jugador, ejecutar el ataque, etc

    QTimer *TimerMovimiento= new QTimer;
    QTimer *TimerAtaque = new QTimer;
    QTimer *Animacion = new QTimer;
    QTimer *Delta = new QTimer;

    //Metodos
    void Ataque();
    void Mover();
    void Colisiones();
    void Reposicionar();


    //Metodo que retorna una lista de QPixmap que dependerá
    //de la dirección del objeto
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

    Tecla _Direccion=Abajo;

    // Primer o segundo jugador

    NumeroJugador Numero;

    //Varios usos


    //Mover el frame

    int FrameMovimiento=0;
    int FrameAtaque=0;

    //Verificar si ataca, si está estatico o moviendose
    bool Moviendose=false;
    bool Estatico=true;
    bool Atacando=false;
    bool FixAtaque=false;
    bool AtaqueEfectivo=false;


    Tecla TeclaPresionada(QKeyEvent *event);

    QList<QPixmap> ParadoDerecha;
    QList<QPixmap> ParadoIzquierda;
    QList<QPixmap> ParadoArriba;
    QList<QPixmap> ParadoAbajo;
    QList<QPixmap> CorrerDerecha;
    QList<QPixmap> CorrerIzquierda;
    QList<QPixmap> CorrerArriba;
    QList<QPixmap> CorrerAbajo;
    QList<QPixmap> AtacarDerecha;
    QList<QPixmap> AtacarIzquierda;
    QList<QPixmap> AtacarArriba;
    QList<QPixmap> AtacarAbajo;


public slots:

    void EjecutarMovimientos();
    void EjecutarAtaque();
    void Actualizar();
    void Movimiento();
};

#endif // JUGADOR_H

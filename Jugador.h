#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QList>

enum Tecla {Derecha, Izquierda, Arriba, Abajo, Espacio};

class Jugador: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    Jugador(int X, int Y, QGraphicsItem *parent=NULL);
    void keyPressEvent(QKeyEvent *event);

    void Velocidad(float _VelocidadX, float VelocidadY);

private:

    QTimer *TimerAnimacion;
    void Ataque();
    void Mover(Tecla Direccion);
    QList<QPixmap> SpriteAtaque();
    void MoverDerecha();
    void MoverIzquierda();
    void MoverAbajo();
    void Estatica(Tecla _Direccion);

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

public slots:

    void Animar();
    void Actualizar();
    void Movimiento();
};

#endif // JUGADOR_H

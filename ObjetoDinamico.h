#ifndef OBJETODINAMICO_H
#define OBJETODINAMICO_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRect>


class ObjetoDinamico: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ObjetoDinamico(float _PosX, float _PosY, int ID);
    void Pausar();
    void Despausar();
private:
    //Metodos

    void DarVelocidad(float X=0, float Y=0);
    void Colisiones();
    void ColisionJugador();

    //Atributos
    float PosX;
    float PosY;
    float VelocidadX=0;
    float VelocidadY=0;
    float Angulo;
    float AceleracionX=0;
    float AceleracionY=0;
    float ResistenciaAire=0.08;
    float VectorVelocidad;
    float DeltaTiempo=0.01;
    QTimer *TimerActualizar;

    bool Chocando=false;

public slots:
    void Actualizar();
};

#endif // OBJETODINAMICO_H

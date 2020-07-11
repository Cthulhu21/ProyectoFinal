#include "ObjetoDinamico.h"
#include <math.h>
#include "Juego.h"
#include "Jugador.h"
#include "NPC.h"

extern Juego *Game;
extern Jugador *Jugador1;

ObjetoDinamico::ObjetoDinamico(float _PosX, float _PosY, int ID)
{
    setPixmap(QPixmap(":/Objeto/"+QString(QString::fromStdString(std::to_string(ID)))));

    PosX=_PosX;
    PosY=_PosY;

    TimerActualizar= new QTimer;
    connect(TimerActualizar, SIGNAL(timeout()),this, SLOT(Actualizar()));
    TimerActualizar->start(1);
}

void ObjetoDinamico::Pausar()
{
    TimerActualizar->stop();
    setOpacity(0.5);
}

void ObjetoDinamico::Despausar()
{
    TimerActualizar->start(1);
    setOpacity(1);
}

void ObjetoDinamico::DarVelocidad(float X, float Y)
{
    VelocidadX+=X;
    VelocidadY+=Y;
}

void ObjetoDinamico::Actualizar()
{
    ColisionJugador();
    Colisiones();
    VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
    Angulo = atan2(VelocidadY,VelocidadX);

    AceleracionX = -(ResistenciaAire*pow(VectorVelocidad,2))*cos(Angulo);
    AceleracionY = -(ResistenciaAire*pow(VectorVelocidad,2))*sin(Angulo);

    PosX += VelocidadX*DeltaTiempo + ((AceleracionX*pow(DeltaTiempo,2))/2);
    PosY += VelocidadY*DeltaTiempo + ((AceleracionY*pow(DeltaTiempo,2))/2);

    VelocidadX += AceleracionX*DeltaTiempo;
    VelocidadY += AceleracionY*DeltaTiempo;

    // Se verifica que no se salga del mapa; si lo hace, se toma como choque -> Velocidad 0

    PosX=(PosX<0)? 0: PosX;
    PosY=(PosY<0)? 0: PosY;

    VelocidadX=(abs(VelocidadX)<1)? 0: VelocidadX;
    VelocidadY=(abs(VelocidadY)<1)? 0: VelocidadY;

    setPos(PosX, PosY);
}

void ObjetoDinamico::Colisiones()
{
    QList<QGraphicsItem*> Elementos=collidingItems();
    if(Elementos.size()!=0 and !Jugador1->GetAtacando())
    //for(auto Elemento: Elementos)
    {
      //  if(typeid (*Elemento)==typeid (NPC))
        {
            switch (Jugador1->Direccion)
            {
            case Derecha:
                DarVelocidad(-10);
                break;
            case Izquierda:
                DarVelocidad(10);
                break;
            case Arriba:
                DarVelocidad(0,10);
                break;
            case Abajo:
                DarVelocidad(0,-10);
                break;
            default:
                break;
            }
        }
    }
}

void ObjetoDinamico::ColisionJugador()
{
    if(Jugador1->Chocando)
    {
        switch (Jugador1->Direccion)
        {
        case Derecha:
            VelocidadX+=100;
            break;
        case Izquierda:
            VelocidadX-=100;
            break;
        case Arriba:
            VelocidadY-=100;
            break;
        case Abajo:
            VelocidadY+=100;
            break;
        default:
            break;
        }
    }
}
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

void ObjetoDinamico::DarAceleracion(float X, float Y)
{
    AceleracionX+=X;
    AceleracionY+=Y;
}

void ObjetoDinamico::Actualizar()
{
    float _X=PosX, _Y=PosY;
    VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
    Angulo = atan2(VelocidadY,VelocidadX);

    PosX = PosX + VelocidadX*DeltaTiempo + ((AceleracionX*pow(DeltaTiempo,2))/2);
    PosY = PosY + VelocidadY*DeltaTiempo + ((AceleracionY*pow(DeltaTiempo,2))/2);

    VelocidadX = VelocidadX + AceleracionX*DeltaTiempo;
    VelocidadY = VelocidadY + AceleracionY*DeltaTiempo;

    AceleracionX = (ResistenciaAire*pow(VectorVelocidad,2))*-cos(Angulo);
    AceleracionY = (ResistenciaAire*pow(VectorVelocidad,2))*-sin(Angulo);


    // Se verifica que no se salga del mapa; si lo hace, se toma como choque -> Velocidad 0

    PosX=(PosX<0)? 0: PosX;
    PosY=(PosY<0)? 0: PosY;

    VelocidadX=(VelocidadX<5)? 0: VelocidadX;
    VelocidadY=(VelocidadY<5)? 0: VelocidadY;

    Colisiones();
    setPos(PosX, PosY);
}

void ObjetoDinamico::Colisiones()
{
    QList<QGraphicsItem*> Elementos=collidingItems();
    for(auto Elemento: Elementos)
    {
        if(typeid (*Elemento)==typeid (NPC))
        {
            VelocidadX=0;
            VelocidadY=0;
        }
        else if(typeid (*Elemento)==typeid (Jugador))
        {
            switch (Jugador1->Direccion)
            {
            case Derecha:
                DarAceleracion(1000);
                break;
            case Izquierda:
                DarAceleracion(-1000);
                break;
            case Arriba:
                DarAceleracion(0,-1000);
                break;
            case Abajo:
                DarAceleracion(0,1000);
                break;
            default:
                break;
            }
        }

    }
}

#include "Enemigo.h"
#include "Juego.h"
#include <QTimer>
#include "Jugador.h"
#include <math.h>

extern Juego *Game;
extern Jugador *Jugador1;

Enemigo::Enemigo(int _ID, int _PosX, int _PosY, QGraphicsItem *parent)
{
    srand(time(NULL));
    ID=_ID;
    CargarDatos();
    PosX=_PosX;
    PosY=_PosY;

    Drop = new Objeto(ID);

    Movimiento = new QTimer;
    Estado = new QTimer;
    MoverEnemigo = new QTimer;

    connect(Movimiento, SIGNAL(timeout()), this, SLOT(Animar()));
    connect(Estado, SIGNAL(timeout()), this, SLOT(EstadoActual()));
    connect(MoverEnemigo, SIGNAL(timeout()),this,SLOT(Mover()));

    MoverEnemigo->start(60);
    Movimiento->start(200);
    Estado->start(1);
}

void Enemigo::Hurt(int _Hurt)
{
    Vida-=_Hurt-Defensa;
}

void Enemigo::Pausar()
{
    setOpacity(0.5);
    Movimiento->stop();
    Estado->stop();
    MoverEnemigo->stop();
}

void Enemigo::Despausar()
{
    setOpacity(1);
    Movimiento->start(200);
    MoverEnemigo->start(60);
    Estado->start(1);
}

void Enemigo::CargarDatos()
{
    std::string _DireccionArchivo=":/Enemigos/";
    switch (ID)
    {
    case 1:
    {
        auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID))));
        for(int i=0; i<4; i++)
        {
            Sprite.push_back(Tempo.copy(2+(i*17),19,17,16).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
        }
        Vida=10;
        Ataque=10;
        Defensa=0;
        break;
    }
    case 2:
    {
        auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID))));
        for(int i=0; i<3; i++)
        {
            Sprite.push_back(Tempo.copy(29+(i*17),43,17,24).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            MoverDerecha.push_back(Tempo.copy(25+(i*17),69,17,24).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            AtaqueArriba.push_back(Tempo.copy(45,97,16,22).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
        }
        Vida=20;
        Ataque=12;
        Defensa=5;
        break;
    }
    case 3:
    {
        auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID))));
        for(int i=0; i<3; i++)
        {
            Proyectil.push_back(Tempo.copy(11+(i*10),9,10,11).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            Sprite.push_back(Tempo.copy(11+(i*17),26,17,24).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
        }
        Vida=80;
        Ataque=20;
        Defensa=10;
        break;
    }
    case 4:
    {
        auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID))));
        for(int i=0; i<11; i++)
        {
            Sprite.push_back(Tempo.copy(203+(i*17),761,17,21).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            if(i<7)
                AtaqueDerecha.push_back(Tempo.copy(6+(i*18),903,18,25).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio)); //Saltar
            AtaqueAbajo.push_back(Tempo.copy(170+(i*20),800,20,33).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
        }
        Vida=60;
        Ataque=35;
        Defensa=10;
        break;
    }
    case 5:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=80;
        Ataque=20;
        Defensa=30;
        break;
    }
    case 6:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=200;
        Ataque=50;
        Defensa=5;
        break;
    }
    case 7:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=150;
        Ataque=10;
        Defensa=40;
        break;
    }
    case 8:
    {
        _DireccionArchivo=":/Enemigos/";
        for(int i=0;i<4;i++)
        {
            auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID))));
            Sprite.push_back(Tempo.copy(57+(i*31),112,31,38).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            AtaqueArriba.push_back(Tempo.copy(67+(i*30),175,30,44).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            AtaqueIzquierda.push_back(Tempo.copy((i*59),224,59,32).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            AtaqueDerecha.push_back(Tempo.copy(29+(59*i),264,59,32).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
            AtaqueAbajo.push_back(Tempo.copy(70+(32*i),302,32,40).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
        }
        Vida=50;
        Ataque=60;
        Defensa=0;
        break;
    }
    case 9:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=200;
        Ataque=50;
        Defensa=40;
        break;
    }
    case 10:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=90;
        Ataque=70;
        Defensa=20;
        break;
    }
    case 11:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=150;
        Ataque=50;
        Defensa=80;
        break;
    }
    case 12:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=300;
        Ataque=40;
        Defensa=30;
        break;
    }
    case 13:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=180;
        Ataque=70;
        Defensa=30;
        break;
    }
    case 14:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=30;
        Ataque=70;
        Defensa=40;
        break;
    }
    default:
        break;
    }
}

void Enemigo::Mover()
{
    //Busca la posicion del jugador y lo persigue


    switch (ID)
    {
    case 8:
    {
        float JugadorPosX=Jugador1->x()+50, JugadorPosY=Jugador1->y()+30;
        if(!Atacando)
        {
            if(abs(JugadorPosX-x())<50)
            {
                PosicionJugadorY=JugadorPosY;
                SeguimientoY=true;
                TimerAtaque = new QTimer;
                Atacando=true;
                Movimiento->stop();
                TimerAtaque->start(100);
                connect(TimerAtaque, SIGNAL(timeout()),this, SLOT(EjecutarAtaque()));
            }
            if(abs(JugadorPosY-y())<20)
            {
                PosicionJugadorX=JugadorPosX;
                SeguimientoX=true;
                TimerAtaque = new QTimer;
                Atacando=true;
                Movimiento->stop();
                TimerAtaque->start(100);
                connect(TimerAtaque, SIGNAL(timeout()),this, SLOT(EjecutarAtaque()));
            }
        }
    }
        break;
    default:
        break;
    }
}

void Enemigo::Animar()
{
    if(Game->JuegoActivo)
    {
        if(Frame>=Sprite.size())
        {
            Frame=0;
        }
        else
        {
            setPixmap(Sprite[Frame++]);
        }
    }
}

void Enemigo::EstadoActual()
{
    //Revisa las colisiones del objeto y hará daño o se hará
    //daño de acuerdo al estado del jugador
    // Se actualizan los datos de posicion y velocidad
    VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
    Angulo = atan2(VelocidadY,VelocidadX);

    PosX = PosX + VelocidadX*DeltaTiempo + ((AceleracionX*pow(DeltaTiempo,2))/2);
    PosY = PosY + VelocidadY*DeltaTiempo + ((AceleracionY*pow(DeltaTiempo,2))/2);

    VelocidadX = VelocidadX + AceleracionX*DeltaTiempo;
    VelocidadY = VelocidadY + AceleracionY*DeltaTiempo;

    AceleracionX = (ResistenciaAire*pow(VectorVelocidad,2))*-cos(Angulo);
    AceleracionY = (ResistenciaAire*pow(VectorVelocidad,2))*-sin(Angulo);

    // Determina velocidad mínima
    {
        float VelocidadMinima=5;
        if(abs(VelocidadX)<VelocidadMinima)
        {
            VelocidadX=0;
        }
        if(abs(VelocidadY)<VelocidadMinima)
        {
            VelocidadY=0;
        }
    }
    setPos(PosX, PosY);
    QList<QGraphicsItem *> Colisiones=collidingItems();
    for(auto Item: Colisiones)
    {
        if(typeid(*Item)==typeid (Jugador))
        {
            if(Jugador1->GetAtacando())
            {
                Hurt(Jugador1->AtaqueJugador*pow(2,Jugador1->TierAtaque));
            }
            else
            {
                Jugador1->Hurt(Ataque);
            }
        }
    }
    if(Vida<=0)
    {
        int i=(rand()%3)+1;
        if(i==3)
        {
            Drop->PosX=((x()+Sprite[Frame].width())/2)+300;
            Drop->PosY=((y()+Sprite[Frame].height())/2)-20;
            Game->AgregarDrop(Drop);
            Game->DropSuelo.push_back(Drop);
        }
        Game->Pantalla->removeItem(this);
        auto ItThis=Game->EnemigosActuales.begin();
        for(auto _Enemigo: Game->EnemigosActuales)
        {
            if(_Enemigo==this)
            {
                Game->EnemigosActuales.erase(ItThis);
                break;
            }
            ItThis++;
        }
        delete this;
    }
}

void Enemigo::EjecutarAtaque()
{
    switch (ID)
    {
    case 2:
    {
        setPixmap(QPixmap(":/Enemigos/2").copy(45,97,16,22));
    }
        break;
    case 8:
    {
        if(SeguimientoY)
        {
            if(abs(y()-PosicionJugadorY)<30)
            {
                Atacando=false;
                SeguimientoY=false;
                Movimiento->start(200);
                TimerAtaque->stop();
            }
            else
            {
                if(y()>PosicionJugadorY)
                {
                    VelocidadY-=100;
                    SpriteAtaque=AtaqueArriba;
                }
                else
                {
                    SpriteAtaque=AtaqueAbajo;
                    VelocidadY+=100;
                }
                if(Frame>=SpriteAtaque.size())
                {
                    Frame=0;
                }
                else
                {
                    setPixmap(SpriteAtaque[Frame++]);
                }
            }
        }
        else if(SeguimientoX)
        {
            if(abs(x()-PosicionJugadorX)<30)
            {
                Atacando=false;
                SeguimientoX=false;
                Movimiento->start(200);
                TimerAtaque->stop();
            }
            else
            {
                if(x()>PosicionJugadorX)
                {
                    VelocidadX-=100;
                    SpriteAtaque=AtaqueIzquierda;
                }
                else
                {
                    SpriteAtaque=AtaqueDerecha;
                    VelocidadX+=100;
                }
                if(Frame>=SpriteAtaque.size())
                {
                    Frame=0;
                }
                else
                {
                    setPixmap(SpriteAtaque[Frame++]);
                }
            }
        }

    }
        break;
    }

}


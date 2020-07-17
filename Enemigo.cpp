#include "Enemigo.h"
#include "Juego.h"
#include <QTimer>
#include "Jugador.h"

extern Juego *Game;
extern Jugador *Jugador1;

Enemigo::Enemigo(int _ID, int PosX, int PosY, QGraphicsItem *parent)
{
    ID=_ID;
    CargarDatos();
    setPos(PosX, PosY);

    Drop = new Objeto(1);

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
    //MoverEnemigo->stop();
}

void Enemigo::Despausar()
{
    setOpacity(1);
    Movimiento->start(60);
    //MoverEnemigo->start(80);
    Estado->start(1);
}

void Enemigo::CargarDatos()
{
    std::string _DireccionArchivo;
    switch (ID)
    {
    case 1:
    {
        for(int i=1; i<11; i++)
        {
            _DireccionArchivo=":/Enemigos/Slime_Par";
            Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(i)))));
        }
        Vida=10;
        Ataque=10;
        Defensa=0;
        //Drop = new Objeto(1);
        break;
    }
    case 2:
    {
        _DireccionArchivo=":/Enemigos/"+std::to_string(ID);
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo))).copy(0,0,25,50));
        Vida=20;
        Ataque=12;
        Defensa=5;
        break;
    }
    case 3:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
        Vida=100;
        Ataque=20;
        Defensa=10;
        break;
    }
    case 4:
    {
        _DireccionArchivo=":/Enemigos/";
        Sprite.push_back(QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(0,0,50,50));
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
            int a=57+(i*31);
            auto Tempo=QPixmap(QString(QString::fromStdString(_DireccionArchivo+std::to_string(ID)))).copy(a,112,31,38).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio);
            Sprite.push_back(Tempo);
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
    float JugadorPosX=Jugador1->x()+50, JugadorPosY=Jugador1->y()+30;

    // Derecha Abajo
    if(JugadorPosX > x() and JugadorPosY > y())
    {
        setPos(x()+5, y()+5);
    }
    //Izquierda Abajo
    else if(JugadorPosX < x() and JugadorPosY > y())
    {
        setPos(x()-5, y()+5);
    }
    //Derecha Arriba
    else if(JugadorPosX > x() and JugadorPosY < y())
    {
        setPos(x() + 5, y() - 5);
    }
    //Izquierda Arriba
    else if(JugadorPosX < x() and JugadorPosY < y())
    {
        setPos(x() - 5, y() - 5);
    }
    //Derecha
    else if(JugadorPosX-100 > x())
    {
        setX(x() + 5);
    }
    //Izquierda
    else if(JugadorPosX+100 < x())
    {
        setX(x() - 5);
    }
    //Arriba
    else if(JugadorPosY-100 < y())
    {
        setY(y() - 5);
    }
    //Abajo
    else if(JugadorPosY+100 > y())
    {
        setY(y() + 5);
    }
}

void Enemigo::Animar()
{
    if(Game->JuegoActivo)
    {
        if(FrameMovimiento>=Sprite.size())
        {
            FrameMovimiento=0;
        }
        else
        {
            setPixmap(Sprite[FrameMovimiento++]);
        }
    }
}

void Enemigo::EstadoActual()
{
    //Revisa las colisiones del objeto y hará daño o se hará
    //daño de acuerdo al estado del jugador
    QList<QGraphicsItem *> Colisiones=collidingItems();
    for(auto Item: Colisiones)
    {
        if(typeid(*Item)==typeid (Jugador))
        {
            if(Jugador1->GetAtacando())
            {
                Hurt(Jugador1->AtaqueJugador);
            }
            else
            {
                Jugador1->Hurt(Ataque);
            }
        }
    }
    if(Vida<=0)
    {
        srand(time(NULL));
        //if((rand()%3)+1==3)
        {
            Drop->PosX=((x()+Sprite[FrameMovimiento].width())/2)+300;
            Drop->PosY=((y()+Sprite[FrameMovimiento].height())/2)-20;
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


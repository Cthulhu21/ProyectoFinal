#include "Enemigo.h"
#include "Juego.h"
#include <QTimer>
#include "Jugador.h"
#include <QMovie>
#include <QLabel>

extern Juego *Game;
extern Jugador *Jugador1;

QList<QPixmap> Slime;

int FrameMovimiento=0;

Enemigo::Enemigo(int PosX, int PosY, QGraphicsItem *parent)
{
    setPos(PosX, PosY);
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/Enemigos/Slime_Par";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        Slime.push_back(QPixmap(DireccionArchivo));
    }
    Vida=10;
    Ataque=10;
    Defensa=0;
    Movimiento = new QTimer;
    Estado = new QTimer;
    MoverEnemigo = new QTimer;

    Drop = new Objeto(1);

    connect(Movimiento, SIGNAL(timeout()), this, SLOT(Animar()));
    connect(Estado, SIGNAL(timeout()), this, SLOT(EstadoActual()));
    //connect(MoverEnemigo, SIGNAL(timeout()),this,SLOT(Mover()));

    //MoverEnemigo->start(60);
    Movimiento->start(80);
    Estado->start(1);

    Game->Pantalla->addItem(this);
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
    Movimiento->start(60);
    MoverEnemigo->start(80);
    Estado->start(1);

}


void Enemigo::Mover()
{
    //Busca la posicion del jugador y lo persigue
    float JugadorPosX=Jugador1->x(), JugadorPosY=Jugador1->y();

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
        if(FrameMovimiento>=Slime.size())
        {
            FrameMovimiento=0;
        }
        else
        {
            setPixmap(Slime[FrameMovimiento++]);
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
            //Drop->PosX=(x()+Slime[FrameMovimiento].width())/2;
            //Drop->PosY=(y()+Slime[FrameMovimiento].height())/2;
            Drop->PosX=1000;
            Drop->PosY=500;
            Objeto *A= new Objeto(2);
            A->PosX=500;
            A->PosY=500;
            Game->AgregarDrop(A);
            Game->AgregarDrop(Drop);
            Game->DropSuelo.push_back(Drop);
        }
        Game->Pantalla->removeItem(this);
        auto Comiezo=Game->EnemigosActuales.begin();
        for(auto Enemy: Game->EnemigosActuales)
        {
            if(Enemy==this)
            {
                Game->EnemigosActuales.erase(Comiezo);
            }
            Comiezo++;
        }
        delete this;
    }
}


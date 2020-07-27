#include "NPC.h"
#include "Jugador.h"
#include <math.h>
#include <QTimer>
#include <QGraphicsTextItem>

extern Jugador *Jugador1;
extern Juego *Game;

NPC::NPC(int _ID, int _X, int _Y)
{
    ID=_ID;
    CargarImagen();
    setPos(_X, _Y);

    {
    AumentosV={"10 Almas de Araña","10 Almas de Bomb", "10 Almas de Slime", "10 Almas de Jabali", "No tenemos mas mejoras"};
    AumentosA={"10 Almas de Escupidor","10 Almas de RompeTierra","10 Almas de Tortuga","10 Almas de Zorro","No tenemos mas mejoras"};
    AumentosD={"10 Almas de Araña","10 Almas de Escupidor","10 Almas de Octorock","10 Almas de Saltador","No tenemos mas mejoras"};
    }
    QTimer *Busqueda= new QTimer;
    connect(Busqueda,SIGNAL(timeout()),this, SLOT(Hablar()));
    Busqueda->start(1);

    Estatico=false;
}

void NPC::CargarImagen()
{
    setPixmap(QPixmap(":/NPCs/1"));
}

void NPC::Pausar()
{
    setOpacity(0.5);
}

void NPC::Despausar()
{
    setOpacity(1);
}

void NPC::Hablar()
{
    /*1248;
    35910;
    1367;*/
    float A=(Jugador1->x()+64)-(x()+32);
    float B=(Jugador1->y()+64)-(y()+32);
    //Mostrar el texto
    if(sqrt(pow(A,2)+pow(B,2))<75 and !TextoEnPantalla)
    {
        switch (ID)
        {
        case 1:
            Texto= new QGraphicsTextItem(AumentosV[Jugador1->TierVida-1]);
            Texto->setFont(QFont("Times",10));
            Texto->setPos(x()-30,y()-20);
            Game->Pantalla->addItem(Texto);
            TextoEnPantalla=true;
            break;
        case 2:
            Texto= new QGraphicsTextItem(AumentosA[Jugador1->TierAtaque-1]);
            Texto->setFont(QFont("Times",10));
            Texto->setPos(x()-30,y()-20);
            Game->Pantalla->addItem(Texto);
            TextoEnPantalla=true;
            break;
        case 3:
            Texto= new QGraphicsTextItem(AumentosD[Jugador1->TierDefensa-1]);
            Texto->setFont(QFont("Times",10));
            Texto->setPos(x()-30,y()-20);
            Game->Pantalla->addItem(Texto);
            TextoEnPantalla=true;
            break;
        }
    }
    //Cerrar el texto
    else if(sqrt(pow(A,2)+pow(B,2))>75 and TextoEnPantalla)
    {
        Game->Pantalla->removeItem(Texto);
        delete Texto;
        TextoEnPantalla=false;
    }
    //Pedir los materiales
    else if(TextoEnPantalla)
    {
        if(Jugador1->Presionada==Z)
        {
            auto Inventario=Jugador1->InventarioJugadores.Objetos;
            switch (ID)
            {
            case 1:
            {
                switch (Jugador1->TierVida)
                {
                    case 1:
                    {
                        auto Pos=Inventario.find(1);
                        if(Pos!=Inventario.end())
                        {
                            if(Pos.value()>=10)
                            {
                                Jugador1->TierVida++;
                                Pos.value()-=10;
                                if(Pos.value()==0)
                                {
                                    Inventario.erase(Pos);
                                }
                                Jugador1->InventarioJugadores.Objetos=Inventario;
                            }
                        }
                    }
                        break;
                    case 2:
                    {
                        auto Pos=Inventario.find(2);
                        if(Pos!=Inventario.end())
                        {
                            if(Pos.value()>=10)
                            {
                                Jugador1->TierVida++;
                                Pos.value()-=10;
                                if(Pos.value()==0)
                                {
                                    Inventario.erase(Pos);
                                }
                                Jugador1->InventarioJugadores.Objetos=Inventario;
                            }
                        }
                    }
                        break;
                    case 3:
                    {
                        auto Pos=Inventario.find(4);
                        if(Pos!=Inventario.end())
                        {
                            if(Pos.value()>=10)
                            {
                                Jugador1->TierVida++;
                                Pos.value()-=10;
                                if(Pos.value()==0)
                                {
                                    Inventario.erase(Pos);
                                }
                                Jugador1->InventarioJugadores.Objetos=Inventario;
                            }
                        }
                    }
                        break;
                    case 4:
                    {
                        auto Pos=Inventario.find(8);
                        if(Pos!=Inventario.end())
                        {
                            if(Pos.value()>=10)
                            {
                                Jugador1->TierVida++;
                                Pos.value()-=10;
                                if(Pos.value()==0)
                                {
                                    Inventario.erase(Pos);
                                }
                                Jugador1->InventarioJugadores.Objetos=Inventario;
                            }
                        }
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            case 2:
            {
                switch (Jugador1->TierAtaque)
                {
                case 1:
                {
                    auto Pos=Inventario.find(3);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierAtaque++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 2:
                {
                    auto Pos=Inventario.find(5);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierAtaque++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 3:
                {
                    auto Pos=Inventario.find(9);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierAtaque++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 4:
                {
                    auto Pos=Inventario.find(10);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierAtaque++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                default:
                    break;
                }
            }
                break;
            case 3:
            {
                switch (Jugador1->TierDefensa)
                {
                case 1:
                {
                    auto Pos=Inventario.find(1);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierDefensa++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 2:
                {
                    auto Pos=Inventario.find(3);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierDefensa++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 3:
                {
                    auto Pos=Inventario.find(6);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierDefensa++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                case 4:
                {
                    auto Pos=Inventario.find(7);
                    if(Pos!=Inventario.end())
                    {
                        if(Pos.value()>=10)
                        {
                            Jugador1->TierDefensa++;
                            Pos.value()-=10;
                            if(Pos.value()==0)
                            {
                                Inventario.erase(Pos);
                            }
                            Jugador1->InventarioJugadores.Objetos=Inventario;
                        }
                    }
                }
                    break;
                default:
                    break;
                }
            }
                break;
            default:
                break;
            }
        }
    }
}

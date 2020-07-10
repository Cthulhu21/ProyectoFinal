#include "NPC.h"
#include "Jugador.h"
#include <math.h>
#include <QTimer>
#include <QGraphicsTextItem>

extern Jugador *Jugador1;
extern Juego *Game;

NPC::NPC(int _ID, int _X, int _Y)
{
    CargarImagen(_ID);
    setPos(_X, _Y);
    QTimer *Busqueda= new QTimer;
    connect(Busqueda,SIGNAL(timeout()),this, SLOT(Hablar()));
    Busqueda->start(1);

    Estatico=false;
}

void NPC::CargarImagen(int _ID)
{
    setPixmap(QPixmap(":/NPCs/"+QString::fromStdString(std::to_string(_ID))));
}

void NPC::Hablar()
{
    float A=(Jugador1->x()+64)-(x()+32);
    float B=(Jugador1->y()+64)-(y()+32);
    if(sqrt(pow(A,2)+pow(B,2))<100 and !TextoEnPantalla)
    {
        Texto= new QGraphicsTextItem("Hola aventurero");
        Texto->setFont(QFont("Times",10));
        Texto->setPos(x()-10,y()-5);
        Game->Pantalla->addItem(Texto);
        TextoEnPantalla=true;
    }
    else if(sqrt(pow(A,2)+pow(B,2))>100 and TextoEnPantalla)
    {
        Game->Pantalla->removeItem(Texto);
        delete Texto;
        TextoEnPantalla=false;
    }
}

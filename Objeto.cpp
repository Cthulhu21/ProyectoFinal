#include "Objeto.h"
#include "Jugador.h"

extern Jugador *Jugador1 ;

Objeto::Objeto(int ID, QGraphicsItem *parent)
{
    Imagen=QPixmap(":/Objetos/CharcoRosa").scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio);
}

void Objeto::MostrarEnMapa()
{
    setPixmap(Imagen);
    setPos(PosX, PosY);
}

void Objeto::Recoger()
{
    QList<QGraphicsItem *> Circundantes=collidingItems();
    for(int i=0; i<Circundantes.size();i++)
    {
        if(typeid(Circundantes[i])==typeid (Jugador))
        {
            Jugador1->AgregarAInventario(this);
        }
    }
}

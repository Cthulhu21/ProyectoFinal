#include "Objeto.h"
#include "Jugador.h"

extern Juego *Game;
extern Jugador *Jugador1 ;

Objeto::Objeto(int _ID, QGraphicsItem *parent)
{
    Imagen=QPixmap(":/Objetos/CharcoRosa").scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio);
    ID=_ID;
}

void Objeto::MostrarEnMapa()
{
    setPixmap(Imagen);
    setPos(PosX, PosY);
    Evento= new QTimer;
    connect(Evento, SIGNAL(timeout()), this, SLOT(Recoger()));
    Evento->start(1);
}

void Objeto::Recoger()
{
    QList<QGraphicsItem *> Circundantes=collidingItems();
    for(int i=0; i<Circundantes.size();i++)
    {
        if(typeid(*Circundantes[i])==typeid (Jugador))
        {
            Jugador1->AgregarAInventario(this);
            Game->Pantalla->removeItem(this);
            auto Inicio=Game->ObjetosSuelo.begin();
            for(auto Elemento: Game->ObjetosSuelo)
            {
                if(Elemento==this)
                {
                    Game->ObjetosSuelo.erase(Inicio);
                    break;
                }
                Inicio++;
            }
            delete this;
        }
    }
}

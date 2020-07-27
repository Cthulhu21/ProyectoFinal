#include "Objeto.h"
#include "Jugador.h"

extern Juego *Game;
extern Jugador *Jugador1 ;

Objeto::Objeto(int _ID, QGraphicsItem *parent)
{
    std::string _Direccion=":/Drop/"+std::to_string(_ID);
    QString Direccion=QString::fromStdString(_Direccion);
    Imagen=QPixmap(Direccion).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio);
    ID=_ID;
    Cantidad=1;
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
            auto Inicio=Game->DropSuelo.begin();
            for(auto Elemento: Game->DropSuelo)
            {
                if(Elemento==this)
                {
                    Game->DropSuelo.erase(Inicio);
                    break;
                }
                Inicio++;
            }
            delete this;
        }
    }
}

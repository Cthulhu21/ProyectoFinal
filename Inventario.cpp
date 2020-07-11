#include "Inventario.h"
#include "Jugador.h"
#include "Casilla.h"

extern Jugador *Jugador1;
extern Juego *Game;

Inventario::Inventario()
{
}

void Inventario::AgregarObjeto(Objeto *_Item)
{
    //Se agrega un objeto extra si ya está en el inventario
    auto Mapa=Jugador1->InventarioJugadores.Objetos;

    if(Mapa.find(_Item->ID)!=Mapa.end())
    {
        if(Mapa[_Item->ID]<10)
            Mapa[_Item->ID]++;
    }
    //Se agrega al inventario
    else
    {
        Mapa.insert(_Item->ID,_Item->Cantidad);
        Mapa[_Item->ID]=1;
    }
    //Jugador1->InventarioJugadores.Objetos=this->Objetos;
    Jugador1->InventarioJugadores.Objetos=Mapa;
}

void Inventario::MostrarInventario()
{
    if(Game->JuegoActivo)
    {
        if(!On)
        {
            Jugador1->Pausar();
            for(auto _Enemigo: Game->EnemigosActuales)
            {
                _Enemigo->Pausar();
            }
            for(auto Elemento: Game->DropSuelo)
            {
                Elemento->setOpacity(0.5);
            }
            for(auto Elemento : Game->ObjetosSuelo)
            {
                Elemento->Pausar();
            }
            for(auto _NPC: Game->NPCs)
            {
                _NPC->Pausar();
            }
            On=true;
        }
        else
        {
            Jugador1->Despausar();
            for(auto _Enemigo: Game->EnemigosActuales)
            {
                _Enemigo->Despausar();
            }
            for(auto Elemento: Game->DropSuelo)
            {
                Elemento->setOpacity(0.5);
            }
            for(auto Elemento : Game->ObjetosSuelo)
            {
                Elemento->Despausar();
            }
            for(auto _NPC: Game->NPCs)
            {
                _NPC->Despausar();
            }
            On=false;
        }
        DibujarInventario(On);
    }
}

void Inventario::DibujarInventario(bool _On)
{
    if(_On)
    {
        //Fondo del inventario
        Fondo= new QGraphicsRectItem;
        Fondo->setRect(100,100,1200,550);
        Fondo->setBrush(QColor(Qt::lightGray));
        Game->Pantalla->addItem(Fondo);

        //Titulo del inventario
        Titulo= new QGraphicsTextItem("Inventario");
        Titulo->setPos(1300/2,100);
        Titulo->setFont(QFont("Times",20));
        Game->Pantalla->addItem(Titulo);

        //Casillas del inventario
        int i=0;
        auto Inicio=Objetos.begin();
        for(auto Elemento: Objetos)
        {
            Casilla *_Casilla= new Casilla(200,(i+1)*200,100,100,Inicio.key());
            QString _Numero=QString::fromStdString(std::to_string(Elemento));
            QGraphicsTextItem *Numero= new QGraphicsTextItem(_Numero);
            Numero->setFont(QFont("Times",10));
            Numero->setPos(500,(i+1)*210);
            Game->Pantalla->addItem(Numero);
            //
            Game->Pantalla->addItem(_Casilla);

            Casillas.push_back(_Casilla);
            Numeros.push_back(Numero);
            i++;
            Inicio++;
        }
    }
    else
    {
        Game->Pantalla->removeItem(Fondo);
        delete Fondo;
        Game->Pantalla->removeItem(Titulo);
        delete Titulo;
        auto InicioNumeros=Numeros.begin();
        for(auto _Casilla    :   Casillas)
        {

            Game->Pantalla->removeItem(_Casilla);
            delete _Casilla;
            Game->Pantalla->removeItem(*InicioNumeros);
            delete  *InicioNumeros;
            InicioNumeros++;
        }
        Casillas.clear();
        Numeros.clear();
    }
}

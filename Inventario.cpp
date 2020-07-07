#include "Inventario.h"
#include "Jugador.h"


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
            for(auto Elemento: Game->ObjetosSuelo)
            {
                Elemento->setOpacity(0.5);
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
            for(auto Elemento: Game->ObjetosSuelo)
            {
                Elemento->setOpacity(1);
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
        for(int i=0; i<Jugador1->InventarioJugadores.Objetos.size();i++)
        {
            //Prueba de texto
            auto A=Jugador1->InventarioJugadores.Objetos[i];
            if(A>0)
            {
                QString _Numero;
                for(auto Letra:std::to_string(A))
                {
                    _Numero+=Letra;
                }
                QGraphicsTextItem *Numero= new QGraphicsTextItem(_Numero);
                Numero->setFont(QFont("Times",10));
                Numero->setPos(210,(i+1)*210);
                Game->Pantalla->addItem(Numero);
                //
                Casilla= new QGraphicsRectItem;
                Casilla->setRect(200,(i+1)*200,100,100);
                Game->Pantalla->addItem(Casilla);
                Casillas.push_back(Casilla);
            }
        }
    }
    else
    {
        Game->Pantalla->removeItem(Fondo);
        delete Fondo;
        Game->Pantalla->removeItem(Titulo);
        delete Titulo;
        for(auto _Casilla    :   Casillas)
        {
            Game->Pantalla->removeItem(_Casilla);
            delete _Casilla;
        }
    }
}

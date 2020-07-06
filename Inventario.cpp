#include "Inventario.h"
#include "Jugador.h"

extern Jugador *Jugador1;
extern Juego *Game;

Inventario::Inventario()
{
    Objetos.clear();
}

void Inventario::AgregarObjeto(Objeto *_Item)
{
    //Se agrega un objeto extra si ya está en el inventario
    if(Objetos.find(_Item->ID)!=Objetos.end())
    {
        if(Objetos[_Item->ID]->Cantidad<10)
            Objetos[_Item->ID]->Cantidad++;
    }
    //Se agrega al inventario
    else
    {
        Objetos.insert(_Item->ID,_Item);
    }
}

void Inventario::MostrarInventario()
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
}

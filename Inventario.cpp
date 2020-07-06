#include "Inventario.h"


Inventario::Inventario()
{
    Objetos.clear();
}

void Inventario::AgregarObjeto(Objeto *_Item)
{
    if(Objetos.find(_Item->ID)!=Objetos.end())
    {
        if(Objetos[_Item->ID]->Cantidad<10)
            Objetos[_Item->ID]->Cantidad++;
    }
    else
    {
        Objetos[_Item->ID]->Cantidad=1;
    }
}

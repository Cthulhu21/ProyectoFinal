#include "Mapa.h"
#include "Enemigo.h"
#include "Juego.h"
#include <fstream>

using namespace std;

extern Juego *Game;


void Mapa::CargarMapas()
{
    ifstream Archivo;
    Archivo.open("C:/Users/William/Documents/Info II/ProyectoFinal/Recursos/Mapas/Conexiones/Mapas.txt");
    if(!Archivo.fail())
    {
        string LineaDeTexto;
        while(!Archivo.eof())
        {
            getline(Archivo, LineaDeTexto);
            string _ID;
            for(auto Letra: LineaDeTexto)
            {
                if(Letra!='\t')
                    _ID+=Letra;
                else
                {
                    break;
                }
            }
            if(to_string(ID)==_ID)
            {
                string I_D;
                bool firts=false;
                for(auto Letra: LineaDeTexto)
                {
                    if(Letra!='\t')
                    {
                        if(firts)
                        I_D+=Letra;
                    }
                    else if(!firts)
                    {
                        firts=true;
                    }
                    else
                    {
                        bool Find=false;
                        for(auto Elemento: Circundantes)
                        {
                            if(Elemento==stoi(I_D))
                            {
                                Find=true;
                                break;
                            }
                        }
                        if(!Find)
                        {
                            Circundantes.push_back(stoi(I_D));
                        }
                        I_D.clear();
                    }
                }
                break;
            }
        }
    }
}

Mapa::Mapa(int _ID)
{
    ID=_ID;
    CargarMapas();
    FondoMapa=QImage(":/Mapas/Recursos/Mapas/"+QString::fromStdString(to_string(_ID)+"F.png"));
    QGraphicsPixmapItem *_Estructura= new QGraphicsPixmapItem;
    _Estructura->setPixmap(QPixmap(":/Mapas/Recursos/Mapas/"+QString::fromStdString(to_string(_ID)+"E.png")));
    Estructura=_Estructura;
    switch (ID)
    {
    case 0:
        NPCs.push_back({1,400,300});
        NPCs.push_back({2,850,100});
        NPCs.push_back({3,1000,600});
        //ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        //Enemigos.push_back({8,500,300});
        break;
    }
}

QBrush Mapa::ConseguirFondo()
{
    return FondoMapa;
}

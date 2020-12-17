#include "Mapa.h"
#include "Enemigo.h"
#include "Juego.h"
#include <fstream>
#include <QFile>
#include <QTextStream>

using namespace std;

extern Juego *Game;


void Mapa::CargarMapas()
{
    QFile Archivo(":/Conexiones/1");
    if(Archivo.open(QFile::ReadOnly))
    {
        QTextStream in(&Archivo);
        QString LineaDeTexto;
        while(!in.atEnd())
        {
            LineaDeTexto=in.readLine();
            string _ID;
            for(auto Letra: LineaDeTexto)
            {
                if(Letra.unicode()!='\t')
                    _ID+=Letra.unicode();
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
                    if(Letra.unicode()!='\t')
                    {
                        if(firts)
                        I_D+=Letra.unicode();
                    }
                    else if(!firts)
                    {
                        firts=true;
                    }
                    else
                    {
                        Circundantes.push_back(stoi(I_D));
                        I_D.clear();
                    }
                }
                break;
            }
        }
    }
    //ifstream Archivo;
    //Archivo.open(":/Conexiones/1", ios::in);
    //Archivo.open("C:/Users/William/Documents/Info II/ProyectoFinal/Recursos/Mapas/Conexiones/Mapas.txt");
    /*if(Archivo.open(QFile::ReadOnly))
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
                        Circundantes.push_back(stoi(I_D));
                        I_D.clear();
                    }
                }
                break;
            }
        }
    }*/
}

Mapa::Mapa(int _ID)
{
    srand(time(NULL));
    ID=_ID;
    CargarMapas();
    FondoMapa=QImage(":/Mapas/Recursos/Mapas/"+QString::fromStdString(to_string(_ID)+"F.png"));
    QGraphicsPixmapItem *_Estructura= new QGraphicsPixmapItem;
    _Estructura->setPixmap(QPixmap(":/Mapas/Recursos/Mapas/"+QString::fromStdString(to_string(_ID)+"E.png")));
    Estructura=_Estructura;
    switch (ID)
    {
    case 0:
    {
        NPCs.push_back({1,400,300});
        NPCs.push_back({2,850,100});
        NPCs.push_back({3,1000,600});
    }
        break;
    case 1:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 2:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 3:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 4:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 5:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 6:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 600,300});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,500});
    }
        break;
    case 7:
    {
        //ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,400});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 700,100});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 1000,500});
    }
        break;
    case 8:
    {
        ObjetosDinamicos.push_back(new ObjetoDinamico(400,500,1));
        int Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 300,100});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 900,100});
        Temp=(rand()%10)+1;
        Enemigos.push_back({Temp, 500,600});
    }
        break;
    }
}

QBrush Mapa::ConseguirFondo()
{
    return FondoMapa;
}

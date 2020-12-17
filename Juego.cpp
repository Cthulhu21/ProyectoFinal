#include "Juego.h"
#include "Boton.h"
#include <QGraphicsPixmapItem>
#include <Jugador.h>
#include <QTimeLine>
#include <windows.h>
#include "Enemigo.h"
#include <NPC.h>
#include <QMouseEvent>
#include <math.h>
#include <fstream>

Jugador *Jugador1;
Jugador *Jugador2;

Juego::Juego(QWidget *parent)
{
    CargarMapas();

    // Se inicializa el juego

    int Ancho=GetSystemMetrics(SM_CXSCREEN), Alto=GetSystemMetrics(SM_CYSCREEN);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(Ancho, Alto);

    Pantalla = new QGraphicsScene;

    Pantalla->setSceneRect(0, 0, Ancho, Alto);

    setScene(Pantalla);
}

void Juego::MenuInicial()
{
    //Limpia la pantalla
    Pantalla->clear();

    // Poner fondo
    setBackgroundBrush(QBrush(":/Mapas/Fondo"));
    QGraphicsPixmapItem *A=new QGraphicsPixmapItem(QPixmap(":/Mapas/1F"));
    Pantalla->addItem(A);

    // Titulo

    QGraphicsTextItem *Titulo = new QGraphicsTextItem(QString("Endless"));
    QFont FuenteTitulo("Times", 50);
    Titulo->setFont(FuenteTitulo);
    int TXPos= this->width()/2 - Titulo->boundingRect().width()/2;
    int TYPos= 150;
    Titulo->setPos(TXPos,TYPos);
    Pantalla->addItem(Titulo);

    //Boton para jugar
    Boton *Jugar = new Boton("Jugar",200,50);
    int BXPos = this->width()/2 - Jugar->boundingRect().width()/2;
    int BYPos= 250;
    Jugar->setPos(BXPos, BYPos);
    Pantalla->addItem(Jugar);
    connect(Jugar,SIGNAL(clicked()),this,SLOT(Animacion()));

    //Boton para Cargar
    Boton *Cargar = new Boton(QString("Cargar"),200,50);
    BXPos = this->width()/2 - Jugar->boundingRect().width()/2;
    BYPos = 350;
    Cargar->setPos(BXPos, BYPos);
    Pantalla->addItem(Cargar);
    connect(Cargar, SIGNAL(clicked()), this, SLOT(CargarPartida()));

    //Boton para salir
    Boton *Salir = new Boton(QString("Salir"),200,50);
    BXPos = this->width()/2 - Jugar->boundingRect().width()/2;
    BYPos = 450;
    Salir->setPos(BXPos, BYPos);
    Pantalla->addItem(Salir);
    connect(Salir, SIGNAL(clicked()), this, SLOT(Cerrar()));
}

void Juego::CambiarMapaActual(Mapa _MapaACambiar)
{
    Pantalla->removeItem(MapaActual.Estructura);

    for(auto Elemento : ObjetosSuelo)
    {
        Pantalla->removeItem(Elemento);
    }
    ObjetosSuelo.clear();

    for(auto Elemento: MapaActual.ObjetosDinamicos)
    {
        Pantalla->removeItem(Elemento);
    }

    for(auto Elemento: DropSuelo)
    {
        Pantalla->removeItem(Elemento);
    }
    for(auto _Enemigo:EnemigosActuales)
    {
        delete _Enemigo;
        //Pantalla->removeItem(_Enemigo);
    }
    for(auto _NPC:NPCs)
    {
        delete _NPC;
        //Pantalla->removeItem(_NPC);
    }
    NPCs.clear();
    //Se reescriben las caracteristicas del enemigo

    QList<QList<int>> Temp;
    for(auto _Enemigo: EnemigosActuales)
    {
        float temp=_Enemigo->ID;
        Temp.push_back({int(std::round(temp)),int(_Enemigo->x()),int(_Enemigo->y())});
    }
    if(Temp.size()!=0)
    {
        MapaActual.Enemigos=Temp;
        Ma_Pas[MapaActual.ID]=MapaActual;
        EnemigosActuales.clear();
    }

    //Añadir los nuevos elementos al mapa
    MapaActual=_MapaACambiar;
    setBackgroundBrush(MapaActual.FondoMapa);
    for(auto Elemento: MapaActual.ObjetosDinamicos)
    {
        Pantalla->addItem(Elemento);
        ObjetosSuelo.push_back(Elemento);
    }
    for(auto _Enemigo: MapaActual.Enemigos)
    {
        int ID=_Enemigo[0];
        int PosX=_Enemigo[1];
        int PosY=_Enemigo[2];
        Enemigo *Tempo= new Enemigo(ID, PosX, PosY);
        Pantalla->addItem(Tempo);
        EnemigosActuales.push_back(Tempo);
    }
    for(auto _NPC: MapaActual.NPCs)
    {
        int ID=_NPC[0];
        int PosX=_NPC[1];
        int PosY=_NPC[2];
        NPC *Temp= new NPC(ID, PosX, PosY);
        Pantalla->addItem(Temp);
        NPCs.push_back(Temp);
    }
    Pantalla->addItem(MapaActual.Estructura);
}

void Juego::MenuPausa()
{
    //Se verifica que las condiciones para pausar sean correctas
    if(!Jugador1->InventarioJugadores.On)
    {
        if(JuegoActivo)
        {
            JuegoActivo=false;
            Jugador1->Pausar();
            for(auto Enemigo: EnemigosActuales)
            {
                Enemigo->Pausar();
            }
            for(auto Elemento: DropSuelo)
            {
                Elemento->setOpacity(0.5);
            }
            for(auto Elemento : ObjetosSuelo)
            {
                Elemento->Pausar();
            }
            for(auto _NPC: NPCs)
            {
                _NPC->Pausar();
            }

            int BXPos = this->width()/2 - Continuar->boundingRect().width()/2;
            Continuar->setPos(BXPos, 150);
            Pantalla->addItem(Continuar);
            connect(Continuar,SIGNAL(clicked()),this,SLOT(CerrarMenuPausa()));

            Guardar->setPos(BXPos, 250);
            connect(Guardar, SIGNAL(clicked()), this, SLOT(GuardarPartida()));
            Pantalla->addItem(Guardar);

            Salir->setPos(BXPos, 350);
            Pantalla->addItem(Salir);
            connect(Salir, SIGNAL(clicked()), this, SLOT(Cerrar()));
        }
        else
        {
            JuegoActivo=true;
            CerrarMenuPausa();
        }
    }
}

void Juego::AgregarDrop(Objeto *_Drop)
{
    //Agrega el objeto recibido al escenario
    Pantalla->addItem(_Drop);
    _Drop->MostrarEnMapa();
}

void Juego::CargarJugador(float X, float Y, int TV, int TA, int TD, int IDM, QList<int> IDsO, QList<int> CaO)
{
    JuegoActivo=true;
    Pantalla->clear();

    Jugador1= new Jugador(Primero, X, Y);
    Jugador1->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador1->setFocus();

    Jugador1->TierVida=TV;
    Jugador1->TierAtaque=TA;
    Jugador1->TierDefensa=TD;

    for(int i=0; i<IDsO.size(); i++)
    {
        Objeto *Temp= new Objeto(IDsO[i]);
        Temp->Cantidad=CaO[i];
        Jugador1->InventarioJugadores.AgregarObjeto(Temp);
    }

    CambiarMapaActual(Ma_Pas[IDM]);
    Pantalla->addItem(Jugador1);
}

void Juego::CerrarMenuPausa()
{
    //Se eliminan los botones del escenario
    Jugador1->Despausar();
    for(auto Enemigo: EnemigosActuales)
    {
        Enemigo->Despausar();
    }
    for(auto Elemento: DropSuelo)
    {
        Elemento->setOpacity(1);
    }
    for(auto _NPC: NPCs)
    {
        _NPC->Despausar();
    }
    for(auto Objeto: ObjetosSuelo)
    {
        Objeto->Despausar();
    }
    QList<QGraphicsItem*> Items=Pantalla->items();
    int i=0;
    for(auto Elemento : Items)
    {
        if(typeid(*Elemento)==typeid(Boton))
        {
            Pantalla->removeItem(Elemento);
            i++;
        }
        else if(i==4) //Para que no itere más llá de la cantidad de botones
        {
            break;
        }
    }
}

void Juego::Cerrar()
{
    exit(0);
}

void Juego::GuardarPartida()
{
    //Se guardan los datos del jugador
    Jugador *a=Jugador1;
    Jugador *b=Jugador2;
    //Busca si es una partida de uno o 2 jugadores
    if(b==nullptr)
    {
        float PosX=std::round(a->PosX),PosY= std::round(a->PosY);
        int TierVida=a->TierVida;
        int TierAtaque=a->TierAtaque;
        int TierDefensa=a->TierDefensa;
        int IDMap=MapaActual.ID;
        QList<QList<int>> Inventario;
        auto Begin=a->InventarioJugadores.Objetos.begin();
        while(Begin!=a->InventarioJugadores.Objetos.end())
        {
            Inventario.push_back({Begin.key(),Begin.value()});
            Begin++;
        }
        std::ofstream Archivo;
        Archivo.open("Partidas.txt",std::ios::out);
        if(!Archivo.fail())
        {
            Archivo<<"1\t"
            <<std::to_string(PosX)<<"\t"
            <<std::to_string(PosY)<<"\t"
            <<std::to_string(TierVida)<<"\t"
            <<std::to_string(TierAtaque)<<"\t"
            <<std::to_string(TierDefensa)<<"\t"
            <<std::to_string(IDMap)<<"\t";
            for(auto Elemento : Inventario)
            {
                Archivo<<std::to_string(Elemento[0])<<"\t"
                <<std::to_string(Elemento[1])<<"\t";
            }
        }
        Archivo.close();
    }
}

void Juego::CargarPartida()
{
    //Buscar la información de las partidas
    std::ifstream Archivo;
    Archivo.open(":/Partidas/1", std::ios::in);
    if(!Archivo.fail())
    {
        std::string Linea;
        while(!Archivo.eof())
        {
            std::getline(Archivo, Linea);
            if(Linea.size()!=0)
            {
                std::string _TipoDePartida;
                _TipoDePartida=Linea[0];
                int TipoDePartida=std::stoi(_TipoDePartida);
                switch (TipoDePartida)
                {
                case 1:
                {

                    int i=0;
                    std::string _X, _Y, _TierVida, _TierAtaque,
                    _TierDefensa, _IDMapa, _Cantidad;
                    QList<std::string> _IDObjetos,_CantidadObjetos;
                    for(auto Letra: Linea)
                    {
                        switch(i)
                        {
                        case 0:
                            if(Letra=='\t')
                            {
                                i++;
                            }
                            break;
                        case 1:
                        {
                            if(Letra!='\t')
                            {
                                _X+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 2:
                        {
                            if(Letra!='\t')
                            {
                                _Y+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 3:
                        {
                            if(Letra!='\t')
                            {
                                _TierVida+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 4:
                        {
                            if(Letra!='\t')
                            {
                                _TierAtaque+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 5:
                        {
                            if(Letra!='\t')
                            {
                                _TierDefensa+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 6:
                        {
                            if(Letra!='\t')
                            {
                                _IDMapa+=Letra;
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 7:
                        {
                            if(Letra!='\t')
                            {
                                _IDObjetos.push_back(std::string(1,Letra));
                            }
                            else
                            {
                                i++;
                            }
                        }
                            break;
                        case 8:
                        {
                            if(Letra!='\t')
                            {
                                _Cantidad+=Letra;
                            }
                            else
                            {
                                _CantidadObjetos.push_back(_Cantidad);
                                //_CantidadObjetos.push_back(std::string(1,_Cantidad));
                                _Cantidad.clear();
                                i=7;
                            }
                        }
                            break;
                        default:
                        {
                            if(Letra=='\t')
                            {
                                i++;
                            }
                        }
                            break;
                        }
                    }
                    int X, Y, TierVida, TierAtaque, TierDefensa, IDMapa;
                    QList<int> IDObjetos, CantidadObjetos;
                    {
                        X=stoi(_X);
                        Y=stoi(_Y);
                        TierVida=stoi(_TierVida);
                        TierAtaque=stoi(_TierAtaque);
                        TierDefensa=stoi(_TierDefensa);
                        IDMapa=stoi(_IDMapa);
                        for(int i=0; i <_IDObjetos.size(); i++)
                        {
                            IDObjetos.push_back(stoi(_IDObjetos[i]));
                            CantidadObjetos.push_back(stoi(_CantidadObjetos[i]));
                        }
                    }
                    CargarJugador(X, Y, TierVida, TierAtaque, TierDefensa, IDMapa, IDObjetos, CantidadObjetos);
                    Archivo.close();
                }
                    break;
                case 2:
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void Juego::CargarMapas()
{
    // Se cargarán todos los mapas asociados al juego
    for(int i=0; i<9;i++)
    {
        Mapa _Mapa(i);
        Ma_Pas[i]=_Mapa;
    }
    MapaActual= Ma_Pas[1];
}

void Juego::Animacion()
{
    //
    JuegoActivo=true;

    Pantalla->clear();

    CambiarMapaActual(Ma_Pas[0]);

    Jugador1= new Jugador(Primero, 200, 500);
    Jugador1->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador1->setFocus();

    Pantalla->addItem(Jugador1);

    //MenuPausa();
    //MenuPausa();
    /*NPC *Heroina= new NPC(1,500,500);
    Pantalla->addItem(Heroina);
    NPCs.push_back(Heroina);

    Enemigo *Slime1= new Enemigo(100,100), *Slime2 = new Enemigo(200,200), *Slime3= new Enemigo(300,300);

    EnemigosActuales.push_back(Slime1);
    EnemigosActuales.push_back(Slime2);
    EnemigosActuales.push_back(Slime3);*/

}

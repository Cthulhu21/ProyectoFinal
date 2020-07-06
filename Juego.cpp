#include "Juego.h"
#include "Boton.h"
#include <QGraphicsPixmapItem>
#include <Jugador.h>
#include <QTimeLine>
#include <windows.h>
#include "Enemigo.h"

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
    setBackgroundBrush(Mapas[0].ConseguirFondo());
    CambiarMapaActual(Mapas[0]);

    // Titulo

    QGraphicsTextItem *Titulo = new QGraphicsTextItem(QString("Endless"));
    QFont FuenteTitulo("Times", 50);
    Titulo->setFont(FuenteTitulo);
    int TXPos= this->width()/2 - Titulo->boundingRect().width()/2;
    int TYPos= 150;
    Titulo->setPos(TXPos,TYPos);
    Pantalla->addItem(Titulo);

    //Boton para jugar
    Boton *Jugar = new Boton(QString("Jugar"),200,50);
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
    MapaActual=_MapaACambiar;
}

void Juego::MenuPausa()
{
    if(JuegoActivo)
    {
        JuegoActivo=false;
        Jugador1->Pausar();
        for(int i=0; i<EnemigosActuales.size(); i++)
        {
            EnemigosActuales[i]->Pausar();
        }
        for(auto Elemento: ObjetosSuelo)
        {
            Elemento->setOpacity(0.5);
        }

        int BXPos = this->width()/2 - Continuar->boundingRect().width()/2;
        Continuar->setPos(BXPos, 150);
        Pantalla->addItem(Continuar);
        connect(Continuar,SIGNAL(clicked()),this,SLOT(CerrarMenuPausa()));

        Guardar->setPos(BXPos, 250);
        Pantalla->addItem(Guardar);

        Cargar->setPos(BXPos, 350);
        Pantalla->addItem(Cargar);

        Salir->setPos(BXPos, 450);
        Pantalla->addItem(Salir);
    }
    else
    {
        JuegoActivo=true;
        CerrarMenuPausa();
    }
}

void Juego::AgregarDrop(Objeto *_Drop)
{
    //Agrega el objeto recibido al escenario
    Pantalla->addItem(_Drop);
    _Drop->MostrarEnMapa();
}

void Juego::CerrarMenuPausa()
{
    //Se eliminan los botones del escenario
    JuegoActivo=true;
    Jugador1->Despausar();
    for(int i =0; i<EnemigosActuales.size(); i++)
    {
        EnemigosActuales[i]->Despausar();
    }
    for(auto Elemento: ObjetosSuelo)
    {
        Elemento->setOpacity(1);
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

void Juego::CargarMapas()
{
    // Se cargarán todos los mapas asociados al juego
    QImage *_Mapa1= new QImage(":/Mapas/Fondo");
    Mapa _Mapa(0,_Mapa1);
    Mapas.push_back(_Mapa);
}

void Juego::Animacion()
{
    //
    JuegoStart=true;
    JuegoActivo=true;

    Pantalla->clear();

    Jugador1= new Jugador(Primero, 0, 0);
    Jugador1->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador1->setFocus();

    Enemigo *Slime1= new Enemigo(100,100), *Slime2 = new Enemigo(200,200), *Slime3= new Enemigo(300,300);

    EnemigosActuales.push_back(Slime1);
    EnemigosActuales.push_back(Slime2);
    EnemigosActuales.push_back(Slime3);

    Pantalla->addItem(Slime1);
    Pantalla->addItem(Slime2);
    Pantalla->addItem(Slime3);

    Pantalla->addItem(Jugador1);
}

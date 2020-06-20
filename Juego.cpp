#include "Juego.h"
#include "Boton.h"

Juego::Juego(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,700);

    Pantalla = new QGraphicsScene;
    Pantalla->setSceneRect(0,0,1024,700);

    setScene(Pantalla);
}

void Juego::MenuInicial()
{
    Pantalla->clear();

    // Poner fondo

    setBackgroundBrush(QBrush(QImage(":/Fondo/Recursos/Fondo.png")));

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
}

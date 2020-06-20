#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsView>

class Juego: public QGraphicsView
{
public:
    //Constructor
    Juego(QWidget *parent=NULL);

    //Atributos públicos
    QGraphicsScene *Pantalla;

    //Metodos públicos

    void MenuInicial();

};

#endif // JUEGO_H

#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>

class Juego: public QGraphicsView
{
    Q_OBJECT
public:
    //Constructor
    Juego(QWidget *parent=NULL);

    //Atributos públicos
    QGraphicsScene *Pantalla;

    //Metodos públicos

    void MenuInicial();
public slots:

    void Animacion();

};

#endif // JUEGO_H

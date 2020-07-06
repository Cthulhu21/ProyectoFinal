#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <Mapa.h>
#include <Boton.h>
#include <QKeyEvent>
#include "Enemigo.h"

class Juego: public QGraphicsView
{
    Q_OBJECT
public:
    //Constructor
    Juego(QWidget *parent=NULL);

    //Atributos públicos
    bool JuegoActivo=false;
    bool JuegoStart=false;
    QGraphicsScene *Pantalla;
    QList<Enemigo*> EnemigosActuales;

    //Metodos públicos

    void MenuInicial();
    void CambiarMapaActual(Mapa _MapaACambiar);
    void PonerMapa(Mapa _Mapa);

    void MenuPausa();
    void AgregarDrop(Objeto *_Drop);


    // Botones

    Boton *Continuar = new Boton(QString("Continuar"), 200, 50);
    Boton *Guardar = new Boton(QString("Guardar"), 200, 50);;
    Boton *Cargar = new Boton(QString("Cargar"), 200, 50);;
    Boton *Salir = new Boton(QString("Salir"), 200, 50);;
    //
private:
    QList<Mapa> Mapas;
    Mapa MapaActual;
    void CargarMapas();

public slots:

    void Animacion();
    void CerrarMenuPausa();

};

#endif // JUEGO_H

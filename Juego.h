#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <Mapa.h>
#include <Boton.h>
#include <QKeyEvent>

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

    //Metodos públicos

    void MenuInicial();
    void CambiarMapaActual(Mapa _MapaACambiar);
    void PonerMapa(Mapa _Mapa);

    void MenuPausa();
    void CerrarMenuPausa();

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

    void ContinuarJuego();
    void Animacion();

};

#endif // JUEGO_H

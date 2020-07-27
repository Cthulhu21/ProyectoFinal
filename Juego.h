#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <Mapa.h>
#include <Boton.h>
#include <QKeyEvent>
#include "Enemigo.h"
#include "Objeto.h"
#include "ObjetoDinamico.h"
#include "NPC.h"

class Juego: public QGraphicsView
{
    Q_OBJECT
public:
    //Constructor
    Juego(QWidget *parent=NULL);

    //Atributos públicos
    bool JuegoActivo=false;
    QGraphicsScene *Pantalla;
    QList<Enemigo*> EnemigosActuales;
    QList<Objeto*> DropSuelo;
    QList<ObjetoDinamico*> ObjetosSuelo;
    QList<NPC*> NPCs;
    Mapa MapaActual;
    QMap<int, Mapa> Ma_Pas;

    //Metodos públicos

    void MenuInicial();
    void CambiarMapaActual(Mapa _MapaACambiar);
    void PonerMapa(Mapa _Mapa);
    void MenuPausa();
    void AgregarDrop(Objeto *_Drop);
    void CargarJugador(float X, float Y, int TV, int TA, int TD, int IDM ,QList<int> IDsO, QList<int> CaO);


    // Botones

    Boton *Continuar = new Boton(QString("Continuar"), 200, 50);
    Boton *Guardar = new Boton(QString("Guardar"), 200, 50);;
    Boton *Salir = new Boton(QString("Salir"), 200, 50);;
    //
private:
    QList<Mapa> Mapas;

    void CargarMapas();


public slots:

    void Animacion();
    void CerrarMenuPausa();
    void Cerrar();
    void GuardarPartida();
    void CargarPartida();
};

#endif // JUEGO_H

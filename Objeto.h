#ifndef OBJETO_H
#define OBJETO_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Objeto:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Objeto(int ID, QGraphicsItem *parent=NULL);

    //Atributos

    QPixmap Imagen;
    int PosX, PosY;
    int Cantidad=1;
    int ID;

    //Metodos
    void MostrarEnMapa();
    void Recoger();
};

#endif // OBJETO_H

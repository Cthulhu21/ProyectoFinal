#ifndef BOTON_H
#define BOTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>


//Clase auxiliar
class Boton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Boton(QString Nombre,int Ancho, int Largo, QGraphicsItem *parent =NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void PasarSobre();
    void clicked();

private:
    QGraphicsTextItem * Texto;
};

#endif // BOTON_H

#include "Boton.h"

#include "Boton.h"
#include <QGraphicsTextItem>
#include <QBrush>


Boton::Boton(QString Nombre,int Ancho, int Largo, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0, 0, Ancho, Largo);
    QBrush Brush;
    Brush.setStyle(Qt::SolidPattern);
    Brush.setColor(Qt::darkCyan);
    setBrush(Brush);

    Texto= new QGraphicsTextItem(Nombre, this);
    int PosX= rect().width()/2 - Texto->boundingRect().width()/2;
    int PosY= rect().height()/2 - Texto->boundingRect().height()/2;
    Texto->setPos(PosX, PosY);

    setAcceptHoverEvents(true);
}

void Boton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Boton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush Brush;
    Brush.setStyle(Qt::SolidPattern);
    Brush.setColor(Qt::cyan);
    setBrush(Brush);
}

void Boton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush Brush;
    Brush.setStyle(Qt::SolidPattern);
    Brush.setColor(Qt::darkCyan);
    setBrush(Brush);
}

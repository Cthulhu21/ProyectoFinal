#include "Casilla.h"
#include <QBrush>

Casilla::Casilla(int X, int Y, int W, int H, int ID)
{
    setPos(X,Y);
    //setRect(X,Y,W,H);
    Imagen(ID);
}

void Casilla::Imagen(int _ID)
{
    std::string DireccionArchivo=":/Drop/"+std::to_string(_ID);
    QString _Dir=QString::fromStdString(DireccionArchivo);
    setPixmap(QPixmap(_Dir).scaled(50,50,Qt::AspectRatioMode::KeepAspectRatio));
    //setBrush(QBrush(QPixmap(_Dir)));
}

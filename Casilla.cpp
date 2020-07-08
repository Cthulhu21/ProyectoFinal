#include "Casilla.h"
#include <QBrush>

Casilla::Casilla(int X, int Y, int W, int H, int ID)
{
    setRect(X,Y,W,H);
    Imagen(ID);
}

void Casilla::Imagen(int _ID)
{
    std::string DireccionArchivo=":/Objetos/"+std::to_string(_ID);
    QString _Dir=QString::fromStdString(DireccionArchivo);
    setBrush(QBrush(QPixmap(_Dir)));
}

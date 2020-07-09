#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>

class NPC:public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NPC(int _ID, int X, int Y);
    void CargarImagen(int _ID);
private:
    QGraphicsTextItem *Texto;
    bool TextoEnPantalla=false;
public slots:
    void Hablar();
};

#endif // NPC_H

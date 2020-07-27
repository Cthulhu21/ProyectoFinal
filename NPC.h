#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>

class NPC:public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NPC(int _ID, int X, int Y);
    void CargarImagen();
    bool Estatico;
    void Pausar();
    void Despausar();

private:
    QGraphicsTextItem *Texto;
    bool TextoEnPantalla=false;
    void CargarDialogos();

    int ID;
    int Tiempo=0;

    QList<QString> AumentosV;
    QList<QString> AumentosA;
    QList<QString> AumentosD;

public slots:
    void Hablar();
};

#endif // NPC_H

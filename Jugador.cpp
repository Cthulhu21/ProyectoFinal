#include "Jugador.h"
#include <math.h>

int FrameDerecha=0;
int FrameIzquierda=0;
int FrameAbajo=0;
int FrameArriba=0;
int FrameEstatica=0;

Tecla TeclaPresionada(QKeyEvent *event);
Tecla Direccion=Derecha;

Jugador::Jugador(int X, int Y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    // Se inicializa al personaje
    QPixmap Player(":/Personajes/Pri");
    Player=Player.copy(0,0,16,32);
    setPixmap(Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio));

    PosX=X;
    PosY=Y;
    VelocidadX=0;
    VelocidadY=0;
    AceleracionX=0;
    AceleracionY=0;
    ResistenciaAire=0.08;
    DeltaTiempo=0.01;

    QTimer *Delta=new QTimer;
    connect(Delta,SIGNAL(timeout()),this, SLOT(Actualizar()));
    Delta->start(1);

    QTimer *Animacion= new QTimer;
    connect(Animacion, SIGNAL(timeout()), this, SLOT(Movimiento()));
    Animacion->start(80);
}


void Jugador::keyPressEvent(QKeyEvent *event)
{
    // Se elige la accion del personaje
    Tecla Presionada;
    Presionada = TeclaPresionada(event);

    // Se ejecuta la accion asociada
    switch (Presionada)
    {
    default:
        Mover(Presionada);
        break;
    }
}

void Jugador::Velocidad(float _VelocidadX, float _VelocidadY)
{
    // Se actualiza la velocidad y posicion

    VelocidadX=_VelocidadX;
    VelocidadY=_VelocidadY;
}

void Jugador::Actualizar()
{
    // Se actualizan los datos de posicion y velocidad
    VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
    Angulo = atan2(VelocidadY,VelocidadX);

    AceleracionX = (0.045*pow(VectorVelocidad,2))*-cos(Angulo);
    AceleracionY = (0.045*pow(VectorVelocidad,2))*-sin(Angulo);

    PosX = PosX + VelocidadX*DeltaTiempo + (AceleracionX*pow(DeltaTiempo,2)/2);
    PosY = PosY + VelocidadY*DeltaTiempo + (AceleracionY*pow(DeltaTiempo,2)/2);

    // Se verifica que no se salga del mapa; si lo hace, se toma como choque -> Velocidad 0
    {
        if(PosX>952)
        {
            PosX=952;
            VelocidadX=0;
        }
        else if(PosX<0)
        {
            VelocidadX=0;
            PosX=0;
        }
        if(PosY<-36)
        {
            PosY=-36;
            VelocidadY=0;
        }
        else if(PosY>600)
        {
            PosY=600;
            VelocidadY=0;
        }
    }


    VelocidadX = VelocidadX + AceleracionX*DeltaTiempo;
    VelocidadY = VelocidadY + AceleracionY*DeltaTiempo;

    if(abs(VelocidadX)>50 or abs(VelocidadY)>50)
    {
        if(VelocidadX>50)
        {
            VelocidadX=50;
        }
        else if (VelocidadX<-50)
        {
            VelocidadX=-50;
        }
        if(VelocidadY>50)
        {
            VelocidadY=50;
        }
        else if (VelocidadY<-50)
        {
            VelocidadY=-50;
        }
    }

    // Determina velocidad mínima
    {
        if(abs(VelocidadX)<2.25)
        {
            VelocidadX=0;
        }
        if(abs(VelocidadY)<2.25)
        {
            VelocidadY=0;
        }
    }
    setPos(PosX,PosY);
}

void Jugador::Movimiento()
{
    if(VelocidadX==0 and VelocidadY==0)
    {
        Estatica(Direccion);
    }
    else
    {
        switch (Direccion)
        {
        case Izquierda:
            MoverIzquierda();
            break;
        case Derecha:
            MoverDerecha();
            break;
        case Abajo:
            MoverAbajo();
        default:
            break;
        }
    }
}

Tecla TeclaPresionada(QKeyEvent *event)
{
    Tecla Presionada=Arriba;
    if(event->key()==Qt::Key_Space)
    {
        Presionada=Tecla::Espacio;
    }
    else if(event->key()==Qt::Key_Up)
    {
        Direccion=Arriba;
        Presionada=Arriba;
    }
    else if(event->key()==Qt::Key_Down)
    {
        Direccion=Abajo;
        Presionada=Abajo;
    }
    else if(event->key()==Qt::Key_Right)
    {
        Direccion=Derecha;
        Presionada=Derecha;
    }
    else if(event->key()==Qt::Key_Left)
    {
        Direccion=Izquierda;
        Presionada=Izquierda;
    }
    return Presionada;
}



void Jugador::Mover(Tecla Direccion)
{
    switch (Direccion)
    {
    case Derecha:
        Velocidad(VelocidadX+40, VelocidadY);
        break;
    case Izquierda:
        Velocidad(VelocidadX-40, VelocidadY);
        break;
    case Arriba:
        Velocidad(VelocidadX, VelocidadY-40);
        break;
    case Abajo:
        Velocidad(VelocidadX, VelocidadY+40);
        break;
    default:
        break;
    }
}

void Jugador::MoverIzquierda()
{
    QPixmap Player(":/Personajes/Pri");
    {
        switch (FrameIzquierda)
        {
        case 0:
            setPixmap(Player.copy(40,0,24,33).scaled(100,100, Qt::AspectRatioMode::KeepAspectRatio));
            FrameIzquierda++;
            break;
        case 1:
            setPixmap(Player.copy(40,34,24,33).scaled(100,100, Qt::AspectRatioMode::KeepAspectRatio));
            FrameIzquierda++;
            break;
        case 2:
            setPixmap(Player.copy(40,68,24,33).scaled(100,100, Qt::AspectRatioMode::KeepAspectRatio));
            FrameIzquierda++;
            break;
        case 3:
            setPixmap(Player.copy(40,102,24,33).scaled(100,100, Qt::AspectRatioMode::KeepAspectRatio));
            FrameIzquierda=0;
            break;
        }
    }
}

void Jugador::MoverDerecha()
{
    QPixmap Player(":/Personajes/Pri");
    {
        switch (FrameDerecha)
        {
        case 0:
            Player=Player.copy(40,0,24,33).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameDerecha++;
            break;
        case 1:
            Player=Player.copy(40,34,24,33).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameDerecha++;
            break;
        case 2:
            Player=Player.copy(40,68,24,33).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameDerecha++;
            break;
        case 3:
            Player=Player.copy(40,102,24,33).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameDerecha=0;
            break;
        }
    }
}

void Jugador::MoverAbajo()
{
    QPixmap Player(":/Personajes/Pri");
    switch (FrameAbajo)
    {
    case 0:
        setPixmap(Player.copy(80,0,17,36).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio));
        FrameAbajo++;
        break;
    case 1:
        setPixmap(Player.copy(80,38,17,36).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio));
        FrameAbajo++;
        break;
    case 2:
        setPixmap(Player.copy(80,77,17,36).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio));
        FrameAbajo++;
        break;
    case 3:
        setPixmap(Player.copy(80,113,17,36).scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio));
        FrameAbajo=0;
        break;
    }
}

void Jugador::Estatica(Tecla _Direccion)
{
    QPixmap Player(":/Personajes/Pri");
    switch (FrameEstatica)
    {
    case 0:
        switch (_Direccion)
        {
        case Izquierda:
            Player=Player.copy(0,0,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameEstatica++;
            break;
        case Derecha:
            Player=Player.copy(0,0,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            setPixmap(Player);
            FrameEstatica++;
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (_Direccion)
        {
        case Izquierda:
            Player=Player.copy(0,33,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameEstatica++;
            break;
        case Derecha:
            Player=Player.copy(0,33,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            setPixmap(Player);
            FrameEstatica++;
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (_Direccion)
        {
        case Izquierda:
            Player=Player.copy(0,67,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            Player=Player.transformed(QTransform().scale(-1,1));
            setPixmap(Player);
            FrameEstatica=0;
            break;
        case Derecha:
            Player=Player.copy(0,67,16,32);
            Player=Player.scaled(100,100,Qt::AspectRatioMode::KeepAspectRatio);
            setPixmap(Player);
            FrameEstatica=0;
            break;
        default:
            break;
        }
        break;
    }
}


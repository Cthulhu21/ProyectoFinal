#include "Jugador.h"
#include <math.h>


Jugador::Jugador(int X, int Y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    // Se inicializa al personaje

    // Para las fisicas
    PosX=X;
    PosY=Y;
    VelocidadX=0;
    VelocidadY=0;
    AceleracionX=0;
    AceleracionY=0;
    ResistenciaAire=0.08;
    DeltaTiempo=0.01;

    // Actualizar parametros de fisicas
    connect(Delta,SIGNAL(timeout()),this, SLOT(Actualizar()));
    Delta->start(1);

    //Actualizar animacion del jugador
    connect(Animacion, SIGNAL(timeout()), this, SLOT(Movimiento()));
    Animacion->start(60);
}

void Jugador::Actualizar()
{
    // Se actualizan los datos de posicion y velocidad

    VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
    Angulo = atan2(VelocidadY,VelocidadX);

    AceleracionX = (ResistenciaAire*pow(VectorVelocidad,2))*-cos(Angulo);
    AceleracionY = (ResistenciaAire*pow(VectorVelocidad,2))*-sin(Angulo);

    PosX = PosX + VelocidadX*DeltaTiempo + ((AceleracionX*pow(DeltaTiempo,2))/2);
    PosY = PosY + VelocidadY*DeltaTiempo + ((AceleracionY*pow(DeltaTiempo,2))/2);

    VelocidadX = VelocidadX + AceleracionX*DeltaTiempo;
    VelocidadY = VelocidadY + AceleracionY*DeltaTiempo;

    // Se verifica que no se salga del mapa; si lo hace, se toma como choque -> Velocidad 0
    {
        if(PosX>775)
        {
            PosX=775;
            VelocidadX=0;
        }
        else if(PosX<-150)
        {
            VelocidadX=0;
            PosX=-150;
        }
        if(PosY<-150)
        {
            PosY=-150;
            VelocidadY=0;
        }
        else if(PosY>450)
        {
            PosY=450;
            VelocidadY=0;
        }
    }
    // Determina velocidad mínima
    {
        float VelocidadMinima=5;
        if(abs(VelocidadX)<VelocidadMinima)
        {
            VelocidadX=0;
        }
        if(abs(VelocidadY)<VelocidadMinima)
        {
            VelocidadY=0;
        }
    }
    setPos(PosX, PosY);
}


void Jugador::keyPressEvent(QKeyEvent *event)
{
    // Se elige la accion del personaje
    Tecla Presionada;
    Presionada = TeclaPresionada(event);

    // Se ejecuta la accion asociada
    switch (Presionada)
    {
    case Espacio:
        if(!Atacando)
            Ataque();
        break;
    case Derecha:
    case Izquierda:
    case Arriba:
    case Abajo:
        Mover();
        break;
    default:
        break;
    }
}

void Jugador::Velocidad(float _VelocidadX, float _VelocidadY, float _AceleracionX, float _AceleracionY)
{
    // Se actualiza la velocidad y posicion

    VelocidadX=_VelocidadX;
    VelocidadY=_VelocidadY;
    AceleracionX=_AceleracionX;
    AceleracionY=_AceleracionY;
}

void Jugador::Ataque()
{
    TimerAtaque = new QTimer;
    Atacando=true;
    Animacion->stop();
    Delta->stop();
    ListaMovimiento=CargarMovimiento();
    TimerAtaque->start(20);
    connect(TimerAtaque, SIGNAL(timeout()), this, SLOT(EjecutarAtaque()));
}

QList<QPixmap> Jugador::CargarMovimiento()
{
    QList<QPixmap> Lista;
    if(Atacando)
    {
        switch (Direccion)
        {
        case Abajo:
            for(int i=1; i<43; i++)
            {
                std::string _DireccionArchivo=":/PersonajePrincipal/A_Ab";
                _DireccionArchivo+=(std::to_string(i));
                QString DireccionArchivo;
                for(auto Letra : _DireccionArchivo)
                {
                    DireccionArchivo+=Letra;
                }
                Lista.push_back(QPixmap(DireccionArchivo).scaled(600,600,Qt::AspectRatioMode::KeepAspectRatio));
            }
            break;
        default:
            break;
        }
        return  Lista;
    }
    else
    {
        //Moviendose=true;
        if(Estatico)
        {
            switch (Direccion)
            {
            case Derecha:
                for(int i=1; i<11; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Iz";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio).transformed(QTransform().scale(-1,1)));
                }
                break;
            case Arriba:
                for(int i=1; i<11; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ar";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            case Abajo:
                for(int i=1; i<11; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ab";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            case Izquierda:
                for(int i=1; i<11; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Iz";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            default:
                break;
            }
        }
        else
        {
            switch (Direccion)
            {
            /*case Espacio:
                for(int i=1; i<43;i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/A_Ab";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;*/
            case Derecha:
                for(int i=1; i<9; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            case Izquierda:
                for(int i=1; i<9; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            case Arriba:
                for(int i=1; i<9; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Arr";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            case Abajo:
                for(int i=1; i<9; i++)
                {
                    std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Ab";
                    _DireccionArchivo+=(std::to_string(i));
                    QString DireccionArchivo;
                    for(auto Letra : _DireccionArchivo)
                    {
                        DireccionArchivo+=Letra;
                    }
                    Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
                }
                break;
            default:
                break;
            }
        }
    }
    return Lista;
}


void Jugador::Movimiento()
{
    if(!Atacando)
    {
        Estatico=(VelocidadX==0 and VelocidadY==0)? true: false;

        // Se llama a los sprites de movimiento

        ListaMovimiento=CargarMovimiento();
        EjecutarMovimientos();
    }
}

Tecla Jugador::TeclaPresionada(QKeyEvent *event)
{
    Tecla Presionada=NULA;
    if(!Atacando)
    {
        switch (event->key())
        {
        case Qt::Key_Space:
            Presionada=Espacio;
            break;
        case Qt::Key_Up:
            Direccion=Arriba;
            Presionada=Arriba;
            break;
        case Qt::Key_Down:
            Direccion=Abajo;
            Presionada=Abajo;
            break;
        case Qt::Key_Right:
            Direccion=Derecha;
            Presionada=Derecha;
            break;
        case Qt::Key_Left:
            Direccion=Izquierda;
            Presionada=Izquierda;
            break;
        default:
            Direccion=_Direccion;
            break;
        }
    }
    return Presionada;
}

void Jugador::Mover()
{
    if(!Atacando)
    {
        int PlusAceleracion=0, PlusVelocidad=40;
        switch (Direccion)
        {
        case Derecha:
            Velocidad(VelocidadX+PlusVelocidad, VelocidadY, AceleracionX+PlusAceleracion, AceleracionY);
            break;
        case Izquierda:
            Velocidad(VelocidadX-PlusVelocidad, VelocidadY, AceleracionX-PlusAceleracion, AceleracionY);
            break;
        case Arriba:
            Velocidad(VelocidadX, VelocidadY-PlusVelocidad, AceleracionX, AceleracionY-PlusAceleracion);
            break;
        case Abajo:
            Velocidad(VelocidadX, VelocidadY+PlusVelocidad, AceleracionX,AceleracionY+PlusAceleracion);
            break;
        default:
            break;
        }
    }
}
void Jugador::EjecutarMovimientos()
{
    if(FrameMovimiento>=ListaMovimiento.size())
    {
        FrameMovimiento=0;
        TimerMovimiento->stop();
        Moviendose=false;
    }
    else
    {
        setPixmap(ListaMovimiento[FrameMovimiento]);
        FrameMovimiento++;
    }
}

void Jugador::EjecutarAtaque()
{
    if(FrameAtaque>=ListaMovimiento.size())
    {
        Delta->start(1);
        Animacion->start(60);
        TimerAtaque->stop();

        FrameAtaque=0;
        Atacando=false;
    }
    else
    {
        // Reacomodar, culpa del sprite
        if(FrameAtaque!=42)
        {
            setPos(PosX-100, PosY-100);
            setPixmap(ListaMovimiento[FrameAtaque]);
        }
        else
        {
            setPixmap(ListaMovimiento[FrameAtaque]);
        }
        FrameAtaque++;
    }
}


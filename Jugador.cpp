#include "Jugador.h"
#include <math.h>

extern Jugador *Jugador1, *Jugador2;
extern Juego *Game;

Jugador::Jugador(NumeroJugador _NumeroJugador ,int X, int Y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    // Se inicializa al personaje

    //Cargar los sprites
    CargarSprites();
    // Para las fisicas
    Numero=_NumeroJugador;
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

void Jugador::CargarSprites()
{
    //Se cargan todos los sprites en sus respectivas listas
    //Parado Derecha
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        ParadoDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Parado Izquierda
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        ParadoIzquierda.push_back(QPixmap(DireccionArchivo));
        //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
    }
    //Parado Arriba
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ar";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        ParadoArriba.push_back(QPixmap(DireccionArchivo));
    }
    //Parado Abajo
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        ParadoAbajo.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Derecha
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        CorrerDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Correr Izquierda
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        CorrerIzquierda.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Arriba
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Arr";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        CorrerArriba.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Abajo
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        CorrerAbajo.push_back(QPixmap(DireccionArchivo));
    }
    //Ataque Derecha
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        AtacarDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Atacar Izquierda
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        AtacarIzquierda.push_back(QPixmap(DireccionArchivo));
    }
    //Ataque Arriba
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Ar";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        AtacarArriba.push_back(QPixmap(DireccionArchivo));
        //Lista.push_back(QPixmap(DireccionArchivo).scaled(650,650,Qt::AspectRatioMode::KeepAspectRatio));
    }
    //Ataque Abajo
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo;
        for(auto Letra : _DireccionArchivo)
        {
            DireccionArchivo+=Letra;
        }
        AtacarAbajo.push_back(QPixmap(DireccionArchivo));
    }
}

void Jugador::Pausar()
{
    setOpacity(0.5);
    Delta->stop();
    Animacion->stop();
}

void Jugador::Despausar()
{
    //Jugador1->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador1->setFocus();
    setOpacity(1);
    Delta->start(1);
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

    PosX=(PosX<0)? 0: PosX;
    PosY=(PosY<0)? 0: PosY;
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

void Jugador::Mover()
{
    switch (Numero)
    {
    case Primero:
        if(!Atacando)
        {
            int PlusAceleracion=0, PlusVelocidad=40;
            switch (Direccion)
            {
            case Derecha:
                Jugador1->Velocidad(VelocidadX+PlusVelocidad, VelocidadY, AceleracionX+PlusAceleracion, AceleracionY);
                break;
            case Izquierda:
                Jugador1->Velocidad(VelocidadX-PlusVelocidad, VelocidadY, AceleracionX-PlusAceleracion, AceleracionY);
                break;
            case Arriba:
                Jugador1->Velocidad(VelocidadX, VelocidadY-PlusVelocidad, AceleracionX, AceleracionY-PlusAceleracion);
                break;
            case Abajo:
                Jugador1->Velocidad(VelocidadX, VelocidadY+PlusVelocidad, AceleracionX,AceleracionY+PlusAceleracion);
                break;
            default:
                break;
            }
        }
        break;
    case Segundo:
        if(!Atacando)
        {
            int PlusAceleracion=0, PlusVelocidad=40;
            switch (Direccion)
            {
            case Derecha:
                Jugador2->Velocidad(VelocidadX+PlusVelocidad, VelocidadY, AceleracionX+PlusAceleracion, AceleracionY);
                break;
            case Izquierda:
                Jugador2->Velocidad(VelocidadX-PlusVelocidad, VelocidadY, AceleracionX-PlusAceleracion, AceleracionY);
                break;
            case Arriba:
                Jugador2->Velocidad(VelocidadX, VelocidadY-PlusVelocidad, AceleracionX, AceleracionY-PlusAceleracion);
                break;
            case Abajo:
                Jugador2->Velocidad(VelocidadX, VelocidadY+PlusVelocidad, AceleracionX,AceleracionY+PlusAceleracion);
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
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
    case Esc:
        Game->MenuPausa();
        break;
    default:
        break;
    }
}

void Jugador::Velocidad(float _VelocidadX, float _VelocidadY, float _AceleracionX, float _AceleracionY)
{
    // Se actualiza la velocidad y posicion

    VelocidadX+=_VelocidadX;
    VelocidadY+=_VelocidadY;
    AceleracionX+=_AceleracionX;
    AceleracionY+=_AceleracionY;
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
                Lista.push_back(QPixmap(DireccionArchivo));
                //Lista.push_back(QPixmap(DireccionArchivo).scaled(650,650,Qt::AspectRatioMode::KeepAspectRatio));
            }
            break;
        case Izquierda:
            for(int i=1; i<43; i++)
            {
                std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
                _DireccionArchivo+=(std::to_string(i));
                QString DireccionArchivo;
                for(auto Letra : _DireccionArchivo)
                {
                    DireccionArchivo+=Letra;
                }
                Lista.push_back(QPixmap(DireccionArchivo));
                //Lista.push_back(QPixmap(DireccionArchivo).scaled(650,650,Qt::AspectRatioMode::KeepAspectRatio));
            }
            break;
        case Arriba:
            for(int i=1; i<43; i++)
            {
                std::string _DireccionArchivo=":/PersonajePrincipal/A_Ar";
                _DireccionArchivo+=(std::to_string(i));
                QString DireccionArchivo;
                for(auto Letra : _DireccionArchivo)
                {
                    DireccionArchivo+=Letra;
                }
                Lista.push_back(QPixmap(DireccionArchivo));
                //Lista.push_back(QPixmap(DireccionArchivo).scaled(650,650,Qt::AspectRatioMode::KeepAspectRatio));
            }
            break;
        case Derecha:
            for(int i=1; i<43; i++)
            {
                std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
                _DireccionArchivo+=(std::to_string(i));
                QString DireccionArchivo;
                for(auto Letra : _DireccionArchivo)
                {
                    DireccionArchivo+=Letra;
                }
                Lista.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
                //Lista.push_back(QPixmap(DireccionArchivo).scaled(650,650,Qt::AspectRatioMode::KeepAspectRatio));
            }
            break;
        default:
            break;
        }
        return  Lista;
    }
    else
    {
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
                    Lista.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio).transformed(QTransform().scale(-1,1)));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
                    //Lista.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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
                    Lista.push_back(QPixmap(DireccionArchivo));
                    //Lista.push_back(QPixmap(DireccionArchivo).scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio));
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

        EjecutarMovimientos();
    }
    else
    {
        EjecutarMovimientos();
    }
}

Tecla Jugador::TeclaPresionada(QKeyEvent *event)
{
    //Función que retorna una "Tecla" con el valor de la tecla presiona
    // Se verifica que no se esté ejecutando la animación de ataque
    Tecla Presionada=NULA;
    if(!Atacando)
    {
        // Se verifica cuál tecla se presiona
        switch (event->key())
        {
        case Qt::Key_Space:
            Presionada=Espacio;
            break;
        case Qt::Key_Up:
            Direccion=Arriba;
            _Direccion=Direccion;
            Presionada=Arriba;
            break;
        case Qt::Key_Down:
            Direccion=Abajo;
            _Direccion=Direccion;
            Presionada=Abajo;
            break;
        case Qt::Key_Right:
            Direccion=Derecha;
            _Direccion=Direccion;
            Presionada=Derecha;
            break;
        case Qt::Key_Left:
            Direccion=Izquierda;
            _Direccion=Direccion;
            Presionada=Izquierda;
            break;
        case Qt::Key_Escape:
            Presionada=Esc;
            Direccion=_Direccion;
            break;
        default:
            Direccion=_Direccion;
            break;
        }
    }
    return Presionada;
}

void Jugador::EjecutarMovimientos()
{
    if(!Atacando)
    {
        if(Estatico)
        {
            switch (Direccion)
            {
            case Derecha:
                if(FrameMovimiento>=ParadoDerecha.size())
                {
                    FrameMovimiento=0;
                }
                else
                {
                    setPixmap(ParadoDerecha[FrameMovimiento]);
                    FrameMovimiento++;
                }
                break;
            case Izquierda:
                if(FrameMovimiento>=ParadoIzquierda.size())
                {
                    FrameMovimiento=0;
                }
                else
                {
                    setPixmap(ParadoIzquierda[FrameMovimiento]);
                    FrameMovimiento++;
                }
                break;
            case Arriba:
                if(FrameMovimiento>=ParadoArriba.size())
                {
                    FrameMovimiento=0;
                }
                else
                {
                    setPixmap(ParadoArriba[FrameMovimiento]);
                    FrameMovimiento++;
                }
                break;
            case Abajo:
                if(FrameMovimiento>=ParadoAbajo.size())
                {
                    FrameMovimiento=0;
                }
                else
                {
                    setPixmap(ParadoAbajo[FrameMovimiento]);
                    FrameMovimiento++;
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
        case Derecha:
            if(FrameMovimiento>=CorrerDerecha.size())
            {
                FrameMovimiento=0;
            }
            else
            {
                setPixmap(CorrerDerecha[FrameMovimiento]);
                FrameMovimiento++;
            }
            break;
        case Izquierda:
            if(FrameMovimiento>=CorrerIzquierda.size())
            {
                FrameMovimiento=0;
            }
            else
            {
                setPixmap(CorrerIzquierda[FrameMovimiento]);
                FrameMovimiento++;
            }
            break;
        case Arriba:
            if(FrameMovimiento>=CorrerArriba.size())
            {
                FrameMovimiento=0;
            }
            else
            {
                setPixmap(CorrerArriba[FrameMovimiento]);
                FrameMovimiento++;
            }
            break;
        case Abajo:
            if(FrameMovimiento>=CorrerAbajo.size())
            {
                FrameMovimiento=0;
            }
            else
            {
                setPixmap(CorrerAbajo[FrameMovimiento]);
                FrameMovimiento++;
            }
            break;
        default:
            break;
        }

    }
    }
}

void Jugador::Ataque()
{
    TimerAtaque = new QTimer;
    Atacando=true;
    Animacion->stop();
    Delta->stop();

    TimerAtaque->start(20);
    connect(TimerAtaque, SIGNAL(timeout()), this, SLOT(EjecutarAtaque()));
}

void Jugador::EjecutarAtaque()
{
    switch (Direccion)
    {
    case Derecha:
        if(FrameMovimiento>=AtacarDerecha.size())
        {
            TimerAtaque->stop();
            FrameAtaque=0;
            FrameMovimiento=0;
            Atacando=false;
            FixAtaque=true;

            Direccion=_Direccion;

            Delta->start(1);
            Animacion->start(60);
        }
        else
        {
            setPos(PosX-65, PosY-58);
            setPixmap(AtacarDerecha[FrameMovimiento++]);
        }
        break;
    case Izquierda:
        if(FrameMovimiento>=AtacarIzquierda.size())
        {
            TimerAtaque->stop();
            FrameAtaque=0;
            FrameMovimiento=0;
            Atacando=false;
            FixAtaque=true;

            Direccion=_Direccion;

            Delta->start(1);
            Animacion->start(60);
        }
        else
        {
            setPos(PosX-65, PosY-58);
            setPixmap(AtacarIzquierda[FrameMovimiento++]);
        }
        break;
    case Arriba:
        if(FrameMovimiento>=AtacarArriba.size())
        {
            TimerAtaque->stop();
            FrameAtaque=0;
            FrameMovimiento=0;
            Atacando=false;
            FixAtaque=true;

            Direccion=_Direccion;

            Delta->start(1);
            Animacion->start(60);
        }
        else
        {
            setPos(PosX-65, PosY-58);
            setPixmap(AtacarArriba[FrameMovimiento++]);
        }
        break;
    case Abajo:
        if(FrameMovimiento>=AtacarAbajo.size())
        {
            TimerAtaque->stop();
            FrameAtaque=0;
            FrameMovimiento=0;
            Atacando=false;
            FixAtaque=true;

            Direccion=_Direccion;

            Delta->start(1);
            Animacion->start(60);
        }
        else
        {
            setPos(PosX-65, PosY-58);
            setPixmap(AtacarAbajo[FrameMovimiento++]);
        }
        break;
    default:
        break;
    }
}

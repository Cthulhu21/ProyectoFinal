#include "Jugador.h"
#include <math.h>
#include "Enemigo.h"
#include "NPC.h"
#include "ObjetoDinamico.h"

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
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        ParadoDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Parado Izquierda
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        ParadoIzquierda.push_back(QPixmap(DireccionArchivo));
    }
    //Parado Arriba
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ar";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        ParadoArriba.push_back(QPixmap(DireccionArchivo));
    }
    //Parado Abajo
    for(int i=1; i<11; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Esta_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        ParadoAbajo.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Derecha
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        CorrerDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Correr Izquierda
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        CorrerIzquierda.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Arriba
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Arr";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        CorrerArriba.push_back(QPixmap(DireccionArchivo));
    }
    //Correr Abajo
    for(int i=1; i<9; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/Correr_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        CorrerAbajo.push_back(QPixmap(DireccionArchivo));
    }
    //Ataque Derecha
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        AtacarDerecha.push_back(QPixmap(DireccionArchivo).transformed(QTransform().scale(-1,1)));
    }
    //Atacar Izquierda
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Iz";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        AtacarIzquierda.push_back(QPixmap(DireccionArchivo));
    }
    //Ataque Arriba
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Ar";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        AtacarArriba.push_back(QPixmap(DireccionArchivo));
    }
    //Ataque Abajo
    for(int i=1; i<43; i++)
    {
        std::string _DireccionArchivo=":/PersonajePrincipal/A_Ab";
        _DireccionArchivo+=(std::to_string(i));
        QString DireccionArchivo=QString::fromStdString(_DireccionArchivo);
        AtacarAbajo.push_back(QPixmap(DireccionArchivo));
    }
}

void Jugador::Pausar()
{
    Pausa=true;
    setOpacity(0.5);
    Delta->stop();
    Animacion->stop();
}

void Jugador::Despausar()
{
    Pausa=false;
    setOpacity(1);
    Delta->start(1);
    Animacion->start(60);
}

bool Jugador::GetAtacando()
{
    //Retorna si el jugador está atacando o no
    return Atacando;
}

void Jugador::Hurt(int _Hurt)
{
    //Hiere al jugador
    Vida-=_Hurt-Defensa*pow(2,TierDefensa);
}

void Jugador::AgregarAInventario(Objeto *_Objeto)
{
    //Agrega un Objeto al inventario del jugador
    //Y quita el objeto del suelo
    InventarioJugadores.AgregarObjeto(_Objeto);
}

void Jugador::Actualizar()
{
    Jugador1->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador1->setFocus();
    //Se verifica que no esté cambiando de mapa
    {

        if(PosY<0)
        {
            auto Temp=Game->MapaActual.Circundantes;
            int A=Game->MapaActual.Circundantes[0];
            Game->CambiarMapaActual(Game->Ma_Pas[A]);
            PosY=600;
        }
        else if(PosX>1400)
        {
            auto Temp=Game->MapaActual.Circundantes;
            int A=Game->MapaActual.Circundantes[1];
            Game->CambiarMapaActual(Game->Ma_Pas[A]);
            PosX=30;
        }
        else if(PosY>700)
        {
            auto Temp=Game->MapaActual.Circundantes;
            int A=Game->MapaActual.Circundantes[2];
            Game->CambiarMapaActual(Game->Ma_Pas[A]);
            PosY=30;
        }
        else if(PosX<0)
        {
            auto Temp=Game->MapaActual.Circundantes;
            int A=Game->MapaActual.Circundantes[3];
            Game->CambiarMapaActual(Game->Ma_Pas[A]);
            PosX=1300;
        }
    }
    if(Vida<=0)
    {
        //Se retorna al primer mapa
        Game->CambiarMapaActual(Game->Ma_Pas[0]);
        PosX=500;
        PosY=500;
    }
    else
    {
        // Se actualizan los datos de posicion y velocidad
        VectorVelocidad = sqrt((pow(VelocidadX,2)+pow(VelocidadY,2)));
        Angulo = atan2(VelocidadY,VelocidadX);

        PosX = PosX + VelocidadX*DeltaTiempo + ((AceleracionX*pow(DeltaTiempo,2))/2);
        PosY = PosY + VelocidadY*DeltaTiempo + ((AceleracionY*pow(DeltaTiempo,2))/2);

        VelocidadX = VelocidadX + AceleracionX*DeltaTiempo;
        VelocidadY = VelocidadY + AceleracionY*DeltaTiempo;

        AceleracionX = (ResistenciaAire*pow(VectorVelocidad,2))*-cos(Angulo);
        AceleracionY = (ResistenciaAire*pow(VectorVelocidad,2))*-sin(Angulo);

        // Determina velocidad mínima*
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
        Colisiones();
    }
}

void Jugador::Mover()
{
    //Le da velocidad al jugador dependiendo la tecla presionada
    if(!Pausa)
    {
        switch (Numero)
        {
        case Primero:
            if(!Atacando)
            {
                int PlusAceleracion=0, PlusVelocidad=100;
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
}

void Jugador::Colisiones()
{
    QList<QGraphicsItem*> Elementos=collidingItems();
    for(auto Elemento: Elementos)
    {
        if(typeid(*Elemento)==typeid (ObjetoDinamico))
        {
            Chocando=true;
        }
        else if((typeid (*Elemento)==typeid(NPC)) or
                (typeid(*Elemento)==typeid (QGraphicsPixmapItem)) or
                (typeid (*Elemento)==typeid(Enemigo)) or
                (typeid (*Elemento)==typeid(Jugador)))
        {
            Rebote();
        }
    }
    if(Elementos.size()==0)
    {
        Chocando=false;
    }
}

void Jugador::Rebote()
{
    switch (Direccion)
    {
    case Derecha:
        (Chocando==false)?Velocidad(-10):Velocidad(-2);
        break;
    case Izquierda:
        (Chocando==false)?Velocidad(10):Velocidad(2);
        break;
    case Arriba:
        (Chocando==false)?Velocidad(0,10):Velocidad(0,2);
        break;
    case Abajo:
        (Chocando==false)?Velocidad(0,-10):Velocidad(0,-2);
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
        if(!Pausa)
        {
            if(!Atacando)
                Ataque();
        }
        break;
    case Derecha:
    case Izquierda:
    case Arriba:
    case Abajo:
        if(!Pausa)
        Mover();
        break;
    case Esc:
        Game->MenuPausa();
        break;
    case I:
        InventarioJugadores.MostrarInventario();
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
    Actualizar();
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
    Tecla _Presionada=NULA;
    if(!Atacando)
    {
        // Se verifica cuál tecla se presiona
        switch (event->key())
        {
        case Qt::Key_Space:
            _Presionada=Espacio;
            break;
        case Qt::Key_Up:
            Direccion=Arriba;
            _Direccion=Direccion;
            _Presionada=Arriba;
            break;
        case Qt::Key_Down:
            Direccion=Abajo;
            _Direccion=Direccion;
            _Presionada=Abajo;
            break;
        case Qt::Key_Right:
            Direccion=Derecha;
            _Direccion=Direccion;
            _Presionada=Derecha;
            break;
        case Qt::Key_Left:
            Direccion=Izquierda;
            _Direccion=Direccion;
            _Presionada=Izquierda;
            break;
        case Qt::Key_Escape:
            _Presionada=Esc;
            Direccion=_Direccion;
            break;
        case Qt::Key_I:
            _Presionada=I;
            Direccion=_Direccion;
            break;
        case Qt::Key_Z:
            _Presionada=Z;
            Direccion=_Direccion;
            break;
        default:
            Direccion=_Direccion;
            break;
        }
    }
    Presionada=_Presionada;
    return _Presionada;
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
            setPixmap(AtacarAbajo[FrameMovimiento++]);
        }
        break;
    default:
        break;
    }
}

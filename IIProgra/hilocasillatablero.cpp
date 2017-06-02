#include "hilocasillatablero.h"

HiloCasillaTablero::HiloCasillaTablero()
{
    //Por ahora no hay espanta pajaros
    espantaArriba = nullptr;
    espantaIzquierda = nullptr;
    espantaAbajo = nullptr;
    espantaDerecha = nullptr;

    pausa = false;
    semilla = 0;

    posXGranjero = nullptr;
    posYGranjero = nullptr;
    //Plagas

    probabilidadAparicionCuervo = nullptr;
    probabilidadAparicionOveja = nullptr;
    probabilidadAparicionPlaga = nullptr;

    cantidadApareceCuervo = nullptr;
    cantidadApareceOveja = nullptr;

    tiempoApareceCuervo = nullptr;
    tiempoApareceOveja = nullptr;
    tiempoAparecePlaga = nullptr;



    hayCuervo = false;
    hayOveja = false;
    hayPlaga = false;

    tiempoComeCuervo = nullptr;
    tiempoComeOveja = nullptr;
    tiempoDestruccionPlaga = nullptr;

    frutosComeCuervo = nullptr;
    frutosComeOveja = nullptr;
    //ARBOL
    hayArbol = nullptr;
    cantidadFrutos = 0;

    crecimientoABB = nullptr;
    frutosCosechaABB = nullptr;
    cantSegCosechaABB = nullptr;

    crecimientoHeap = nullptr;
    frutosCosechaHeap = nullptr;
    cantSegCosechaHeap = nullptr;

    crecimientoAVL = nullptr;
    frutosCosechaAVL = nullptr;
    cantSegCosechaAVL = nullptr;

    crecimientoBonus = nullptr;
    frutosCosechaBonus = nullptr;
    cantSegCosechaBonus = nullptr;

    //FIN ARBOL

}

void HiloCasillaTablero::setInfo(QVector<QVector<QVector<int> > > *vectorArbolesGranja, int posXHilo, int posYHilo, int *posXGranjero, int *posYGranjero, int *probabilidadAparicionCuervo, int *cantidadApareceCuervo, int* tiempoApareceCuervo, int* frutosComeCuervo, int *tiempoComeCuervo, int *probabilidadAparicionOveja, int *cantidadApareceOveja, int *tiempoApareceOveja, int *frutosComeOveja, int *tiempoComeOveja, int *probabilidadAparicionPlaga, int* tiempoAparecePlaga, int *tiempoDestruccionPlaga, int *crecimientoABB, int *frutosCosechaABB, int *cantSegCosechaABB, int *crecimientoHeap, int *frutosCosechaHeap, int *cantSegCosechaHeap, int *crecimientoAVL, int *frutosCosechaAVL, int *cantSegCosechaAVL, int *crecimientoBonus, int *frutosCosechaBonus, int *cantSegCosechaBonus, int modificadorSemilla){
    punteroVectorArbolesGranja = vectorArbolesGranja;

    this->posXHilo = posXHilo;
    this->posYHilo = posYHilo;

    this->posXGranjero = posXGranjero;
    this->posYGranjero = posYGranjero;
    //Plagas
    this->tiempoComeCuervo = tiempoComeCuervo;
    this->tiempoComeOveja = tiempoComeOveja;
    this->tiempoDestruccionPlaga = tiempoDestruccionPlaga;

    this->cantidadCuervos = 0;
    this->cantidadOvejas = 0;
    this->cantidadFrutos = 0;
    //
    this->probabilidadAparicionCuervo = probabilidadAparicionCuervo;
    this->probabilidadAparicionOveja = probabilidadAparicionOveja;
    this->probabilidadAparicionPlaga = probabilidadAparicionPlaga;

    this->cantidadApareceCuervo = cantidadApareceCuervo;
    this->cantidadApareceOveja = cantidadApareceOveja;

    this->tiempoApareceCuervo = tiempoApareceCuervo;
    this->tiempoApareceOveja = tiempoApareceOveja;
    this->tiempoAparecePlaga = tiempoAparecePlaga;
    this->frutosComeCuervo = frutosComeCuervo;
    this->frutosComeOveja = frutosComeOveja;

    //ARBOL
    this->crecimientoABB = crecimientoABB;
    this->frutosCosechaABB = frutosCosechaABB;
    this->cantSegCosechaABB = cantSegCosechaABB;

    this->crecimientoHeap = crecimientoHeap;
    this->frutosCosechaHeap = frutosCosechaHeap;
    this->cantSegCosechaHeap = cantSegCosechaHeap;

    this->crecimientoAVL = crecimientoAVL;
    this->frutosCosechaAVL = frutosCosechaAVL;
    this->cantSegCosechaAVL = cantSegCosechaAVL;

    this->crecimientoBonus = crecimientoBonus;
    this->frutosCosechaBonus = frutosCosechaBonus;
    this->cantSegCosechaBonus = cantSegCosechaBonus;


    semilla = time(0) + modificadorSemilla;
}

void HiloCasillaTablero::setPunterosBooleanos(bool* espantaArriba, bool* espantaIzquierda, bool* espantaAbajo, bool* espantaDerecha){
    this->espantaArriba = espantaArriba;
    this->espantaIzquierda = espantaIzquierda;
    this->espantaAbajo = espantaAbajo;
    this->espantaDerecha = espantaDerecha;
}

void HiloCasillaTablero::run(){
    std::mt19937 generator(semilla); // Generador de numeros randoms cuya seed es igual a time(0)
    std::uniform_int_distribution<> distr(0, 100); // Distribuidor
    //precioFrutoABB = distr(generator);
    int contadorGenerarFrutos = 0;
    int contadorGenerarOvejas = 0, contadorComeOveja = 0;
    int contadorGenerarCuervos = 0, contadorComeCuervo = 0;
    int contadorGenerarPlaga = 0, contadorPlagaDestruirArbol = 0;

    QMutex mutex;
    while(true){
        if(pausa){
            msleep(500);
        }
        if ((*punteroVectorArbolesGranja)[posXHilo][posYHilo][0] != NoHayArbol){
            //Debo generar frutos pues hay un arbol
            switch ((*punteroVectorArbolesGranja)[posXHilo][posYHilo][0]){
            case ABB:
                if(contadorGenerarFrutos >= *cantSegCosechaABB){
                    contadorGenerarFrutos = 0;//Reseteo
                    mutex.lock();//[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                    (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] += *frutosCosechaABB;
                    mutex.unlock();
                    emit actualizarMercado();
                }
                break;
            case Heap:
                if(contadorGenerarFrutos >= *cantSegCosechaHeap){
                    contadorGenerarFrutos = 0;//Reseteo
                    mutex.lock();//[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                    (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] += *frutosCosechaABB;
                    mutex.unlock();
                    emit actualizarMercado();
                }
                break;
            case AVL:
                if(contadorGenerarFrutos >= *cantSegCosechaAVL){
                    contadorGenerarFrutos = 0;//Reseteo
                    mutex.lock();//[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                    (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] += *frutosCosechaABB;
                    mutex.unlock();
                    emit actualizarMercado();
                }
                break;
            case Bonus:
                if(contadorGenerarFrutos >= *cantSegCosechaBonus){
                    contadorGenerarFrutos = 0;//Reseteo
                    mutex.lock();//[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                    (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] += *frutosCosechaABB;
                    mutex.unlock();
                    emit actualizarMercado();
                }
                break;
            default:
                break;
            }

            if (*posXGranjero == posXHilo && *posYGranjero == posYHilo){//El granjero está sobre el hilo por lo que debo eliminar plagas
                if (cantidadCuervos > 0 || cantidadOvejas > 0 || hayPlaga){
                    cantidadCuervos = 0;
                    cantidadOvejas = 0;
                    if(hayPlaga){
                        //DEBO QUITAR LA PLAGA PERO TAMBIEN DEBO DESTRUIR SEGUN EL TIEMPO EN EL QUE ESTUVO EN EL ARBOL
                        hayPlaga = false;
                    }
                    emit espantarPlagas();
                }
            }
            else{//No está el granjero en la casilla
                //Debo ver si genero una nueva plaga
                if(!espantaCerca()){
                    if (*tiempoApareceCuervo <= contadorGenerarCuervos){
                        contadorGenerarCuervos = 0;
                        if(distr(generator) <= *probabilidadAparicionCuervo){
                            //Si debo crear un cuervo
                            cantidadCuervos += *cantidadApareceCuervo;
                            emit anadirCuervo();

                        }
                    }
                    if (*tiempoApareceOveja <= contadorGenerarOvejas){
                        contadorGenerarOvejas = 0;
                        if(distr(generator) <= *probabilidadAparicionOveja){
                            //Si debo de crear una oveja
                            cantidadOvejas += *cantidadApareceOveja;
                            emit anadirOveja();
                        }
                    }
                    if (*tiempoAparecePlaga == contadorGenerarPlaga){
                        contadorGenerarPlaga = 0;
                        if (distr(generator) <= *probabilidadAparicionPlaga && !hayPlaga){
                            //Si debo de añadir una plaga
                            hayPlaga = true;
                            emit anadirPlaga();
                        }
                    }
                }
                //Debo hacer que las plagas coman frutos
                if(contadorComeCuervo >= *tiempoComeCuervo){
                    contadorComeCuervo = 0;
                    int cantFrutos = (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3];
                    if(cantidadCuervos > 0 && cantFrutos > 0){
                        //Se pueden comer frutos
                        //[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                        cantFrutos -= (cantidadCuervos * (*frutosComeCuervo));
                        if(cantFrutos < 0){
                            mutex.lock();
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][5] += (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3];
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] = 0;
                            mutex.unlock();
                        }
                        else{
                            mutex.lock();
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][5] += (cantidadCuervos * (*frutosComeCuervo));
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] -= (cantidadCuervos * (*frutosComeCuervo));
                            mutex.unlock();
                        }
                        emit actualizarMercado();
                    }
                }
                if(contadorComeOveja >= *tiempoComeOveja){
                    contadorComeOveja = 0;
                    int cantFrutos = (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3];
                    if(cantidadOvejas > 0 && cantFrutos > 0){
                        //Se pueden comer frutos
                        //[[TIPO][UBICACION X][UBICACION Y][CANTIDAD FRUTOS][VENDIDOS][PERDIDOS]]
                        cantFrutos -= (cantidadOvejas * (*frutosComeOveja));
                        if(cantFrutos < 0){
                            mutex.lock();
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][5] += (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3];
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] = 0;
                            mutex.unlock();
                        }
                        else{
                            mutex.lock();
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][5] += (cantidadOvejas * (*frutosComeOveja));
                            (*punteroVectorArbolesGranja)[posXHilo][posYHilo][3] -= (cantidadOvejas * (*frutosComeOveja));
                            mutex.unlock();
                        }
                        emit actualizarMercado();
                    }
                }

                if(contadorPlagaDestruirArbol <= *tiempoDestruccionPlaga){
                    contadorPlagaDestruirArbol = 0;
                    //DESTRUIR ARBOL
                }

            }
        }
        //NO HAY ARBOL ENTONCES LA CASILLA NO HACE NADA
        msleep(1000);//1 Segundo
        contadorGenerarFrutos += 1000;
        contadorGenerarOvejas += 1000;
        contadorComeOveja += 1000;
        contadorGenerarCuervos += 1000;
        contadorComeCuervo += 1000;
        contadorGenerarPlaga += 1000;
        contadorPlagaDestruirArbol += 1000;
        //Los contadores se suman los segundos en milisegundos. 1 = 1000
    }

}

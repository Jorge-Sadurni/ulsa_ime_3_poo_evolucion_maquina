#include "Pulidora.h"
#include <iostream>

Pulidora::Pulidora(const std::string &nombre) : Maquina(nombre) {}

int Pulidora::tiempoCicloSeg() const
{
    return 30;
}

void Pulidora::procesar()
{
    std::cout << "Puliendo Pieza\n";
    registrarPieza();
    agregarTiempo(tiempoCicloSeg());
}

#include "InspeccionVisual.h"

#include <iostream>

namespace planta
{

    InspeccionVisual::InspeccionVisual(const std::string &nombre) : Maquina(nombre) {}

    int InspeccionVisual::tiempoCicloSeg() const
    {
        return 15;
    }

    void InspeccionVisual::ejecutarCiclo()
    {
        std::cout << "Inspeccionando Pieza\n";
    }
} // namespace planta
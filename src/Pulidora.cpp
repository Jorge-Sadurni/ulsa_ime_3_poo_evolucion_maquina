#include "Pulidora.h"
#include <iostream>

namespace planta
{

    Pulidora::Pulidora(const std::string &nombre) : Maquina(nombre) {}

    int Pulidora::tiempoCicloSeg() const
    {
        return 30;
    }

    void Pulidora::ejecutarCiclo()
    {

        std::cout << "Puliendo Pieza\n";
    }

} // namespace planta

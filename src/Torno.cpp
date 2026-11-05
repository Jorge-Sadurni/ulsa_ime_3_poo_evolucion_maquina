#include "Torno.h"

#include <iostream>

namespace planta
{

    Torno::Torno(const std::string &nombre) : Maquina(nombre), husillo(3000.0) {}

    void Torno::ejecutarCiclo()
    {

        std::cout << "toreneando Pieza a 1200 rpm\n";
    }

    int Torno::tiempoCicloSeg() const
    {
        return 45;
    }
} // namespace planta

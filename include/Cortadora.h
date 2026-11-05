#ifndef CORTADORA_H
#define CORTADORA_H

#include "Maquina.h"

namespace planta
{

    class Cortadora : public Maquina
    {
    public:
        explicit Cortadora(const std::string &nombre);

        void ejecutarCiclo() override;
        int tiempoCicloSeg() const override;
    };

} // namespace planta

#endif
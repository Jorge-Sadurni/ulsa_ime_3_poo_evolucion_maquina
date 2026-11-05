#ifndef FRESADORA_H
#define FRESADORA_H

#include "Maquina.h"

namespace planta
{

    class Fresadora : public Maquina
    {
    public:
        explicit Fresadora(const std::string &nombre);

        int tiempoCicloSeg() const override;

    private:
        void ejecutarCiclo() override;
    };

} // namespace planta

#endif
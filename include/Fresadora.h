#ifndef FRESADORA_H
#define FRESADORA_H

#include "Maquina.h"

class Fresadora : public Maquina
{
public:
    explicit Fresadora(const std::string &nombre);

    int tiempoCicloSeg() const override;

private:
    void ejecutarCiclo() override;
};

#endif
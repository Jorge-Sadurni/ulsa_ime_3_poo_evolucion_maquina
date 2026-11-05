#ifndef INSPECCIONVISUAL_H
#define INSPECCIONVISUAL_H

#include "Maquina.h"

class InspeccionVisual : public Maquina
{
public:
    explicit InspeccionVisual(const std::string &nombre);

    int tiempoCicloSeg() const override;

private:
    void ejecutarCiclo() override;
};

#endif
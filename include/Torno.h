#ifndef TORNO_H
#define TORNO_H

#include "Maquina.h"
#include "Motor.h"

class Torno : public Maquina
{
private:
    Motor husillo;

public:
    explicit Torno(const std::string &nombre);

    int tiempoCicloSeg() const override;

private:
    void ejecutarCiclo() override;
};

#endif
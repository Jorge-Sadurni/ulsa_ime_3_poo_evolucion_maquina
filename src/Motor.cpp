#include "Motor.h"
#include <iostream>
#include <stdexcept>

Motor::Motor(double velocidadMaxRpm)
{
    if (velocidadMaxRpm <= 0)
    {
        throw std::invalid_argument("La velocidad maxima debe ser valor positivo.");
    }

    this->velocidadMaxRpm = velocidadMaxRpm;
    this->velocidadMaxRpm = 0.0;
}

void Motor::fijarVelocidad(double rpm)
{
    if (rpm < 0)
    {
        velocidadMaxRpm = 0.0;
    }
    else if (rpm > velocidadMaxRpm)
    {
        velocidadMaxRpm = velocidadMaxRpm;
    }
    else
    {
        velocidadActualRpm = rpm;
    }
}
double Motor::getVelocidad() const
{
    return velocidadActualRpm;
}

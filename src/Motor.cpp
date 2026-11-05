#include "Motor.h"
#include <iostream>
#include <stdexcept>

namespace planta
{

    Motor::Motor(double velocidadMaxRpm)
    {
        if (velocidadMaxRpm <= 0)
        {
            throw std::invalid_argument("La velocidad maxima debe ser valor positivo.");
        }

        this->velocidadMaxRpm = velocidadMaxRpm;
        this->velocidadActualRpm = 0.0;
    }

    void Motor::fijarVelocidad(double rpm)
    {
        if (rpm < 0)
        {
            velocidadActualRpm = 0.0;
        }
        else if (rpm > velocidadMaxRpm)
        {
            velocidadActualRpm = velocidadMaxRpm;
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

} // namespace planta
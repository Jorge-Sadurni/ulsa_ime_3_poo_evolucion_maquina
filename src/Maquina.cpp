#include "Maquina.h"
#include <iostream>
#include <stdexcept>

Maquina::Maquina(const std::string &nombre)
    : nombre(nombre), piezasProcesadas(0), tiempoTrabajadoSeg(0)

{
    if (nombre.empty())
    {
        throw std::invalid_argument("El nombre no puede estar vacio");
    }
}

void Maquina::registrarPieza()
{
    piezasProcesadas++;
}

void Maquina::agregarTiempo(int segundos)
{
    if (segundos <= 0)
    {
        throw std::invalid_argument("Los segundos deben ser mayores que cero");
    }
    tiempoTrabajadoSeg += segundos;
}

void Maquina::mostrarEstado() const
{
    std::cout << nombre << " | piezas: " << piezasProcesadas
              << " | tiempo: " << getTiempoTrabajadoSeg() << " s"
              << " | capacidad: " << capacidadPorHora() << " pzas/h\n";
}

int Maquina::tiempoCicloValidado() const
{
    int tiempo = tiempoCicloSeg();
    if (tiempo <= 0)
    {
        throw std::logic_error(nombre + ": tiempoCicloSeg() debe ser mayor a 0");
    }
    return tiempo;
}

void Maquina::procesar()
{
    int tiempo = tiempoCicloValidado();
    ejecutarCiclo();
    registrarPieza();
    agregarTiempo(tiempo);
}

double Maquina::capacidadPorHora() const
{
    int tiempo = tiempoCicloValidado();
    return 3600.0 / tiempo;
}

const std::string &Maquina::getNombre() const { return nombre; }
int Maquina::getPiezasProcesadas() const { return piezasProcesadas; }
int Maquina::getTiempoTrabajadoSeg() const { return tiempoTrabajadoSeg; }

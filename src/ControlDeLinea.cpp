#include "ControlDeLinea.h"

#include <iostream>

namespace planta
{

    bool ControlDeLinea::agregar(Maquina *m)
    {
        if (m == nullptr)
            return false;

        for (const auto &maquina : maquinas)
        {
            if (maquina == m)
            {
                return false;
            }
        }

        maquinas.push_back(m);
        return true;
    }

    void ControlDeLinea::ejecutarTurno(int ciclos)
    {
        for (Maquina *m : maquinas)
        {
            for (int i = 0; i < ciclos; i++)
            {
                m->procesar();
            }
        }
    }

    void ControlDeLinea::imprimirReporte() const
    {
        if (maquinas.empty())
        {
            std::cout << " La linea no tiene maquinas\n";
            return;
        }

        std::cout << "--- Reporte de la linea ---\n";
        int totalPiezasGlobal = 0;

        for (const Maquina *m : maquinas)
        {
            m->mostrarEstado();
        }
        std::cout << " Total de piezas producidas en la linea: " << totalPiezasGlobal << "\n";
    }
} // namespace planta
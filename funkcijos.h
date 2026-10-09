#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <random>
#include "studentas.h"

struct MatavimoLaikai {
    double nuskaitymas = 0;
    double grupavimas = 0;
    double rusiavimas = 0;
    double isvedimas = 0;
};

void generuoti_faila(
    std::string failo_pavadinimas,
    int kiek_studentu,
    std::mt19937 &gen
);

void generuoti_visus_failus(std::mt19937 &gen);

MatavimoLaikai apdoroti_faila(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
);

void apdoroti_visus_failus(int pakartojimu_kiekis);

#endif

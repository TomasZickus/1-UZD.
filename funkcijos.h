#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <random>
#include "studentas.h"

// Numatytoji rūšiavimo tvarka – pagal galutinį balą mažėjančiai
constexpr int RUSIAVIMAS_PAGAL_REZULTATA = 3;

// Failo apdorojimo matavimo laikai
struct MatavimoLaikai {
    double nuskaitymas = 0;
    double grupavimas = 0;
    double rusiavimas = 0;
    double isvedimas = 0;
};

// Failų generavimas
void generuoti_faila(
    const std::string& failo_pavadinimas,
    int kiek_studentu,
    std::mt19937& gen
);

void generuoti_visus_failus(std::mt19937& gen);

// 1 strategija – vector
MatavimoLaikai apdoroti_faila(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras = RUSIAVIMAS_PAGAL_REZULTATA
);

// 1 strategija – list
MatavimoLaikai apdoroti_faila_list(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras = RUSIAVIMAS_PAGAL_REZULTATA
);

// 2 strategija – vector
MatavimoLaikai apdoroti_faila_2strategija(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras = RUSIAVIMAS_PAGAL_REZULTATA
);

// 2 strategija – list
MatavimoLaikai apdoroti_faila_list_2strategija(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras = RUSIAVIMAS_PAGAL_REZULTATA
);

#endif

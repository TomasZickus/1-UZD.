#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <random>
#include "studentas.h"

void generuoti_faila(std::string failo_pavadinimas, int kiek_studentu, std::mt19937 &gen);
void generuoti_visus_failus(std::mt19937 &gen);
void apdoroti_faila(const std::string& failo_pavadinimas,
                    const std::string& vargsiuku_failas,
                    const std::string& kietiaku_failas);
void apdoroti_visus_failus();

#endif
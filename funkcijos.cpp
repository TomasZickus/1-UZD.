#include "funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

void generuoti_faila(std::string failo_pavadinimas, int kiek_studentu, std::mt19937 &gen) {
    std::ofstream fr(failo_pavadinimas);

    if (!fr) {
        cout << "Nepavyko sukurti failo " << failo_pavadinimas << "!\n";
        return;
    }

    std::uniform_int_distribution<int> dist(1, 10);

    fr << left << setw(15) << "Vardas"
       << setw(15) << "Pavarde"
       << setw(6) << "ND1"
       << setw(6) << "ND2"
       << setw(6) << "ND3"
       << setw(6) << "Egz" << "\n";

    for (int i = 1; i <= kiek_studentu; i++)
        fr << left << setw(15) << ("Vardas" + std::to_string(i))
           << setw(15) << ("Pavarde" + std::to_string(i))
           << setw(6) << dist(gen)
           << setw(6) << dist(gen)
           << setw(6) << dist(gen)
           << setw(6) << dist(gen) << "\n";

    fr.close();
    cout << "Sugeneruotas failas: " << failo_pavadinimas << "\n";
}

void generuoti_visus_failus(std::mt19937 &gen) {
    generuoti_faila("studentai_1k.txt", 1000, gen);
    generuoti_faila("studentai_10k.txt", 10000, gen);
    generuoti_faila("studentai_100k.txt", 100000, gen);
    generuoti_faila("studentai_1m.txt", 1000000, gen);
    generuoti_faila("studentai_10m.txt", 10000000, gen);
}

void apdoroti_faila(const std::string& failo_pavadinimas,
                    const std::string& vargsiuku_failas,
                    const std::string& kietiaku_failas) {

    std::ifstream fd(failo_pavadinimas);

    if (!fd) {
        cout << "Nepavyko atidaryti failo " << failo_pavadinimas << "!\n";
        return;
    }

    std::vector<studentas> vargsiukai, kietiakai;
    std::string eilute;

    std::getline(fd, eilute);

    while (std::getline(fd, eilute)) {
        if (eilute.empty()) continue;

        std::istringstream iss(eilute);
        studentas A;
        int pazymys;

        if (iss >> A.var >> A.pav) {
            while (iss >> pazymys)
                A.paz.push_back(pazymys);

            A.egz = A.paz.back();
            A.paz.pop_back();

            paskaiciuoti_rezultatus(A);

            if (A.rez < 5.0)
                vargsiukai.push_back(A);
            else
                kietiakai.push_back(A);
        }
    }

    fd.close();

    std::ofstream fr_vargsiukai(vargsiuku_failas);
    std::ofstream fr_kietiakai(kietiaku_failas);

    if (!fr_vargsiukai || !fr_kietiakai) {
        cout << "Nepavyko sukurti rezultatu failu!\n";
        return;
    }

    for (std::ofstream* fr : {&fr_vargsiukai, &fr_kietiakai}) {
        *fr << left << setw(15) << "Vardas"
            << setw(15) << "Pavarde"
            << setw(17) << "Galutinis (Vid.)"
            << setw(17) << "Galutinis (Med.)" << "\n";
    }

    for (const studentas& A : vargsiukai)
        fr_vargsiukai << left << setw(15) << A.var
                      << setw(15) << A.pav
                      << setw(17) << fixed << setprecision(2) << A.rez
                      << setw(17) << A.rez_med << "\n";

    for (const studentas& A : kietiakai)
        fr_kietiakai << left << setw(15) << A.var
                     << setw(15) << A.pav
                     << setw(17) << fixed << setprecision(2) << A.rez
                     << setw(17) << A.rez_med << "\n";
}

void apdoroti_visus_failus() {
    apdoroti_faila("studentai_1k.txt", "vargsiukai_1k.txt", "kietiakai_1k.txt");
    apdoroti_faila("studentai_10k.txt", "vargsiukai_10k.txt", "kietiakai_10k.txt");
    apdoroti_faila("studentai_100k.txt", "vargsiukai_100k.txt", "kietiakai_100k.txt");
    apdoroti_faila("studentai_1m.txt", "vargsiukai_1m.txt", "kietiakai_1m.txt");
    apdoroti_faila("studentai_10m.txt", "vargsiukai_10m.txt", "kietiakai_10m.txt");
}
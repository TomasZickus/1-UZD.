#include "funkcijos.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <limits>
#include <vector>

using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

void generuoti_faila(
    std::string failo_pavadinimas,
    int kiek_studentu,
    std::mt19937 &gen
) {
    auto pradzia = std::chrono::steady_clock::now();

    std::ofstream fr(failo_pavadinimas);

    if (!fr) {
        cout << "Nepavyko sukurti failo "
             << failo_pavadinimas << "!\n";
        return;
    }

    std::uniform_int_distribution<int> dist(1, 10);

    fr << left << setw(15) << "Vardas"
       << setw(15) << "Pavarde"
       << setw(6) << "ND1"
       << setw(6) << "ND2"
       << setw(6) << "ND3"
       << setw(6) << "Egz" << "\n";

    for (int i = 1; i <= kiek_studentu; i++) {
        fr << left << setw(15) << ("Vardas" + std::to_string(i))
           << setw(15) << ("Pavarde" + std::to_string(i))
           << setw(6) << dist(gen)
           << setw(6) << dist(gen)
           << setw(6) << dist(gen)
           << setw(6) << dist(gen) << "\n";
    }

    fr.close();

    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    cout << "Sugeneruotas failas: " << failo_pavadinimas
         << " | Kurimo laikas: " << trukme.count() << " s\n";
}

void generuoti_visus_failus(std::mt19937 &gen) {
    generuoti_faila("studentai_1k.txt", 1000, gen);
    generuoti_faila("studentai_10k.txt", 10000, gen);
    generuoti_faila("studentai_100k.txt", 100000, gen);
    generuoti_faila("studentai_1m.txt", 1000000, gen);
    generuoti_faila("studentai_10m.txt", 10000000, gen);
}

MatavimoLaikai apdoroti_faila(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
) {
    using laikrodis = std::chrono::steady_clock;

    MatavimoLaikai laikai;

    // 1. Duomenu nuskaitymas ir rezultatu skaiciavimas
    auto pradzia = laikrodis::now();

    std::ifstream fd(failo_pavadinimas);

    if (!fd) {
        cout << "Nepavyko atidaryti failo "
             << failo_pavadinimas << "!\n";
        return laikai;
    }

    std::vector<studentas> studentai;
    std::string eilute;

    std::getline(fd, eilute); // Praleidziama antraste

    while (std::getline(fd, eilute)) {
        if (eilute.empty()) continue;

        std::istringstream iss(eilute);
        studentas A;
        int pazymys;

        if (iss >> A.var >> A.pav) {
            while (iss >> pazymys)
                A.paz.push_back(pazymys);

            if (A.paz.empty()) {
                A.egz = 0;
            }
            else {
                A.egz = A.paz.back();
                A.paz.pop_back();
            }

            paskaiciuoti_rezultatus(A);
            studentai.push_back(A);
        }
    }

    fd.close();

    auto pabaiga = laikrodis::now();

    laikai.nuskaitymas =
        std::chrono::duration<double>(pabaiga - pradzia).count();

    // 2. Studentu grupavimas
    pradzia = laikrodis::now();

    std::vector<studentas> vargsiukai, kietiakai;

    for (const studentas& A : studentai) {
        if (A.rez < 5.0)
            vargsiukai.push_back(A);
        else
            kietiakai.push_back(A);
    }

    pabaiga = laikrodis::now();

    laikai.grupavimas =
        std::chrono::duration<double>(pabaiga - pradzia).count();

    // 3. Studentu rusiavimas
    pradzia = laikrodis::now();

    auto pagal_varda = [](const studentas& a, const studentas& b) {
        return a.var < b.var;
    };

    auto pagal_pavarde = [](const studentas& a, const studentas& b) {
        return a.pav < b.pav;
    };

    auto pagal_rezultata = [](const studentas& a, const studentas& b) {
        return a.rez > b.rez;
    };

    if (rusiavimo_parametras == 1) {
        std::sort(vargsiukai.begin(), vargsiukai.end(), pagal_varda);
        std::sort(kietiakai.begin(), kietiakai.end(), pagal_varda);
    }
    else if (rusiavimo_parametras == 2) {
        std::sort(vargsiukai.begin(), vargsiukai.end(), pagal_pavarde);
        std::sort(kietiakai.begin(), kietiakai.end(), pagal_pavarde);
    }
    else if (rusiavimo_parametras == 3) {
        std::sort(vargsiukai.begin(), vargsiukai.end(), pagal_rezultata);
        std::sort(kietiakai.begin(), kietiakai.end(), pagal_rezultata);
    }

    pabaiga = laikrodis::now();

    laikai.rusiavimas =
        std::chrono::duration<double>(pabaiga - pradzia).count();

    // 4. Rezultatu isvedimas i failus
    pradzia = laikrodis::now();

    std::ofstream fr_vargsiukai(vargsiuku_failas);
    std::ofstream fr_kietiakai(kietiaku_failas);

    if (!fr_vargsiukai || !fr_kietiakai) {
        cout << "Nepavyko sukurti rezultatu failu!\n";
        return laikai;
    }

    for (std::ofstream* fr : {&fr_vargsiukai, &fr_kietiakai}) {
        *fr << left << setw(15) << "Vardas"
            << setw(15) << "Pavarde"
            << setw(17) << "Galutinis (Vid.)"
            << setw(17) << "Galutinis (Med.)" << "\n";
    }

    for (const studentas& A : vargsiukai) {
        fr_vargsiukai << left << setw(15) << A.var
                      << setw(15) << A.pav
                      << setw(17) << fixed << setprecision(2) << A.rez
                      << setw(17) << A.rez_med << "\n";
    }

    for (const studentas& A : kietiakai) {
        fr_kietiakai << left << setw(15) << A.var
                     << setw(15) << A.pav
                     << setw(17) << fixed << setprecision(2) << A.rez
                     << setw(17) << A.rez_med << "\n";
    }

    fr_vargsiukai.close();
    fr_kietiakai.close();

    pabaiga = laikrodis::now();

    laikai.isvedimas =
        std::chrono::duration<double>(pabaiga - pradzia).count();

    return laikai;
}

void apdoroti_visus_failus(int pakartojimu_kiekis) {
    int pasirinkimas;

    cout << "\nPasirinkite studentu rusiavimo buda:\n";
    cout << "1 - Pagal varda (A-Z)\n";
    cout << "2 - Pagal pavarde (A-Z)\n";
    cout << "3 - Pagal galutini bala (nuo didziausio iki maziausio)\n";
    cout << "Jusu pasirinkimas: ";

    while (!(std::cin >> pasirinkimas) ||
           pasirinkimas < 1 || pasirinkimas > 3) {
        cout << "Neteisingas pasirinkimas. Iveskite 1, 2 arba 3: ";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }

    struct FailoInformacija {
        std::string pavadinimas;
        std::string vargsiuku;
        std::string kietiaku;
    };

    const std::vector<FailoInformacija> failai = {
        {"studentai_1k.txt", "vargsiukai_1k.txt", "kietiakai_1k.txt"},
        {"studentai_10k.txt", "vargsiukai_10k.txt", "kietiakai_10k.txt"},
        {"studentai_100k.txt", "vargsiukai_100k.txt", "kietiakai_100k.txt"},
        {"studentai_1m.txt", "vargsiukai_1m.txt", "kietiakai_1m.txt"},
        {"studentai_10m.txt", "vargsiukai_10m.txt", "kietiakai_10m.txt"}
    };

    cout << "\nKiekvienam failui atliekama "
         << pakartojimu_kiekis << " band.";

    if (pakartojimu_kiekis > 1)
        cout << " Skaiciuojami vidurkiai.";

    cout << "\n";

    for (const auto& failas : failai) {
        MatavimoLaikai suma;

        cout << "\nFailas: " << failas.pavadinimas << "\n";

        for (int i = 1; i <= pakartojimu_kiekis; i++) {
            MatavimoLaikai laikai = apdoroti_faila(
                failas.pavadinimas,
                failas.vargsiuku,
                failas.kietiaku,
                pasirinkimas
            );

            suma.nuskaitymas += laikai.nuskaitymas;
            suma.grupavimas += laikai.grupavimas;
            suma.rusiavimas += laikai.rusiavimas;
            suma.isvedimas += laikai.isvedimas;

            if (pakartojimu_kiekis > 1) {
                cout << "  Bandymas " << i
                     << ": nuskaitymas = " << laikai.nuskaitymas
                     << " s, grupavimas = " << laikai.grupavimas
                     << " s, rusiavimas = " << laikai.rusiavimas
                     << " s, isvedimas = " << laikai.isvedimas
                     << " s\n";
            }
        }

        double n = pakartojimu_kiekis;

        double nuskaitymas = suma.nuskaitymas / n;
        double grupavimas = suma.grupavimas / n;
        double rusiavimas = suma.rusiavimas / n;
        double isvedimas = suma.isvedimas / n;

        double bendras_laikas =
            nuskaitymas + grupavimas + rusiavimas + isvedimas;

        cout << fixed << setprecision(6);
        cout << "Vidutinis nuskaitymo laikas: "
             << nuskaitymas << " s\n";
        cout << "Vidutinis grupavimo laikas: "
             << grupavimas << " s\n";
        cout << "Vidutinis rusiavimo laikas: "
             << rusiavimas << " s\n";
        cout << "Vidutinis isvedimo laikas: "
             << isvedimas << " s\n";
        cout << "Bendras vidutinis laikas: "
             << bendras_laikas << " s\n";
    }
}

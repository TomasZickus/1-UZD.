#include "funkcijos.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <list>
#include <type_traits>
#include <utility>

using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;


// Pagal naudojamą konteinerį parenkamas tinkamas rūšiavimo metodas.
template <typename Konteineris, typename Palyginimas>
void rusiuoti_konteineri(
    Konteineris& konteineris,
    Palyginimas palyginimas
) {
    if constexpr (
        std::is_same_v<Konteineris, std::list<studentas>>
    ) {
        konteineris.sort(palyginimas);
    }
    else {
        std::sort(
            konteineris.begin(),
            konteineris.end(),
            palyginimas
        );
    }
}


// Sugeneruoja vieną studentų failą.
void generuoti_faila(
    const std::string& failo_pavadinimas,
    int kiek_studentu,
    std::mt19937& gen
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


// Sugeneruoja visus penkis studentų failus.
void generuoti_visus_failus(std::mt19937& gen) {
    generuoti_faila("studentai_1k.txt", 1000, gen);
    generuoti_faila("studentai_10k.txt", 10000, gen);
    generuoti_faila("studentai_100k.txt", 100000, gen);
    generuoti_faila("studentai_1m.txt", 1000000, gen);
    generuoti_faila("studentai_10m.txt", 10000000, gen);
}


// Bendra failo apdorojimo realizacija.
// Konteinerio tipas ir grupavimo strategija parenkami
// pagal šablono parametrą ir funkcijos argumentą.
template <typename Konteineris>
MatavimoLaikai apdoroti_faila_impl(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras,
    bool antra_strategija
) {
    using laikrodis = std::chrono::steady_clock;

    MatavimoLaikai laikai;

    // 1. Duomenų nuskaitymas ir rezultatų skaičiavimas

    auto pradzia = laikrodis::now();

    std::ifstream fd(failo_pavadinimas);

    if (!fd) {
        cout << "Nepavyko atidaryti failo "
             << failo_pavadinimas << "!\n";
        return laikai;
    }

    Konteineris studentai;
    std::string eilute;

    std::getline(fd, eilute); // Praleidžiama antraštė

    while (std::getline(fd, eilute)) {
        if (eilute.empty())
            continue;

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


    // 2. Studentų grupavimas

    pradzia = laikrodis::now();

    Konteineris vargsiukai, kietiakai;

    if (!antra_strategija) {

        // 1 strategija:
        // Studentai kopijuojami į du naujus konteinerius.

        for (const studentas& A : studentai) {
            if (A.rez < 5.0)
                vargsiukai.push_back(A);
            else
                kietiakai.push_back(A);
        }
    }
    else {

        // 2 strategija:
        // Vargšiukai perkeliami į naują konteinerį,
        // o iš pradinio studentai konteinerio ištrinami.

        auto it = studentai.begin();

        while (it != studentai.end()) {
            if (it->rez < 5.0) {
                vargsiukai.push_back(std::move(*it));
                it = studentai.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Nustatoma, kuriame konteineryje liko kietiakai.
    Konteineris& kietiaku_grupe =
        antra_strategija ? studentai : kietiakai;

    pabaiga = laikrodis::now();

    laikai.grupavimas =
        std::chrono::duration<double>(pabaiga - pradzia).count();


    // 3. Studentų rūšiavimas

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
        rusiuoti_konteineri(vargsiukai, pagal_varda);
        rusiuoti_konteineri(kietiaku_grupe, pagal_varda);
    }
    else if (rusiavimo_parametras == 2) {
        rusiuoti_konteineri(vargsiukai, pagal_pavarde);
        rusiuoti_konteineri(kietiaku_grupe, pagal_pavarde);
    }
    else if (rusiavimo_parametras == 3) {
        rusiuoti_konteineri(vargsiukai, pagal_rezultata);
        rusiuoti_konteineri(kietiaku_grupe, pagal_rezultata);
    }

    pabaiga = laikrodis::now();

    laikai.rusiavimas =
        std::chrono::duration<double>(pabaiga - pradzia).count();


    // 4. Rezultatų išvedimas į failus

    pradzia = laikrodis::now();

    std::ofstream fr_vargsiukai(vargsiuku_failas);
    std::ofstream fr_kietiakai(kietiaku_failas);

    if (!fr_vargsiukai || !fr_kietiakai) {
        cout << "Nepavyko sukurti rezultatu failu!\n";
        return laikai;
    }

    // Antraštės
    for (std::ofstream* fr : {&fr_vargsiukai, &fr_kietiakai}) {
        *fr << left << setw(15) << "Vardas"
            << setw(15) << "Pavarde"
            << setw(17) << "Galutinis (Vid.)"
            << setw(17) << "Galutinis (Med.)" << "\n";
    }

    // Vargšiukų išvedimas
    for (const studentas& A : vargsiukai) {
        fr_vargsiukai << left << setw(15) << A.var
                      << setw(15) << A.pav
                      << setw(17) << fixed << setprecision(2) << A.rez
                      << setw(17) << A.rez_med << "\n";
    }

    // Kietiakų išvedimas
    for (const studentas& A : kietiaku_grupe) {
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


// ==================================================
// 1 STRATEGIJA
// ==================================================

// 1 strategija – vector

MatavimoLaikai apdoroti_faila(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
) {
    return apdoroti_faila_impl<std::vector<studentas>>(
        failo_pavadinimas,
        vargsiuku_failas,
        kietiaku_failas,
        rusiavimo_parametras,
        false
    );
}


// 1 strategija – list

MatavimoLaikai apdoroti_faila_list(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
) {
    return apdoroti_faila_impl<std::list<studentas>>(
        failo_pavadinimas,
        vargsiuku_failas,
        kietiaku_failas,
        rusiavimo_parametras,
        false
    );
}


// ==================================================
// 2 STRATEGIJA
// ==================================================

// 2 strategija – vector

MatavimoLaikai apdoroti_faila_2strategija(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
) {
    return apdoroti_faila_impl<std::vector<studentas>>(
        failo_pavadinimas,
        vargsiuku_failas,
        kietiaku_failas,
        rusiavimo_parametras,
        true
    );
}


// 2 strategija – list

MatavimoLaikai apdoroti_faila_list_2strategija(
    const std::string& failo_pavadinimas,
    const std::string& vargsiuku_failas,
    const std::string& kietiaku_failas,
    int rusiavimo_parametras
) {
    return apdoroti_faila_impl<std::list<studentas>>(
        failo_pavadinimas,
        vargsiuku_failas,
        kietiaku_failas,
        rusiavimo_parametras,
        true
    );
}

#include "funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <limits>

using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

void generuoti_faila(std::string failo_pavadinimas, int kiek_studentu, std::mt19937 &gen) {
    auto pradzia = std::chrono::high_resolution_clock::now();

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

    auto pabaiga = std::chrono::high_resolution_clock::now();
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

void apdoroti_faila(const std::string& failo_pavadinimas,
                    const std::string& vargsiuku_failas,
                    const std::string& kietiaku_failas,
                    int rusiavimo_parametras) {

    // 1. Duomenu nuskaitymas
    auto pradzia = std::chrono::high_resolution_clock::now();

    std::ifstream fd(failo_pavadinimas);

    if (!fd) {
        cout << "Nepavyko atidaryti failo " << failo_pavadinimas << "!\n";
        return;
    }

    std::vector<studentas> studentai;
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

            if (A.paz.empty())
                A.egz = 0;
            else {
                A.egz = A.paz.back();
                A.paz.pop_back();
            }

            paskaiciuoti_rezultatus(A);
            studentai.push_back(A);
        }
    }

    fd.close();

    auto pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> nuskaitymo_laikas = pabaiga - pradzia;

    // 2. Studentu suskirstymas i dvi kategorijas
    pradzia = std::chrono::high_resolution_clock::now();

    std::vector<studentas> vargsiukai, kietiakai;

    for (const studentas& A : studentai) {
        if (A.rez < 5.0)
            vargsiukai.push_back(A);
        else
            kietiakai.push_back(A);
    }

    pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> grupavimo_laikas = pabaiga - pradzia;

    // 3. Studentu rusiavimas pagal parametrus
    pradzia = std::chrono::high_resolution_clock::now();

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

    pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> rusiavimo_laikas = pabaiga - pradzia;

    // 4. Rezultatu isvedimas i du failus
    pradzia = std::chrono::high_resolution_clock::now();

    std::ofstream fr_vargsiukai(vargsiuku_failas);
    std::ofstream fr_kietiakai(kietiaku_failas);

    if (!fr_vargsiukai || !fr_kietiakai) {
        cout << "Nepavyko sukurti rezultatu failu!\n";
        return;
    }

    for (std::ofstream* fr : {&fr_vargsiukai, &fr_kietiakai})
        *fr << left << setw(15) << "Vardas"
            << setw(15) << "Pavarde"
            << setw(17) << "Galutinis (Vid.)"
            << setw(17) << "Galutinis (Med.)" << "\n";

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

    fr_vargsiukai.close();
    fr_kietiakai.close();

    pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> isvedimo_laikas = pabaiga - pradzia;

    cout << "\nFailas: " << failo_pavadinimas << "\n";
    cout << "Sio failo nuskaitymo laikas: " << nuskaitymo_laikas.count() << " s\n";
    cout << "Studentu grupavimo i dvi grupes pagal pazymius laikas: " << grupavimo_laikas.count() << " s\n";
    cout << "Isvedimo i naujus failus laikas: " << isvedimo_laikas.count() << " s\n";
    cout << "Studentu rusiavimo pagal pasirinkta parametra laikas: "
     << rusiavimo_laikas.count() << " s\n";

double bendras_laikas = nuskaitymo_laikas.count()
                      + grupavimo_laikas.count()
                      + rusiavimo_laikas.count()
                      + isvedimo_laikas.count();

std::string irasu_kiekis;

if (failo_pavadinimas == "studentai_1k.txt")
    irasu_kiekis = "1 tukst.";
else if (failo_pavadinimas == "studentai_10k.txt")
    irasu_kiekis = "10 tukst.";
else if (failo_pavadinimas == "studentai_100k.txt")
    irasu_kiekis = "100 tukst.";
else if (failo_pavadinimas == "studentai_1m.txt")
    irasu_kiekis = "1 mln.";
else if (failo_pavadinimas == "studentai_10m.txt")
    irasu_kiekis = "10 mln.";

cout << irasu_kiekis << " irasu testo laikas: "
     << bendras_laikas << " s\n";
}

void apdoroti_visus_failus() {
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

    apdoroti_faila("studentai_1k.txt", "vargsiukai_1k.txt",
                   "kietiakai_1k.txt", pasirinkimas);

    apdoroti_faila("studentai_10k.txt", "vargsiukai_10k.txt",
                   "kietiakai_10k.txt", pasirinkimas);

    apdoroti_faila("studentai_100k.txt", "vargsiukai_100k.txt",
                   "kietiakai_100k.txt", pasirinkimas);

    apdoroti_faila("studentai_1m.txt", "vargsiukai_1m.txt",
                   "kietiakai_1m.txt", pasirinkimas);

    apdoroti_faila("studentai_10m.txt", "vargsiukai_10m.txt",
                   "kietiakai_10m.txt", pasirinkimas);
}

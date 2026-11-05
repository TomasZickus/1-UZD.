#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <fstream>
#include <sstream>
#include <array>

#include "studentas.h"
#include "funkcijos.h"

using std::cin;
using std::cout;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;

// Apdorojimo funkcijos tipas
using ApdorojimoFunkcija = MatavimoLaikai (*)(
    const std::string&,
    const std::string&,
    const std::string&,
    int
);

// Vieno failo informacija
struct Failas {
    std::string pavadinimas;
    std::string dydis;
};

// Suskaičiuoja vieno konteinerio vidutinius laikus
MatavimoLaikai matuoti_vidurki(
    ApdorojimoFunkcija funkcija,
    const std::string& failas,
    const std::string& vargs,
    const std::string& kiet,
    int bandymu_kiekis
) {
    MatavimoLaikai suma{};

    for (int i = 0; i < bandymu_kiekis; i++) {
        MatavimoLaikai laikai = funkcija(failas, vargs, kiet, 1);

        suma.nuskaitymas += laikai.nuskaitymas;
        suma.grupavimas += laikai.grupavimas;
        suma.rusiavimas += laikai.rusiavimas;
        suma.isvedimas += laikai.isvedimas;
    }

    suma.nuskaitymas /= bandymu_kiekis;
    suma.grupavimas /= bandymu_kiekis;
    suma.rusiavimas /= bandymu_kiekis;
    suma.isvedimas /= bandymu_kiekis;

    return suma;
}

// Išveda vieno konteinerio vidutinius laikus
void isvesti_laikus(const std::string& konteineris, const MatavimoLaikai& t) {
    double bendras = t.nuskaitymas + t.grupavimas +
                     t.rusiavimas + t.isvedimas;

    cout << "\n" << konteineris << ":\n";
    cout << fixed << setprecision(5);

    cout << "Nuskaitymas: " << t.nuskaitymas << " s\n";
    cout << "Grupavimas:  " << t.grupavimas << " s\n";
    cout << "Rusavimas:   " << t.rusiavimas << " s\n";
    cout << "Isvedimas:   " << t.isvedimas << " s\n";
    cout << "Bendras:     " << bendras << " s\n";
}

// Atlieka pasirinktos strategijos testą su vienu failu
void testuoti_faila(
    const Failas& failas,
    int strategija,
    int bandymu_kiekis
) {
    ApdorojimoFunkcija vector_funkcija;
    ApdorojimoFunkcija list_funkcija;

    if (strategija == 1) {
        vector_funkcija = apdoroti_faila;
        list_funkcija = apdoroti_faila_list;
    }
    else {
        vector_funkcija = apdoroti_faila_2strategija;
        list_funkcija = apdoroti_faila_list_2strategija;
    }

    std::string strategijos_pavadinimas = "s" + std::to_string(strategija);

    cout << "\n========================================\n";
    cout << "Failas: " << failas.pavadinimas << "\n";
    cout << "Strategija: " << strategija << "\n";
    cout << "Bandymu skaicius: " << bandymu_kiekis << "\n";
    cout << "========================================\n";

    // Vector testas
    MatavimoLaikai vector_laikai = matuoti_vidurki(
        vector_funkcija,
        failas.pavadinimas,
        "vargsiukai_" + strategijos_pavadinimas + "_vector_" + failas.dydis + ".txt",
        "kietiakai_" + strategijos_pavadinimas + "_vector_" + failas.dydis + ".txt",
        bandymu_kiekis
    );

    // List testas
    MatavimoLaikai list_laikai = matuoti_vidurki(
        list_funkcija,
        failas.pavadinimas,
        "vargsiukai_" + strategijos_pavadinimas + "_list_" + failas.dydis + ".txt",
        "kietiakai_" + strategijos_pavadinimas + "_list_" + failas.dydis + ".txt",
        bandymu_kiekis
    );

    isvesti_laikus("VECTOR", vector_laikai);
    isvesti_laikus("LIST", list_laikai);
}

// Pasirinkto failo arba visų failų testavimas
void pasirinkti_testus() {
    const std::array<Failas, 5> failai = {{
        {"studentai_1k.txt", "1k"},
        {"studentai_10k.txt", "10k"},
        {"studentai_100k.txt", "100k"},
        {"studentai_1m.txt", "1m"},
        {"studentai_10m.txt", "10m"}
    }};

    int strategija;
    int failo_pasirinkimas;

    cout << "\nPasirinkite grupavimo strategija:\n";
    cout << "1 - Pirmoji strategija\n";
    cout << "2 - Antroji strategija\n";
    cout << "Jusu pasirinkimas: ";

    if (!(cin >> strategija) || (strategija != 1 && strategija != 2)) {
        cout << "Neteisingas pasirinkimas.\n";
        return;
    }

    cout << "\nPasirinkite faila testavimui:\n";

    for (int i = 0; i < 5; i++) {
        cout << i + 1 << " - " << failai[i].pavadinimas << "\n";
    }

    cout << "6 - Visi failai paeiliui\n";
    cout << "Jusu pasirinkimas: ";

    if (!(cin >> failo_pasirinkimas) ||
        failo_pasirinkimas < 1 || failo_pasirinkimas > 6) {
        cout << "Neteisingas pasirinkimas.\n";
        return;
    }

    const int bandymu_kiekis = 3;

    if (failo_pasirinkimas == 6) {
        for (const Failas& failas : failai) {
            testuoti_faila(failas, strategija, bandymu_kiekis);
        }
    }
    else {
        testuoti_faila(
            failai[failo_pasirinkimas - 1],
            strategija,
            bandymu_kiekis
        );
    }

    cout << "\nTestavimas baigtas.\n";
}

int main() {
    std::vector<studentas> studentai;
    std::list<studentas> studentai_list;

    char kl;
    int pasirinkimas;

    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti pazymius ranka\n";
    cout << "2 - Generuoti pazymius atsitiktinai\n";
    cout << "3 - Nuskaityti is failo\n";
    cout << "4 - Sugeneruoti 5 failus ir juos apdoroti\n";
    cout << "5 - Atlikti spartos testus su esamais failais\n";
    cout << "Jusu pasirinkimas: ";

    if (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 5) {
        cout << "Neteisingas pasirinkimas.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    if (pasirinkimas == 4) {
        generuoti_visus_failus(gen);

        cout << "\nPradedamas failu apdorojimas...\n";
        apdoroti_visus_failus(1);
        return 0;
    }

    if (pasirinkimas == 5) {
        pasirinkti_testus();
        return 0;
    }

    if (pasirinkimas == 3) {
        std::string failo_pavadinimas;

        cout << "Iveskite failo pavadinima: ";
        cin >> failo_pavadinimas;

        std::ifstream fd(failo_pavadinimas);

        if (!fd) {
            cout << "Nepavyko atidaryti failo!\n";
            return 1;
        }

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
        cout << "Duomenys sekmingai nuskaityti.\n";
    }
    else {
        std::uniform_int_distribution<int> dist(1, 10);

        while (true) {
            studentas A;

            cout << "\nIveskite varda: ";
            cin >> A.var;

            cout << "Iveskite pavarde: ";
            cin >> A.pav;

            if (pasirinkimas == 1) {
                while (true) {
                    int pazymys;

                    cout << "Iveskite namu darbo pazymi: ";
                    cin >> pazymys;
                    A.paz.push_back(pazymys);

                    cout << "Ar studentas turi dar pazymiu? t/n ";
                    cin >> kl;

                    if (kl == 'n' || kl == 'N')
                        break;
                }

                cout << "Iveskite egzamino pazymi: ";
                cin >> A.egz;
            }
            else if (pasirinkimas == 2) {
                int kiek_nd;

                cout << "Kiek namu darbu pazymiu generuoti? ";
                cin >> kiek_nd;

                for (int i = 0; i < kiek_nd; i++)
                    A.paz.push_back(dist(gen));

                A.egz = dist(gen);

                cout << "Sugeneruoti ND pazymiai: ";

                for (int pazymys : A.paz)
                    cout << pazymys << " ";

                cout << "\nSugeneruotas egzamino pazymys: "
                     << A.egz << "\n";
            }

            paskaiciuoti_rezultatus(A);
            studentai.push_back(A);

            if (pasirinkimas == 1) {
                studentai_list.push_back(A);

                cout << "Objekto adresas (vector): "
                     << static_cast<const void*>(&studentai.back()) << "\n";

                cout << "Objekto adresas (list): "
                     << static_cast<const void*>(&studentai_list.back()) << "\n";
            }

            cout << "Ar norite ivesti dar viena studenta? t/n ";
            cin >> kl;

            if (kl == 'n' || kl == 'N')
                break;
        }
    }

    int plotis = 15 + 15 + 17 + 17 + 5;

    cout << "\nStudentu rezultatai:\n";
    cout << std::string(plotis, '-') << "\n";

    cout << "|" << left << setw(15) << "Pavarde"
         << "|" << left << setw(15) << "Vardas"
         << "|" << left << setw(17) << "Galutinis (Vid.)"
         << "|" << left << setw(17) << "Galutinis (Med.)"
         << "|\n";

    cout << std::string(plotis, '-') << "\n";

    for (const studentas& A : studentai)
        cout << "|" << left << setw(15) << A.pav
             << "|" << left << setw(15) << A.var
             << "|" << left << setw(17) << fixed << setprecision(2) << A.rez
             << "|" << left << setw(17) << A.rez_med << "|\n";

    cout << std::string(plotis, '-') << "\n";

    return 0;
}

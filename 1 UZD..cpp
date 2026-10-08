#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;

struct studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double rez, rez_med;
};

void paskaiciuoti_rezultatus(studentas &A) {
    double suma = 0;

    for (int sk : A.paz)
        suma += sk;

    double nd_vidurkis = A.paz.empty() ? 0 : suma / A.paz.size();
    A.rez = 0.4 * nd_vidurkis + 0.6 * A.egz;

    std::vector<int> surikiuoti = A.paz;
    std::sort(surikiuoti.begin(), surikiuoti.end());

    double nd_mediana = 0;

    if (!surikiuoti.empty()) {
        if (surikiuoti.size() % 2 == 1)
            nd_mediana = surikiuoti[surikiuoti.size() / 2];
        else
            nd_mediana = (surikiuoti[surikiuoti.size() / 2 - 1] +
                          surikiuoti[surikiuoti.size() / 2]) / 2.0;
    }

    A.rez_med = 0.4 * nd_mediana + 0.6 * A.egz;
}

void generuoti_faila(std::string failo_pavadinimas, int kiek_studentu,
                     std::mt19937 &gen) {
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

int main() {
    std::vector<studentas> studentai;
    char kl;
    int pasirinkimas;

    cout << "Pasirinkite, kaip bus ivesti pazymiai:\n";
    cout << "1 - Ivesti pazymius ranka\n";
    cout << "2 - Generuoti pazymius atsitiktinai\n";
    cout << "3 - Nuskaityti is failo\n";
    cout << "4 - Sugeneruoti 5 studentu failus\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    std::random_device rd;
    std::mt19937 gen(rd());

    if (pasirinkimas == 4) {
        generuoti_visus_failus(gen);
        cout << "\nVisi 5 failai sugeneruoti.\n";
        cout << "Pradedamas ju apdorojimas...\n";
        apdoroti_visus_failus();
        return 0;
    }

    if (pasirinkimas == 3) {
        std::string failo_pavadinimas;
        cout << "Iveskite failo pavadinima (pvz., kursiokai.txt): ";
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

                A.egz = A.paz.back();
                A.paz.pop_back();

                paskaiciuoti_rezultatus(A);
                studentai.push_back(A);
            }
        }

        fd.close();
        cout << "Duomenys sekmingai nuskaityti is failo.\n";
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

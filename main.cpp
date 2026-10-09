#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

#include "studentas.h"
#include "funkcijos.h"

using std::cin;
using std::cout;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;

int main() {
    std::vector<studentas> studentai;
    char kl;
    int pasirinkimas;

    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti pazymius ranka\n";
    cout << "2 - Generuoti pazymius atsitiktinai\n";
    cout << "3 - Nuskaityti is failo\n";
    cout << "4 - Sugeneruoti 5 failus ir juos apdoroti\n";
    cout << "5 - Pakartoti spartos testus su esamais failais\n";
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
        cout << "\nBus atliekami 3 testavimo bandymai.\n";
        cout << "Naudojami jau egzistuojantys failai.\n";
        apdoroti_visus_failus(3);
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

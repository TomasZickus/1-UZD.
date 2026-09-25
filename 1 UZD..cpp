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
    double rez;
    double rez_med;
};

void paskaiciuoti_rezultatus(studentas &A) {
    double suma = 0;
    for (int sk : A.paz) {
        suma += sk;
    }
    double nd_vidurkis = A.paz.empty() ? 0 : suma / A.paz.size();
    A.rez = 0.4 * nd_vidurkis + 0.6 * A.egz;

    std::vector<int> surikiuoti = A.paz;
    std::sort(surikiuoti.begin(), surikiuoti.end());
    double nd_mediana = 0;
    
    if (!surikiuoti.empty()) {
        if (surikiuoti.size() % 2 == 1) {
            nd_mediana = surikiuoti[surikiuoti.size() / 2];
        } else {
            nd_mediana = (surikiuoti[surikiuoti.size() / 2 - 1] + 
                          surikiuoti[surikiuoti.size() / 2]) / 2.0;
        }
    }
    A.rez_med = 0.4 * nd_mediana + 0.6 * A.egz;
}

int main() {
    std::vector<studentas> studentai;
    char kl;
    int pasirinkimas;

    cout << "Pasirinkite, kaip bus ivesti pazymiai:\n";
    cout << "1 - Ivesti pazymius ranka\n";
    cout << "2 - Generuoti pazymius atsitiktinai\n";
    cout << "3 - Nuskaityti is failo\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

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
        std::getline(fd, eilute); // Praleidžiama pirma eilutė su stulpelių pavadinimais

        while (std::getline(fd, eilute)) {
            if (eilute.empty()) continue;

            std::istringstream iss(eilute);
            studentas A;
            
            // Nuskaitomas vardas ir pavardė
            if (iss >> A.var >> A.pav) {
                int pazymys;
                A.paz.clear();
                
                // Nuskaitomi visi likę skaičiai eilutėje
                while (iss >> pazymys) {
                    A.paz.push_back(pazymys);
                }
                
                // Paskutinis nuskaitytas skaičius yra egzamino pažymys
                if (!A.paz.empty()) {
                    A.egz = A.paz.back();
                    A.paz.pop_back(); // Pašalinamas egzamino pažymys iš ND sąrašo
                } else {
                    A.egz = 0;
                }
                
                paskaiciuoti_rezultatus(A);
                studentai.push_back(A);
            }
        }
        fd.close();
        cout << "Duomenys sekmingai nuskaityti is failo.\n";
    } 
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
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
                    if (kl == 'n' || kl == 'N') break;
                }
                cout << "Iveskite egzamino pazymi: ";
                cin >> A.egz;
            } 
            else if (pasirinkimas == 2) {
                int kiek_nd;
                cout << "Kiek namu darbu pazymiu generuoti? ";
                cin >> kiek_nd;

                for (int i = 0; i < kiek_nd; i++) {
                    A.paz.push_back(dist(gen));
                }
                A.egz = dist(gen);

                cout << "Sugeneruoti ND pazymiai: ";
                for (int pazymys : A.paz) cout << pazymys << " ";
                cout << "\nSugeneruotas egzamino pazymys: " << A.egz << "\n";
            }

            paskaiciuoti_rezultatus(A);
            studentai.push_back(A);

            cout << "Ar norite ivesti dar viena studenta? t/n ";
            cin >> kl;
            if (kl == 'n' || kl == 'N') break;
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

    for (const studentas& A : studentai) {
        cout << "|" << left << setw(15) << A.pav
             << "|" << left << setw(15) << A.var
             << "|" << left << setw(17) << fixed << setprecision(2) << A.rez
             << "|" << left << setw(17) << fixed << setprecision(2) << A.rez_med
             << "|\n";
    }
    cout << std::string(plotis, '-') << "\n";

    return 0;
}

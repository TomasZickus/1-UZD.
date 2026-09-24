#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

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


int main() {
    std::vector<studentas> studentai;
    char kl;
    int pasirinkimas;

    // Programos veiksmų pasirinkimo meniu
    cout << "Pasirinkite, kaip bus ivesti pazymiai:\n";
    cout << "1 - Ivesti pazymius ranka\n";
    cout << "2 - Generuoti pazymius atsitiktinai\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    // Atsitiktiniu skaiciu generatorius
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
            // Pazymiu ivedimas ranka
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
            // Pazymiu generavimas atsitiktinai
            int kiek_nd;

            cout << "Kiek namu darbu pazymiu generuoti? ";
            cin >> kiek_nd;

            for (int i = 0; i < kiek_nd; i++) {
                A.paz.push_back(dist(gen));
            }

            A.egz = dist(gen);

            cout << "Sugeneruoti ND pazymiai: ";
            for (int pazymys : A.paz)
                cout << pazymys << " ";

            cout << "\nSugeneruotas egzamino pazymys: "
                 << A.egz << "\n";
        }

        // Galutinis balas pagal vidurki
        double suma = 0;

        for (int sk : A.paz)
            suma += sk;

        double nd_vidurkis = suma / A.paz.size();

        A.rez = 0.4 * nd_vidurkis + 0.6 * A.egz;


        // Galutinis balas pagal mediana
        std::vector<int> surikiuoti = A.paz;
        std::sort(surikiuoti.begin(), surikiuoti.end());

        double nd_mediana;

        if (surikiuoti.size() % 2 == 1) {
            nd_mediana = surikiuoti[surikiuoti.size() / 2];
        }
        else {
            nd_mediana = (
                surikiuoti[surikiuoti.size() / 2 - 1] +
                surikiuoti[surikiuoti.size() / 2]
            ) / 2.0;
        }

        A.rez_med = 0.4 * nd_mediana + 0.6 * A.egz;

        studentai.push_back(A);

        cout << "Ar norite ivesti dar viena studenta? t/n ";
        cin >> kl;

        if (kl == 'n' || kl == 'N')
            break;
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

    for (studentas A : studentai) {
        cout << "|" << left << setw(15) << A.pav
             << "|" << left << setw(15) << A.var
             << "|" << left << setw(17) << fixed << setprecision(2) << A.rez
             << "|" << left << setw(17) << fixed << setprecision(2) << A.rez_med
             << "|\n";
    }

    cout << std::string(plotis, '-') << "\n";

    return 0;
}

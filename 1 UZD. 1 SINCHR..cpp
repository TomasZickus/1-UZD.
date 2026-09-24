#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::fixed;
using std::left;
using std::right;
using std::setprecision;
using std::setw;


struct studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double rez;
};


int main() {
    std::vector<studentas> studentai;
    char kl;

    while (true) {
        studentas A;

        cout << "Iveskite varda: ";
        cin >> A.var;

        cout << "Iveskite pavarde: ";
        cin >> A.pav;

        int n;
        cout << "Iveskite namu darbu skaiciu: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            int pazymys;
            cout << "Iveskite namu darbo pazymi: ";
            cin >> pazymys;
            A.paz.push_back(pazymys);
        }

        cout << "Iveskite egzamino pazymi: ";
        cin >> A.egz;

        double suma = 0;

        for (int sk : A.paz)
            suma += sk;

        double nd_vidurkis = suma / A.paz.size();

        A.rez = 0.4 * nd_vidurkis + 0.6 * A.egz;

        studentai.push_back(A);

        cout << "Ar norite ivesti dar viena studenta? t/n ";
        cin >> kl;

        if (kl == 'n' || kl == 'N')
            break;
    }


int plotis = 15 + 15 + 17 + 4;

cout << "\nStudentu rezultatai:\n";

cout << std::string(plotis, '-') << "\n";
cout << "|" << left << setw(15) << "Pavarde"
     << "|" << left << setw(15) << "Vardas"
     << "|" << left << setw(17) << "Galutinis (Vid.)"
     << "|\n";
cout << std::string(plotis, '-') << "\n";

for (studentas A : studentai) {
    cout << "|" << left << setw(15) << A.pav
         << "|" << left << setw(15) << A.var
         << "|" << left << setw(17) << fixed << setprecision(2) << A.rez
         << "|\n";
}

cout << std::string(plotis, '-') << "\n";

    return 0;
}
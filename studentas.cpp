#include "studentas.h"
#include <algorithm>

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
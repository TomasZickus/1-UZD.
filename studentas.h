#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double rez, rez_med;
};

void paskaiciuoti_rezultatus(studentas &A);

#endif
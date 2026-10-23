Programos spartos, dirbant su skirtingais konteinerių tipais ir skirtingo dydžio failais, testavimas

Visi testai atlikti su penkiais skirtingo dydžio failais, kiekvienam iš jų naudojant du skirtingus konteinerių tipus - vector ir list. Kiekvieno bandymo metu buvo atliekamas 4 atskirų operacijų - nuskaitymo, grupavimo, rūšiavimo, išvedimo laiko - matavimas. Kiekvienas bandymas pakartotas po 3 kartus. Lentelėje pateikti pagal tuos 3 bandymus apskaičiuoti vidutiniai kiekvienos operacijos veikimo laikai ir iš jų susumuotas bendras vidutinis veikimo laikas.

Testavimo rezultatai:

| Failas | Įrašų skaičius | Konteineris | Nuskaitymas (s) | Grupavimas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|---|---:|---|---:|---:|---:|---:|---:|
| studentai_1k.txt | 1 000 | vector | 0.005539 | 0.001473 | 0.002462 | 0.010487 | 0.019960 |
| studentai_1k.txt | 1 000 | list | 0.005263 | 0.002884 | 0.000665 | 0.007621 | 0.016433 |
| studentai_10k.txt | 10 000 | vector | 0.039485 | 0.007045 | 0.023252 | 0.039920 | 0.109702 |
| studentai_10k.txt | 10 000 | list | 0.034508 | 0.007442 | 0.007008 | 0.034544 | 0.083502 |
| studentai_100k.txt | 100 000 | vector | 0.254875 | 0.052530 | 0.310901 | 0.241529 | 0.859835 |
| studentai_100k.txt | 100 000 | list | 0.228790 | 0.053537 | 0.085303 | 0.237198 | 0.604828 |
| studentai_1m.txt | 1 000 000 | vector | 2.289487 | 0.528607 | 3.545068 | 2.047804 | 8.410966 |
| studentai_1m.txt | 1 000 000 | list | 2.206596 | 0.459248 | 1.292069 | 2.321948 | 6.279861 |
| studentai_10m.txt | 10 000 000 | vector | 24.085971 | 4.630377 | 42.440929 | 19.776977 | 90.934255 |
| studentai_10m.txt | 10 000 000 | list | 22.935342 | 4.921021 | 17.369295 | 21.858432 | 67.084090 |

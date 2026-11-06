
## Programos įdiegimas ir kompiliavimas

Programai sukompiliuoti reikalingi:
- C++17 standartą palaikantis C++ kompiliatorius (GCC, Clang arba MSVC).
- CMake (ne žemesnė nei 3.15 versija).

1. Atsisiųskite projekto failus iš GitHub repozitorijos.
2. Atidarykite terminalą projekto aplanke.
3. Sukurkite kompiliavimo aplanką ir paruoškite projektą:

```bash
cmake -S . -B build
```

4. Sukompiliuokite programą:

```bash
cmake --build build
```

5. Paleiskite sukurtą vykdomąjį failą.


Programos spartos testavimas, taikant skirtingas grupavimo strategijas

Testavimo sistemos parametrai (prieš atliekant visus testus):

<img width="1315" height="867" alt="CPU_2026_11_05" src="https://github.com/user-attachments/assets/889b1e1f-2c9f-4633-b6ca-cedf1fa84b04" />
<img width="1311" height="891" alt="RAM_2026_11_05" src="https://github.com/user-attachments/assets/596f93d8-e849-4989-b4f6-11d68defc174" />
<img width="1310" height="877" alt="SSD_2026_11_05" src="https://github.com/user-attachments/assets/164b4dbf-5dd2-408c-9074-7f837f3ccdbe" />

Iš pradžių sparta buvo testuojama tik pagal 1 ir 2 strategijas (viena po kitos), siekiant palyginti kuri iš jų greitesnė, kad būtų galima nuspręsti, į kurią iš jų vėliau įtraukti 3 strategijos metodus.

Abiems strategijoms atlikta po analogišką testą. Jo metu visi bandymai atlikti su tais pačiais penkiais skirtingo dydžio failais, kiekvienam iš jų naudojant du skirtingus konteinerių tipus - vector ir list. Kiekvieno bandymo metu buvo atliekamas 4 atskirų operacijų - nuskaitymo, grupavimo, rūšiavimo, išvedimo laiko - matavimas. Kiekvienas bandymas (kiekvienam iš failų ir konteinerių tipų) pakartotas po 3 kartus. Iš tų 3 kartų apskaičiuoti vidutiniai kiekvienos operacijos veikimo laikai ir iš jų susumuotas bendras vidutinis veikimo laikas.

1 ir 2 strategijų testavimo rezultatai:

1 strategija:

| Failas | Įrašų skaičius | Konteineris | Nuskaitymas (s) | Grupavimas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|---|---:|---|---:|---:|---:|---:|---:|
| studentai_1k.txt | 1 000 | vector | 0.00705 | 0.00101 | 0.00282 | 0.01688 | 0.02776 |
| studentai_1k.txt | 1 000 | list | 0.00477 | 0.00082 | 0.00037 | 0.01958 | 0.02554 |
| studentai_10k.txt | 10 000 | vector | 0.03990 | 0.00886 | 0.02928 | 0.03729 | 0.11533 |
| studentai_10k.txt | 10 000 | list | 0.03865 | 0.00956 | 0.00569 | 0.04211 | 0.09602 |
| studentai_100k.txt | 100 000 | vector | 0.30464 | 0.05344 | 0.26497 | 0.21261 | 0.83565 |
| studentai_100k.txt | 100 000 | list | 0.21050 | 0.04244 | 0.06665 | 0.23924 | 0.55882 |
| studentai_1m.txt | 1 000 000 | vector | 2.27323 | 0.51628 | 3.58386 | 2.04863 | 8.42200 |
| studentai_1m.txt | 1 000 000 | list | 2.27616 | 0.46425 | 1.26872 | 2.24519 | 6.25432 |
| studentai_10m.txt | 10 000 000 | vector | 23.95064 | 4.42866 | 41.18683 | 18.92096 | 88.48709 |
| studentai_10m.txt | 10 000 000 | list | 22.66313 | 4.75743 | 16.58871 | 20.65058 | 64.65984 |

2 strategija:

| Failas | Įrašų skaičius | Konteineris | Nuskaitymas (s) | Grupavimas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|---|---:|---|---:|---:|---:|---:|---:|
| studentai_1k.txt | 1 000 | vector | 0.00432 | 0.05710 | 0.00214 | 0.00659 | 0.07016 |
| studentai_1k.txt | 1 000 | list | 0.00484 | 0.00044 | 0.00044 | 0.01471 | 0.02042 |
| studentai_10k.txt | 10 000 | vector | 0.03980 | 3.52760 | 0.01851 | 0.03126 | 3.61717 |
| studentai_10k.txt | 10 000 | list | 0.02332 | 0.00330 | 0.00322 | 0.02414 | 0.05398 |
| studentai_100k.txt | 100 000 | vector | 0.27667 | 397.50126 | 0.37260 | 0.29398 | 398.44452 |
| studentai_100k.txt | 100 000 | list | 0.41018 | 0.03309 | 0.12687 | 0.39978 | 0.96991 |
| studentai_1m.txt | 1 000 000 | vector | - | - | - | - | - |
| studentai_1m.txt | 1 000 000 | list | - | - | - | - | - |
| studentai_10m.txt | 10 000 000 | vector | - | - | - | - | - |
| studentai_10m.txt | 10 000 000 | list | - | - | - | - | - |

Pastaba: 2 strategijos bandymų su didžiausiais failais įgyvendinimo iki galo nebesulaukiau, kadangi tai truko neadekvačiai ilgą laiką. Pagal pilnai įvykdytus bandymus su mažesniais failais akivaizdu, kad to stabdis šioje strategijoje - būtent studentų grupavimo etapas naudojant vektorių.

Išvada iš 1 ir 2 strategijų palyginimo: 1 strategijos veikimas žymiai spartesnis vector konteinerio atveju. Nors list atveju sparta skiriasi mažai, tačiau didžiulis vector skirtumas nulemia tai, kad bendras 1 strategijos veikimas yra žymiai spartesnis.

Kadangi 1 strategija veikia sparčiau, tai pagal instrukcijos reikalavimus 3 strategijos realizacijai pasirinkau būtent ją. Taigi, 3 strategija yra optimizuota 1 strategija. Toliau, po atliktų kodo pakeitimų, atlikau analogišką pakartotinį 1 strategijos spartos matavimą ir jo rezultatus palyginau su išmatuota naujosios 3 strategijos sparta. Laikantis instrukcijos reikalavimų, į rezultatus įtraukti tik vector konteinerio matavimai.

1 ir 3 strategijų testavimo rezultatai:

1 strategija:

| Failas | Įrašų skaičius | Konteineris | Nuskaitymas (s) | Grupavimas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|---|---:|---|---:|---:|---:|---:|---:|
| studentai_1k.txt | 1 000 | vector | 0.00524 | 0.00175 | 0.00241 | 0.02353 | 0.03294 |
| studentai_10k.txt | 10 000 | vector | 0.04912 | 0.00954 | 0.03508 | 0.03830 | 0.13204 |
| studentai_100k.txt | 100 000 | vector | 0.27510 | 0.05078 | 0.27304 | 0.21201 | 0.81093 |
| studentai_1m.txt | 1 000 000 | vector | 2.35079 | 0.52115 | 3.70065 | 1.98832 | 8.56090 |
| studentai_10m.txt | 10 000 000 | vector | 24.37385 | 4.47011 | 43.08957 | 18.67776 | 90.61128 |

3 strategija:

| Failas | Įrašų skaičius | Konteineris | Nuskaitymas (s) | Grupavimas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
|---|---:|---|---:|---:|---:|---:|---:|
| studentai_1k.txt | 1 000 | vector | 0.00718 | 0.00121 | 0.00305 | 0.01847 | 0.02992 |
| studentai_10k.txt | 10 000 | vector | 0.06129 | 0.00940 | 0.02999 | 0.03895 | 0.13962 |
| studentai_100k.txt | 100 000 | vector | 0.28448 | 0.06853 | 0.29612 | 0.23422 | 0.88334 |
| studentai_1m.txt | 1 000 000 | vector | 2.28487 | 0.56047 | 3.60371 | 1.94276 | 8.39181 |
| studentai_10m.txt | 10 000 000 | vector | 30.11702 | 5.55241 | 53.27708 | 23.31548 | 112.26198 |

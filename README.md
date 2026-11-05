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

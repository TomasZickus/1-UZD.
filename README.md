Programos spartos testavimas, taikant skirtingas grupavimo strategijas

Testavimo sistemos parametrai (prieš atliekant visus testus):

<img width="1315" height="867" alt="CPU_2026_11_05" src="https://github.com/user-attachments/assets/889b1e1f-2c9f-4633-b6ca-cedf1fa84b04" />
<img width="1311" height="891" alt="RAM_2026_11_05" src="https://github.com/user-attachments/assets/596f93d8-e849-4989-b4f6-11d68defc174" />
<img width="1310" height="877" alt="SSD_2026_11_05" src="https://github.com/user-attachments/assets/164b4dbf-5dd2-408c-9074-7f837f3ccdbe" />

Iš pradžių sparta buvo testuojama tik pagal 1 ir 2 strategijas (viena po kitos), siekiant palyginti kuri iš jų greitesnė, kad būtų galima nuspręsti, į kurią iš jų vėliau įtraukti 3 strategijos metodus.

Abiems strategijoms atlikta po analogišką testą. Jo metu visi bandymai atlikti su tais pačiais penkiais skirtingo dydžio failais, kiekvienam iš jų naudojant du skirtingus konteinerių tipus - vector ir list. Kiekvieno bandymo metu buvo atliekamas 4 atskirų operacijų - nuskaitymo, grupavimo, rūšiavimo, išvedimo laiko - matavimas. Kiekvienas bandymas (kiekvienam iš failų ir konteinerių tipų) pakartotas po 3 kartus. Iš tų 3 kartų apskaičiuoti vidutiniai kiekvienos operacijos veikimo laikai ir iš jų susumuotas bendras vidutinis veikimo laikas.

1 ir 2 strategijų testavimo rezultatai:

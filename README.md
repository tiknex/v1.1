# Studentų galutinio balo skaičiuoklė (v1.0)

Programa nuskaito studentų duomenis (ranka arba iš failo), apskaičiuoja galutinį balą, padalina studentus į **vargšiukus** (galutinis < 5.0) ir **kietiakius** (galutinis ≥ 5.0), išveda juos į du failus ir matuoja kiekvieno žingsnio trukmę. Programa veikia su dviem konteineriais: `std::vector` ir `std::list`.

---

## Įdiegimas ir paleidimas

### Su CMake (bet kokia OS)

```
mkdir build
cd build## v1.1: struct pakeista į class

### Kas pasikeitė

- `struct Studentas` pakeista į **`class Studentas`** (`studentas.h`, `studentas.cpp`).
- Duomenys (`vardas_`, `pavarde_`, `nd_`, `egzaminas_`) yra **private**, todėl nuskaičius jų pakeisti iš išorės negalima. Prie jų prieinama per `const` get'erius: `vardas()`, `pavarde()`, `nd()`, `egzaminas()`, `galVid()`, `galMed()`.
- Klasė turi:
  - **default konstruktorių** – sukurtas tuščias objektas iškart turi apibrėžtas reikšmes (anksčiau su `struct` laukai galėjo turėti „šiukšles“),
  - **konstruktorių su duomenimis** – naudojamas įvedant studentą ranka,
  - **konstruktorių iš srauto** – kreipiasi į `readStudent()`,
  - **destruktorių**,
  - **`readStudent(std::istream&)`** – nuskaito studentą iš failo eilutės.
- Galutinis balas (vidurkis ir mediana) apskaičiuojamas **vieną kartą**, kai studentas nuskaitomas, nes duomenys po to nesikeičia.
- Palyginimo funkcijos (`palygintiPagalPazymi`, `palygintiPagalVarda`, `palygintiPagalPavarde`) perkeltos į `studentas.h`, todėl visas darbo su studentu interfeisas yra vienoje vietoje.

### Kompiliavimas

Dabar programa turi du `.cpp` failus:

```
g++ main.cpp studentas.cpp -o studentai
```

arba su `make` / `cmake`, kaip aprašyta skyriuje „Įdiegimas ir paleidimas“.

### Testavimo sąlygos

- CPU: Intel Core i5-13420H, RAM: 16 GB, SSD 500 GB
- Kompiliatorius: g++ (MSYS2 UCRT64)
- Konteineris: `std::vector`, 3 dalijimo strategija, rūšiavimas pagal pažymį
- Kiekvienas laikas yra **3 testų vidurkis** (meniu 8 punktas), naudojant tuos pačius anksčiau sugeneruotus failus

### Struct ir class palyginimas su optimizavimo flag'ais

#### 100 000 įrašų (laikai sekundėmis)

| Versija | Flag'as | Nuskaitymas | Padalinimas | Rūšiavimas | Išvedimas | Iš viso |
|---|---|---:|---:|---:|---:|---:|
| struct | -O1 | 0.1741 | 0.0070 | 0.0525 | 0.0805 | 0.3140 |
| struct | -O2 | 0.1652 | 0.0061 | 0.0482 | 0.0730 | 0.2926 |
| struct | -O3 | 0.1587 | 0.0062 | 0.0396 | 0.0749 | 0.2794 |
| class | -O1 | 0.1665 | 0.0154 | 0.0422 | 0.0624 | 0.2866 |
| class | -O2 | 0.1662 | 0.0147 | 0.0397 | 0.0640 | 0.2847 |
| class | -O3 | 0.1654 | 0.0145 | 0.0392 | 0.0597 | 0.2788 |

#### 1 000 000 įrašų (laikai sekundėmis)

| Versija | Flag'as | Nuskaitymas | Padalinimas | Rūšiavimas | Išvedimas | Iš viso |
|---|---|---:|---:|---:|---:|---:|
| struct | -O1 | 0.4634 | 0.0781 | 0.3947 | 0.6500 | 1.5863 |
| struct | -O2 | 0.4336 | 0.0726 | 0.3951 | 0.6382 | 1.5396 |
| struct | -O3 | 0.4360 | 0.0734 | 0.3222 | 0.6575 | 1.4892 |
| class | -O1 | 0.3240 | 0.0669 | 0.2437 | 0.6133 | 1.2480 |
| class | -O2 | 0.3170 | 0.0676 | 0.2301 | 0.6053 | 1.2200 |
| class | -O3 | 0.3154 | 0.0656 | 0.2129 | 0.6119 | 1.2058 |

#### .exe failo dydis

| Versija | -O1 | -O2 | -O3 |
|---|---:|---:|---:|
| struct | 170 170 B | 162 960 B | 175 742 B |
| class | 144 618 B | 142 062 B | 145 359 B |

### Išvados

- **Class versija greitesnė**: su 1 000 000 įrašų ji visais flag'ais buvo apie **19–21 %** greitesnė nei struct. Labiausiai pagreitėjo **nuskaitymas** (apie 0.44 s → 0.32 s) ir **rūšiavimas** (apie 0.32–0.39 s → 0.21–0.24 s). Tai lėmė ne pats perėjimas prie klasės, o du realizacijos pakeitimai: `readStudent()` skaito pažymius tiesiai kaip skaičius (struct versijoje eilutė pirma buvo skaidoma į žodžius, o paskui kiekvienas verčiamas su `stoi`), o galutinis balas klasėje apskaičiuojamas vieną kartą, kai struct versijoje jis buvo skaičiuojamas iš naujo kiekviename palyginime rūšiuojant.
- Su 100 000 įrašų skirtumas mažas (apie 0–9 %). Class versijoje padalinimas truko kiek ilgiau (apie 0.015 s ir 0.006 s), bet dėl tokių mažų laikų bendram rezultatui tai beveik neturi įtakos.
- **Optimizavimo flag'ai**: kuo aukštesnis lygis, tuo programa šiek tiek greitesnė (-O3 greičiausias abiem versijoms), bet skirtumai nedideli: tarp -O1 ir -O3 apie 3–11 %. Daugiausia laimi rūšiavimas.
- **.exe dydis**: mažiausias su **-O2**, didžiausias su **-O3**, nes -O3 agresyviau „išskleidžia“ kodą (inline, ciklų išskleidimas), kad veiktų greičiau. Class versijos `.exe` apie 13–17 % mažesnis nei struct.
cmake ..
cmake --build .
```

Paleidimas: `./studentai` (Linux/macOS) arba `studentai.exe` (Windows, `build/` arba `build/Debug/` aplanke).

### Su make (Unix OS)

```
make
./studentai
```

`make clean` ištrina sukompiliuotą programą.

---

## Naudojimosi instrukcija

1. Paleidus programą pasirenkamas konteineris: `1` – vector, `2` – list.
2. Meniu:

| Meniu | Veiksmas |
|---|---|
| 1 | Studento įvedimas ranka (išvedamas ir objekto adresas atmintyje) |
| 2 | Studentų lentelė su vidurkiu, mediana ir adresu atmintyje |
| 3 | Programos pabaiga |
| 4 | Atsitiktinių studentų failų generavimas (matuojamas kūrimo laikas) |
| 5 | Duomenų nuskaitymas iš failo |
| 6 | Nuskaitymas, padalinimas pasirinkta strategija, rūšiavimas ir išvedimas į `vargsiukai.txt` ir `kietiakiai.txt` (matuojamas kiekvienas žingsnis) |
| 7 | Galutinių balų išvedimas į `galutinis.txt` |
| 8 | 6 punkto testas, kartojamas kelis kartus, su laikų vidurkiu |

3. 6 ir 8 punktuose dar pasirenkama:
   - rūšiavimas: `1` – pagal pažymį, `2` – pagal vardą,
   - dalijimo strategija: `1`, `2` arba `3` (žr. žemiau).

Failo formatas: pirma eilutė – antraštė, toliau `Vardas Pavarde ND1 ... NDn Egz`.

---

## Versijų (release) aprašymas

- **v.pradinė** – studentų įvedimas ranka, galutinis balas pagal vidurkį arba medianą.
- **v0.1** – atsitiktinis pažymių generavimas, nuskaitymas iš failo, rūšiavimas pagal pavardę ir išvedimas į failą.
- **v0.2** – atsitiktinių studentų failų generavimas, padalinimas į vargšiukus ir kietiakius, išvedimas į du failus, kodas išskaidytas į header failus, spartos analizė.
- **v0.3** – programa veikia su `std::vector` ir `std::list`, išvedamas studento adresas atmintyje, testų laikų vidurkis.
- **v1.0** – trys dalijimo strategijos, optimizavimas su `std::stable_partition`, `CMakeLists.txt` ir `Makefile`, išsami dokumentacija.

---

## v0.2 rezultatai (std::vector, vienas pažymys studentui)

| Įrašų kiekis | Failo kūrimas (s) | Nuskaitymas (s) | Padalinimas (s) | Rūšiavimas pagal pažymį (s) | Rūšiavimas pagal vardą (s) | Išvedimas (s) |
|---:|---:|---:|---:|---:|---:|---:|
| 1 000 | 0.006 | 0.004 | 0.0007 | 0.0005 | 0.0013 | 0.002 |
| 10 000 | 0.062 | 0.042 | 0.007 | 0.004 | 0.018 | 0.013 |
| 100 000 | 0.615 | 0.420 | 0.056 | 0.047 | 0.233 | 0.122 |
| 1 000 000 | 6.136 | 4.364 | 0.651 | 0.503 | 2.849 | 1.236 |
| 10 000 000 | 60.180 | 46.464 | 6.801 | 4.378 | 33.564 | 12.205 |

**Komentaras:** įrašų kiekiui padidėjus 10 kartų, beveik visų žingsnių laikas taip pat padidėja apie 10 kartų. Lėčiausias žingsnis yra nuskaitymas iš failo. Rūšiavimas pagal vardą apie 7,5 karto lėtesnis nei pagal pažymį, nes tekstą palyginti sudėtingiau nei skaičius.

---

## Dalijimo strategijos

| Strategija | Kaip veikia | Atmintis |
|---|---|---|
| **1** | Studentai nukopijuojami į du naujus konteinerius: `vargsiukai` ir `kietiakiai`. Bendras `studentai` lieka nepakeistas. | Kiekvienas studentas laikomas 2 kartus |
| **2** | Vargšiukas perkeliamas į `vargsiukai` ir **po vieną** ištrinamas iš `studentai` (`erase`). `studentai` lieka tik kietiakiai. | Efektyvu |
| **3** | `std::stable_partition` vienu perėjimu sustato kietiakius į priekį, o vargšiukus į galą. Tada visi vargšiukai perkeliami ir ištrinami **vienu kartu**. `list` atveju naudojamas `splice()`, kuris perkabina elementus nieko nekopijuodamas. | Efektyvu |

---

## Testavimo sistemos parametrai

- **CPU:** Intel Core i5-13420H
- **RAM:** 16 GB
- **Diskas:** SSD, 500 GB
- **GPU:** NVIDIA GeForce RTX 4050 (programa jos nenaudoja)

Testuota su tais pačiais anksčiau sugeneruotais failais (1 000, 10 000, 100 000, 1 000 000, 10 000 000 įrašų). Kiekvienas matavimas – 8 meniu punktas, **3 testų vidurkis**, rūšiuojant pagal pažymį.

---

## Rezultatai: padalinimo į 2 grupes trukmė (s)

### std::vector

| Įrašų kiekis | 1 strategija | 2 strategija | 3 strategija |
|---:|---:|---:|---:|
| 1 000 | 0.001038 s | 0.0179011 s | 0.0003051 s |
| 10 000 |  0.0128495 s |  1.61785 s | 0.0044307 s |
| 100 000 | 0.132819 s | 157.011 s | 0.0776445 s |
| 1 000 000 | 0.98303 s | * | 0.377603 s |
| 10 000 000 |  15.4931 s | * | 3.89215 s |

\* `vector` su 2 strategija kiekvienas `erase()` pastumia visus po ištrinto esančius elementus. Laikas auga kvadratiškai: įrašų 10 kartų daugiau – laikas apie 80–100 kartų ilgesnis. Su 1 000 000 įrašų tai užtruktų kelias valandas, todėl testuota tik iki 100 000.

### std::list

| Įrašų kiekis | 1 strategija | 2 strategija | 3 strategija |
|---:|---:|---:|---:|
| 1 000 | 0.0012473 s | 0.0006318 s | 0.0005204 s |
| 10 000 | 0.0141962 s | 0.0065537 s | 0.0058129 s |
| 100 000 | 0.158431 s | 0.0712846 s | 0.0649318 s |
| 1 000 000 | 1.35274 s	 | 0.741592 s | 0.623781 s |
| 10 000 000 | 14.0816 s | 7.93105 s | 6.71448 s |

### Visų žingsnių trukmė su greičiausia strategija (s)

| Įrašų kiekis | Konteineris | Nuskaitymas | Padalinimas | Rūšiavimas | Išvedimas |
|---:|---|---:|---:|---:|---:|
| 1 000 000 | vector | 4.352 | 0.378 | 0.491 | 1.218 |
| 1 000 000 | list | 4.617	 | 0.624 | 0.853 | 1.296 |
| 10 000 000 | vector | 45.931 | 3.892	 | 4.402	 | 12.134 |
| 10 000 000 | list | 48.706 | 6.714 | 11.238	 | 13.017 |

---

## Išvados

- **1 strategija** veikia panašiai su abiem konteineriais, bet naudoja dvigubai daugiau atminties, nes kiekvienas studentas yra ir bendrame, ir viename iš naujų konteinerių.
- **2 strategija** su `list` yra greita, nes ištrinti elementą iš sąrašo vidurio reikia tik perjungti nuorodas. Su `vector` ji labai lėta, nes kiekvienas `erase()` perstumia visus likusius elementus.
- **3 strategija** greita su abiem konteineriais, nes elementai perstatomi vienu perėjimu (`stable_partition`) ir ištrinami vienu kartu. Su `vector` tai greičiausias būdas.
- (Įrašyk savo pastebėjimus pagal gautus skaičius: kuris konteineris greitesnis nuskaitant, rūšiuojant ir pan.)

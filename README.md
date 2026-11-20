## v1.1: struct pakeista į class

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
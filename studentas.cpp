#include "studentas.h"
#include <algorithm>

// Pagalbines funkcijos (matomos tik siame faile)
static double vidurkis(const std::vector<int>& nd, int egz) {
    double suma = 0;
    for (int i = 0; i < (int)nd.size(); i++) {
        suma += nd[i];
    }
    suma += egz;
    return suma / (nd.size() + 1);
}

static double mediana(const std::vector<int>& nd, int egz) {
    std::vector<int> visos_reiksmes = nd;
    visos_reiksmes.push_back(egz);
    std::sort(visos_reiksmes.begin(), visos_reiksmes.end());

    int n = visos_reiksmes.size();
    if (n % 2 == 1) {
        return visos_reiksmes[n / 2];
    } else {
        return (visos_reiksmes[n/2 - 1] + visos_reiksmes[n/2]) / 2.0;
    }
}

// Default konstruktorius: objektas iskart turi apibreztas reiksmes
// (anksciau su struct neinicializuoti laukai galejo tureti "siuksles")
Studentas::Studentas() : egzaminas_(0), galVid_(0), galMed_(0) { }

// Konstruktorius, kai visi duomenys zinomi (pvz. ivedant ranka)
Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas) {
    skaiciuotiGalutinius();
}

// Konstruktorius is srauto: kreipiasi i readStudent
Studentas::Studentas(std::istream& is) : egzaminas_(0), galVid_(0), galMed_(0) {
    readStudent(is);
}

// Destruktorius: iskvieciamas, kai objektas sunaikinamas.
// string ir vector atminti atlaisvina patys, cia tik isvalomas pazymiu sarasas
Studentas::~Studentas() {
    nd_.clear();
}


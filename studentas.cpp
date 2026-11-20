#include "studentas.h"
#include <algorithm>

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
Studentas::Studentas() : egzaminas_(0), galVid_(0), galMed_(0) { }
Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas) {
    skaiciuotiGalutinius();
}

Studentas::Studentas(std::istream& is) : egzaminas_(0), galVid_(0), galMed_(0) {
    readStudent(is);
}

Studentas::~Studentas() {
    nd_.clear();
}
void Studentas::skaiciuotiGalutinius() {
    galVid_ = vidurkis(nd_, egzaminas_);
    galMed_ = mediana(nd_, egzaminas_);
}
std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    if (!(is >> vardas_ >> pavarde_)) {
        return is;
    }

    std::vector<int> pazymiai;
    int paz;
    while (is >> paz) {
        pazymiai.push_back(paz);
    }

    if (pazymiai.empty()) {          
        is.setstate(std::ios::failbit);
        return is;
    }
    if (is.eof()) {                  
        is.clear(std::ios::eofbit);
    }

    egzaminas_ = pazymiai.back();
    pazymiai.pop_back();
    nd_ = pazymiai;
    skaiciuotiGalutinius();
    return is;
}
bool palygintiPagalPazymi(const Studentas& a, const Studentas& b) {
    return a.galVid() < b.galVid();
}

bool palygintiPagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool palygintiPagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}



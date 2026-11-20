#pragma once
#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
    double galVid_; 
    double galMed_;

    void skaiciuotiGalutinius(); 

public:
    Studentas();                                        
    Studentas(const std::string& vardas, const std::string& pavarde,
              const std::vector<int>& nd, int egzaminas); 
    Studentas(std::istream& is);                        
    ~Studentas();                                   

    inline const std::string& vardas() const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }
    inline const std::vector<int>& nd() const { return nd_; }
    inline int egzaminas() const { return egzaminas_; }
    inline double galVid() const { return galVid_; }
    inline double galMed() const { return galMed_; }

    std::istream& readStudent(std::istream& is);
};
bool palygintiPagalPazymi(const Studentas& a, const Studentas& b);
bool palygintiPagalVarda(const Studentas& a, const Studentas& b);
bool palygintiPagalPavarde(const Studentas& a, const Studentas& b);

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "studentas.h"
using namespace std;

template <typename Konteineris>
void nuskaityti_is_failo(Konteineris& studentai, string failo_pavadinimas){
    studentai.clear();
    ifstream failas(failo_pavadinimas);
    if(!failas){
        cout<<"Nepavyko atidaryti failo"<<endl;
        return;
    }

    string eilute;
    getline(failas, eilute);

    while(getline(failas, eilute)){
                istringstream ss(eilute);
        Studentas A;
        if(A.readStudent(ss)){
            studentai.push_back(A);
        }

    }

    failas.close();
}
template <typename Konteineris>
void rasyti_i_faila_pagal_pavarde(Konteineris& studentai, string isvesties_failas){
    ofstream failas(isvesties_failas);
    if(!failas){
        cout<<"Nepavyko sukurti failo"<<endl;
        return;
    }
    failas<<left<<setw(15)<<"Pavarde"<<setw(15)<<"Vardas"<<setw(15)<<"Galutinis(vid.)"<<"/"<<"Galutinis(med.)"<<endl;
    failas<<string(70, '-')<<endl;
    failas<<fixed<<setprecision(2);

        for(auto& s : studentai){
               failas <<left<<setw(15)<<s.pavarde()
               <<setw(15)<<s.vardas()
               <<setw(15)<<s.galVid()
               <<s.galMed()
               <<endl;
    }

    failas.close();
    cout<<"Rezultatai issaugoti i faila: "<<isvesties_failas<<endl;
}

void generuoti_faila(int studentu_kiekis, string failo_pavadinimas){
    ofstream failas(failo_pavadinimas);
    if(!failas){
        cout<<"Nepavyko sukurti failo"<<endl;
        return;
    }
    failas<<left<<setw(20)<<"Vardas"<<setw(20)<<"Pavarde";
    for(int j = 1; j <= 15; j++){
        failas<<setw(6)<<"ND" + to_string(j);
    }
    failas<<"Egz."<<"\n";
    
    failas<<string(135, '-')<<"\n";
    for(int i = 1; i<=studentu_kiekis; i++){
        failas <<left<<setw(20)<<"Vardas" + to_string(i)<<setw(20)<<"Pavarde" + to_string(i);
        for(int j = 0; j < 15; j++){
            failas<<setw(6)<<rand() % 10 + 1;
        }
        failas<<rand() % 10 + 1<<"\n";
    }
    failas.close();
}
bool yra_vargsiukas(const Studentas& s){
    return s.galVid() < 5.0;
}
template <typename Konteineris>
void strategija_1(Konteineris& studentai, Konteineris& vargsiukai, Konteineris& kietiakiai){
    vargsiukai.clear();
    kietiakiai.clear();
    for(auto& s : studentai){
        if(yra_vargsiukas(s)){
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
}
template <typename Konteineris>
void strategija_2(Konteineris& studentai, Konteineris& vargsiukai){
    vargsiukai.clear();
    auto it = studentai.begin();
    while(it != studentai.end()){
        if(yra_vargsiukas(*it)){
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}
template <typename Konteineris>
void strategija_3(Konteineris& studentai, Konteineris& vargsiukai){
    vargsiukai.clear();
    auto riba = stable_partition(studentai.begin(), studentai.end(),
                          [](const Studentas& s){ return !yra_vargsiukas(s); });
    vargsiukai.assign(make_move_iterator(riba), make_move_iterator(studentai.end()));
    studentai.erase(riba, studentai.end());
}
void strategija_3(list<Studentas>& studentai, list<Studentas>& vargsiukai){
    vargsiukai.clear();
    auto riba = stable_partition(studentai.begin(), studentai.end(),
                          [](const Studentas& s){ return !yra_vargsiukas(s); });
    vargsiukai.splice(vargsiukai.end(), studentai, riba, studentai.end());
}
template <typename Konteineris>
Konteineris& padalinti(int strategija, Konteineris& studentai, Konteineris& vargsiukai, Konteineris& kietiakiai){
    if(strategija == 1){
        strategija_1(studentai, vargsiukai, kietiakiai);
        return kietiakiai;
    }
    if(strategija == 2){
        strategija_2(studentai, vargsiukai);
    } else {
        strategija_3(studentai, vargsiukai);
    }
    return studentai;
}
template <typename Konteineris>
void rasyti_i_faila_pagal_pazymi(Konteineris& studentai, string isvesties_failas){
    ofstream failas(isvesties_failas);
    if(!failas){
        cout<<"Nepavyko sukurti failo"<<endl;
        return;
    }
    failas<<left<<setw(20)<<"Vardas"<<setw(20)<<"Pavarde"<<"Galutinis"<<"\n";
    failas<<string(50, '-')<<"\n";
    failas<<fixed<<setprecision(2);

        for(auto& s : studentai){
        failas<<left<<setw(20)<<s.vardas()<<setw(20)<<s.pavarde()<<s.galVid()<<"\n";
    }
    failas.close();
}
// budas: 1 - pagal pazymi, 2 - pagal varda, 3 - pagal pavarde
void rusiuoti(vector<Studentas>& studentai, int budas){
    if(budas == 1)      sort(studentai.begin(), studentai.end(), palygintiPagalPazymi);
    else if(budas == 2) sort(studentai.begin(), studentai.end(), palygintiPagalVarda);
    else                sort(studentai.begin(), studentai.end(), palygintiPagalPavarde);
}
 
void rusiuoti(list<Studentas>& studentai, int budas){
    if(budas == 1)      studentai.sort(palygintiPagalPazymi);
    else if(budas == 2) studentai.sort(palygintiPagalVarda);
    else                studentai.sort(palygintiPagalPavarde);
}

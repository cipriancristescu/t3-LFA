#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int nrStari, nrTranzitii, stareStart, stareFinal, stareInitiala, nrStariFinale, nrCuvinte; 
vector<int> stari; 
char charCitit, charScris;
unordered_map<int, vector<tuple<int, char, char>>> tranzitii; 
vector<int> stariFinale; 
string cuvant; 

void citire() {
    fin >> nrStari;
    stari.resize(nrStari);
    for(int i = 0; i < nrStari; ++i) {
        fin >> stari[i];
    }
    fin >> nrTranzitii;
    for(int i = 0; i < nrTranzitii; ++i) {
        fin >> stareStart >> stareFinal >> charCitit >> charScris;
        tranzitii[stareStart].emplace_back(stareFinal, charCitit, charScris);
    }
    fin >> stareInitiala;
    fin >> nrStariFinale;
    stariFinale.resize(nrStariFinale);
    for(int i = 0; i < nrStariFinale; ++i) {
        fin >> stariFinale[i];
    }
    fin >> nrCuvinte;
}

pair<bool, string> fst(string cuv) {
    int stareCurenta = stareInitiala;
    string output = "";
    for(char litera : cuv) {
        bool gasit = false;
        for(auto& trans : tranzitii[stareCurenta]) {
            int stareUrmatoare;
            char intrare, iesire;
            tie(stareUrmatoare, intrare, iesire) = trans;
            if(intrare == litera) {
                stareCurenta = stareUrmatoare;
                output += iesire;
                gasit = true;
                break;
            }
        }
        if(!gasit) {
            return {false, ""};
        }
    }
    for(int stare : stariFinale) {
        if(stare == stareCurenta) {
            return {true, output};
        }
    }
    return {false, ""};
}

int main() {
    citire();

    for (int i = 0; i < nrCuvinte; ++i) {
        fin >> cuvant;
        auto rezultat = fst(cuvant);
        if(rezultat.first) {
            fout << "DA: " << rezultat.second << "\n";
        } else {
            fout << "NU\n";
        }
    }
    
    return 0;
}

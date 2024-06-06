#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>

using namespace std;

//sparge un string dupa delimitator
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    for (char ch : s) {
        if (ch == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// Citire gramatica si cuvant din fisier
void readGrammar(ifstream &file, unordered_map<string, vector<string>> &grammar, string &word) {
    string line;
    while (getline(file, line)) {
        if (line.find("->") != string::npos) {
            auto parts = split(line, ' ');
            string lhs = parts[0];
            for (size_t i = 2; i < parts.size(); i++) {
                if (parts[i] != "|") {
                    grammar[lhs].push_back(parts[i]);
                }
            }
        } else {
            word = line;
        }
    }
}

// Algoritmul CYK
bool cyk(const unordered_map<string, vector<string>> &grammar, const string &word) {
    int n = word.size();
    vector<vector<set<string>>> table(n, vector<set<string>>(n));

    // Inițializare tabel pentru lungimea de 1
    for (int i = 0; i < n; ++i) {
        for (const auto &rule : grammar) {
            for (const string &production : rule.second) {
                if (production.size() == 1 && production[0] == word[i]) {
                    table[i][i].insert(rule.first);
                }
            }
        }
    }

    // Completati tabelul pentru lungimi mai mari
    for (int l = 2; l <= n; ++l) { // l este lung segm
        for (int i = 0; i <= n - l; ++i) { // i este inc segm
            int j = i + l - 1; // j este sfârșitul segmentului
            for (int k = i; k < j; ++k) { // k este pct de impartire
                for (const auto &rule : grammar) {
                    for (const string &production : rule.second) {
                        if (production.size() == 2) {
                            string B = production.substr(0, 1);
                            string C = production.substr(1, 1);
                            if (table[i][k].count(B) && table[k + 1][j].count(C)) {
                                table[i][j].insert(rule.first);
                            }
                        }
                    }
                }
            }
        }
    }

    // Verifica daca s e in dreapta sus
    return table[0][n - 1].count("S");
}

int main() {
    ifstream file("grammar.txt");
    if (!file) {
        cerr << "Unable to open file grammar.txt";
        return 1;
    }

    unordered_map<string, vector<string>> grammar;
    string word;
    readGrammar(file, grammar, word);
    file.close();
    //cout<<word;
    if (cyk(grammar, word)) {
        cout << "The word \"" << word << "\" belongs to the grammar." << endl;
    } else {
        cout << "The word \"" << word << "\" does not belong to the grammar." << endl;
    }

    return 0;
}

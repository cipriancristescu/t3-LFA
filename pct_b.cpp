#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void pda(const string& sirIntrare) 
{
    stack<char> stiva;
    stiva.push('Z');  // Simbolul initial

    // marcam cu e sfarsitul intrarii
    string input = sirIntrare + 'e';
    string stareFinala = "q2";
    string stareInitiala = "q0"; 
    
    // Definim regulile de tranzitie: {stare curenta, simbol intrare, simbol stiva, stare urmatoare, acțiune stiva}
    vector<vector<string>> reguli = {
        {"q0", "0", "Z", "q0", "0Z"},
        {"q0", "0", "0", "q0", "00"},
        {"q0", "1", "0", "q1", "e"},
        {"q1", "1", "0", "q1", "e"},
        {"q1", "e", "Z", "q2", "Z"}
    };

    char simbolCurentStiva = 'Z';
    string stareCurenta = stareInitiala;

    // Procesam fiecare caracter din sir
    for (char caracter : input) 
    {
        bool gasit = false;
        for (const auto& regula : reguli) 
        {
            // Verif regula
            if (regula[0] == stareCurenta && regula[1][0] == caracter && regula[2][0] == simbolCurentStiva) 
            {
                stareCurenta = regula[3]; // actualizam st curenta
                // efectuam actiunea asupra stivei conform regulii
                if (regula[4].length() == 2) 
                {
                    stiva.push(caracter);
                } 
                else if (regula[4] == "e" && stiva.size() > 1) 
                {
                    stiva.pop();
                }
                gasit = true;
                break;
            }
        }
        if (!gasit) 
        {
            break;
        }
        simbolCurentStiva = stiva.top();
    }

    // Verif daca automatul a ajuns in stare de acceptare
    if (stareCurenta == "q2") 
    {
        cout << "Da\n"; 
    } 
    else 
    {
        cout << "Nu\n";  
    }
}

int main() 
{
    string sirIntrare;
    cout << "Introduceti sirul de intrare: ";
    cin >> sirIntrare;

    pda(sirIntrare);

    return 0;
}

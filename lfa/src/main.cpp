#include <deque>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include "../include/json.hpp"
#include "../include/Automat.h"
using namespace std;
using json = nlohmann::json;

int o = 0;
char cuv[50];
void tema1() {
    const int n = 2000, m = 50;
    char cuv[n];
    Automat a, b;

    Input citire_aux("../input.txt");
    Input citire;
    citire = citire_aux;
    // cout << citire << "\n";
    States S{citire};
    // cout << S << "\n";
    Sigma A(citire);
    // cout << A << "\n";
    Transitions T(citire, S, A);
    // cout << T << "\n";
    a = Automat{citire};
    b = a;
    if (a.isValid() == false) {
        exit(0);
    }
    cout << b;
    a.toDFA();
    cout << "\n\n Automat to DFA\n\n";
    cout << a;
    while (true) {
        cout << "\n\n Introduceti cuvantul pentru verificare:\n\n";
        cin >> cuv;
        cout << "(?)DFA: " << a.cuvant(cuv) << "\n*NFA / (DFA initial): " << b.cuvant(cuv) << "\n\n";
    }
    exit(0);
}


void tema2()
{
    ifstream file("../src/LFA-Assignment2_Regex_DFA.json");
    auto data = json::parse(file);
    for (auto ex : data) {
        cout << "\n\nName: " << ex["name"] << "\n" << "Regex: " << ex["regex"] << "\n";
        string regex = ex["regex"];
        Automat a(regex);
        a.toDFA();
       // cout << a;
        for (auto test : ex["test_strings"]) {
            string cuv = test["input"];
            bool rez = a.apartine_automat(cuv);
            bool exp = test["expected"];
            cout << test["input"] << " : " << ((rez == 1) ? "true" : "false") << " corect: " << test["expected"] << "\n";
            if ( rez != exp) {cout << "TIPAAAAAAA!"; exit(4 );};
        }
    }
}
int main()
{
 tema2();
}
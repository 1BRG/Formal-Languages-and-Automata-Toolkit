#include <deque>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
#include <set>

#include "../include/Automat.h"
using namespace std;


int o = 0;
char cuv[50];
void back(int k, int n, Automat &a, Automat &b) {
    if (k <= n + 1) {
        o ++;
        cuv[k] = '\0';
        if (a.cuvant(cuv)  != b.cuvant(cuv))
        cout << cuv << "\n" << "(?)DFA: " << a.cuvant(cuv) << "\n*NFA: " << b.cuvant(cuv) << "\n\n";
        //return;
    }
    else return;
    cuv[k - 1] = 'a';
    back(k + 1, n, a, b);
    cuv[k - 1] = 'b';
    back(k + 1, n, a, b);
    cuv[k - 1] = 'c';
    back(k + 1, n, a, b);
    cuv[k - 1] = 'd';
    back(k + 1, n, a, b);
}
int main()
{
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
        return 0;
    }
    cout << b;
    a.toDFA();
    cout << "\n\n Automat to DFA\n\n";
    cout << a;
    //back(1, 10, a, b);
   // cout << o << "\n";
    while (true) {
        cout << "\n\n Introduceti cuvantul pentru verificare:\n\n";
        cin >> cuv;
        cout << "(?)DFA: " << a.cuvant(cuv) << "\n*NFA / (DFA initial): " << b.cuvant(cuv) << "\n\n";
    }
    return 0;
}
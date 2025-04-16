//
// Created by Gabriel on 4/16/2025.
//

#ifndef AUTOMAT_H
#define AUTOMAT_H
#include "Transitions.h"
#include <deque>


class Automat
{

    static const int n = 2000, m = 50;
    States S;
    Transitions T;
    Sigma A;

    bool ok = true;
    void dfs(bool &valid, char cuv[], int stare, int poz, int len) const;
public:
    Automat& operator=(const Automat& other);
    Automat(const Automat& other);
    Automat() {}
    Automat(const Input &citire);
    Automat(const States &state, const Sigma &sigma, const Transitions &trans);
    bool cuvant(char cuv[]);
    bool isValid();
    bool isDFA() const;
    bool isNFA()const;
    void toDFA();
    friend ostream& operator<<(ostream& os, const Automat &a);
    ~Automat();
};



#endif //AUTOMAT_H

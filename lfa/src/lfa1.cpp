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
    //back(1, 10, a, b);
    // cout << o << "\n";
    while (true) {
        cout << "\n\n Introduceti cuvantul pentru verificare:\n\n";
        cin >> cuv;
        cout << "(?)DFA: " << a.cuvant(cuv) << "\n*NFA / (DFA initial): " << b.cuvant(cuv) << "\n\n";
    }
    exit(0);
}
deque <string> postfixat(string &s)
{
    map<string, int> prec;
    prec["+"] = prec["*"] = prec["?"] = 3;
    prec["."] = 2;
    prec["|"] = 1;
    prec["("] = -1;
    long long nr = 0;
    deque <string> rez, q;
    for(int i = 0; s[i]; i ++)
    {
        if(s[i] <= '9' && s[i] >= '0')
        {
            while(s[i] <= '9' && s[i] >= '0')
            {
                nr = nr * 10 + s[i] - '0';
                i ++;
            }
            i --;
            rez.push_back(to_string(nr));
            nr = 0;
        }
        else if (s[i] <= 'z' && s[i] >= 'a') {
            rez.push_back(string(1, s[i]));
        }
        else
        {
            string c;
            c += s[i];
            if(s[i] == '(')
                q.push_back(c);
            else if(s[i] == ')')
            {
                while(q.back() != "(")
                    rez.push_back(q.back()), q.pop_back();
                q.pop_back();
            }
            else
            {
                while(!q.empty() && prec[c] <= prec[q.back()])
                    rez.push_back(q.back()), q.pop_back();
                q.push_back(c);
            }
        }
    }
    while(!q.empty())
        rez.push_back(q.back()), q.pop_back();
    return rez;
}
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

void parsareRegex(string &regex) {
    for (int i = 0; regex[i]; i ++) {
        if (i != regex.length() - 1) {
            if (!strchr("(|.", regex[i]) && !strchr("|*.+?)", regex[i + 1])) {
                regex.insert(regex.begin() + i + 1, '.');
            }
        }
    }
}
string apartine_automat(Automat a, string cuv) {
    char c[2000];
    strcpy(c, cuv.c_str());
    return a.cuvant(c) == 1 ? "true" : "false";
}
Automat toAutomat(deque <string> p) {
    /*
     : . -> concatenare
     : | -> alternare
     : * -> stelat
     : + -> plus
     : ? -> misterios
     */
    deque <Automat> q;
    while(!p.empty())
    {
        string c = p.front();
        p.pop_front();
        if((c[0] >= '0' && c[0] <= '9') || (c[0] <= 'z' && c[0] >= 'a')) {
            Automat aux(c[0]);
            q.push_back(aux);
        }
        else
        {
            Automat a2 = q.back(); q.pop_back();
            if (c[0] == '.') {
                Automat a1 = q.back(); q.pop_back();
                a1.concatenare(a2);
                q.push_back(a1);
              //  cout << a1 << endl << "size:" << a1.s().size() << endl;
            }
            else if (c[0] == '|') {
                Automat a1 = q.back(); q.pop_back();
                a1.alternare(a2);
                q.push_back(a1);
            //    cout << a1 << endl << "size:" << a1.s().size() << endl;
            }
            else if (c[0] == '*') {
                a2.stelat();
                q.push_back(a2);
  //              cout << a2 << endl << "size:"
//                << a2.s().size() << endl;
            }
            else if (c[0] == '+') {
                a2.plus();
                q.push_back(a2);
                //cout << a2 << endl << "size:" << a2.s().size() << endl;
            }
            else if (c[0] == '?') {
                a2.misterios();
                q.push_back(a2);
            //    cout << a2 << endl << "size:" << a2.s().size() << endl;
            }
            else {
                cout << "Nu trebuia ...\n";
            }
        }
    }
    return q.back();
}
void tema2()
{
    ifstream file("../src/LFA-Assignment2_Regex_DFA.json");
    auto data = json::parse(file);
    for (auto ex : data) {
        cout << "\n\nName: " << ex["name"] << "\n" << "Regex: " << ex["regex"] << "\n";
        deque <string> q;
        string regex = ex["regex"];
        parsareRegex(regex);
        q = postfixat(regex);
        Automat a = toAutomat(q);
       // cout << a;
        a.toNFA();
     //   cout << a;
        a.toDFA();
      //  cout << a << endl;
        for (auto test : ex["test_strings"]) {
            string rez = apartine_automat(a, test["input"]);
            bool exp = test["expected"];
            cout << test["input"] << " : " << rez << " corect: " << test["expected"] << "\n";
            bool rez1 = (rez == "true") ? 1 : 0;
            if ( rez1 != exp) {cout << "TIPAAAAAAA!"; exit(4 );};
        }
    }
}
int main()
{
 tema2();
}
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <map>
using namespace std;
string start;
char c[200], cuv[200];
bool valid = 1, v1, v2;
const int n = 5000;
struct da
{
    string nod;
    char a;
};
map<string, vector<da>>v;


char s[200];
char mat[5000][15];
int i;
int findState(const char mat[][15])
{
    for(int i = 0; true; i ++)
        if(strcmp(mat[i], "States:"))
        return i;
}
int findTran(char mat[][15])
{
    for(int i = 0; true; i ++)
        if(strcmp(mat[i], "Transitions:"))
        return i;
}
int findsigma(char mat[][15])
{
    for(int i = 0; true; i ++)
        if(strcmp(mat[i], "Sigma:"))
        return i;
}

map<string, bool> noduri, Final, Alfabet;
void State() {
    for (int i = findState(mat); true; i ++)
    {
        if (strcmp("End", mat[i]) == 0)
            break;
        if(mat[i][0] == '#')
            continue;
        strcpy(s, mat[i]);
        char *p = strtok(s, ", ");
        string nod;
        while (p)
        {
            strcpy(cuv, p);
            if (cuv[0] == 'S')
            {
                if (start != "\0")
                    valid = false;
                else start = nod, v1 = 1;
            }
            else if (cuv[0] == 'F')
                Final[nod] = 1, v2 = 1;
            else
                noduri[cuv] = 1;
        }
    }
}
void sigma() {
    for (int i = findsigma(mat); true; i ++)
    {
        if (strcmp("End", mat[i]) == 0)
            break;
        if(mat[i][0] == '#')
            continue;
        strcpy(s, mat[i]);
        Alfabet[s] = 1;
    }
}
void Transition() {
    for (int i = findState(mat); true; i ++)
    {
        if (strcmp("End", mat[i]) == 0)
            break;
        if(mat[i][0] == '#')
            continue;
        strcpy(s, mat[i]);
        char *p = strtok(s, ", ");
        string nod;
        char litera;
        int ct = 0;
        while (p)
        {
            ct ++;
            strcpy(cuv, p);
            if (ct == 1 || ct == 3) {
                if (noduri[cuv] == 0)
                    valid = false;
                break;
                if (ct == 1)
                    nod = cuv;
                else v[nod].push_back({cuv, litera});
            }
            else if (strlen(cuv) > 1)
                valid = false;
            else litera = cuv[0];
        }
    }
}
class Input {
    char mat[n][15];
    //bool ok = true; optional;
public:
    int findState() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "States:"))
                return i;
    }
    int findTrans() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "Transitions:"))
                return i;
    }
    int findSigma() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "Sigma:"))
                return i;
    }
    void Matrice(char copie[][15]) const{
        for (int i = 0; i < n; i++) {
            strcpy(copie[i], mat[i]);
        }
    }
};
class States
{
    bool ok = true;
    map<string, int> q;
protected:
    int start = 0;
    bool final[n] = {false};
public:
    bool isValid() const
    {
        return ok;
    }
    States(const Input &citire) {
        char mat[n][15];
        citire.Matrice(mat);
        char s[15];
        int ct = 0;
        bool existaStart = false;
        for (int i = citire.findState(); true; i ++) {
            if (strcmp("End", mat[i]) == 0)
                break;
            if(mat[i][0] == '#')
                continue;
            strcpy(s, mat[i]);
            char *p = strtok(s, ", ");
            int nod;
            while (p)
            {
                strcpy(cuv, p);
                if (cuv[0] == 'S')
                {
                    if (start != 0)
                        ok = false;
                    else start = nod, existaStart = 1;
                }
                else if (cuv[0] == 'F')
                    final[nod] = 1;
                else
                    nod = q[cuv] != 0 ? q[cuv]: ++ ct, q[cuv] = ct;
            }
        }
        if (existaStart == 0)
            ok = false;
    }
    int translate(const string& nod) const {
        map<string, int>::const_iterator it = q.find(nod);
        if (it != q.end())
            return it->second;
        else return -1;
    }
};
class Sigma
{
    bool ok = true;
protected:
    bool alfabet[257] = {false};
    public:
    bool isValid() const
    {
        return ok;
    }
    Sigma(const Input &citire) {
        char mat[n][15], s;
        citire.Matrice(mat);
        for (int i = citire.findSigma(); true; i ++)
        {
            if (strcmp("End", mat[i]) == 0)
                break;
            if(mat[i][0] == '#')
                continue;
            s = mat[i][0];
            alfabet[s] = 1;
        }
    }
    bool apartineAlfabet(char ch) const {
        return alfabet[ch];
    }

};
struct nu {
    int nod;
    char a;
};
class Transitions
{
    bool ok = true;
protected:

    vector<nu> v[n];
    public:

    Transitions(const Input &citire, const States &state, const Sigma &sigma) {
        char mat[n][15], s[15];
        citire.Matrice(mat);
        for (int i = citire.findTrans(); ok; i ++)
        {
            if (strcmp("End", mat[i]) == 0)
                break;
            if(mat[i][0] == '#')
                continue;
            strcpy(s, mat[i]);
            char *p = strtok(s, ", "), cuv[15];
            int nod;
            char litera;
            int ct = 0;
            while (p && ok)
            {
                ct ++;
                strcpy(cuv, p);
                if (ct == 1 || ct == 3) {
                    if (state.translate(cuv) == -1) {
                        ok = false;
                        break;
                    }
                    if (ct == 1)
                        nod = state.translate(cuv);
                    else v[nod].push_back({nod, litera});
                }
                else if (strlen(cuv) > 1 || sigma.apartineAlfabet(cuv[0]))
                    ok = false;
                else litera = cuv[0];
            }
        }
    }
    void trimiteMuchii(vector <nu> w[n]) const {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < v[i].size(); j ++) {
                w[i].push_back(v[i][j]);
            }
        }
    }
    bool isValid() const
    {
        return ok;
    }

};
class Automat
{
    bool ok = true;

    vector<nu> v[n];
    public:
    Automat(){}
    Automat(const States &state, const Sigma &sigma, const Transitions &trans)
    {
        bool ok = 0;
        ok = ok & state.isValid() & sigma.isValid() & trans.isValid();

        if(!ok)
            cout << "Automat invalid\n", this->ok = 0;
        trans.trimiteMuchii(v);
        state.

    }
    bool cuvant(char cuv[]) {
        dfs(valid, cuv, 1, 0, strlen(cuv));
    }
    void dfs(bool valid, char cuv[], int stare, int poz, int len) const
    {
        if (valid)
            return;
        if (poz == len)
        {
            if (Final[stare] == 1)
                valid = true;
            return;
        }
        for (int i = 0; i < v[stare].size(); i++)
        {
            if (!valid && v[stare][i].a == cuv[poz])
                dfs(cuv, v[stare][i].nod, poz + 1, len);
        }
    }
};

int main()
{
    cin >> cuv;
    valid = true;
    ifstream f("input.txt");
    while (f.getline(mat[++i], sizeof(mat[i])));
    State();
    sigma();
    Transition();
    if (valid == 0 || v1 == 0 || v2 == 0)
    {cout << "Automat invalid";}
    else {
        cout << "Introdu un cuvant:\n";
        cin >> cuv;
        dfs(cuv, start, 0, strlen(cuv));
        if (valid == 0)
            cout << "Cuvant invalid";
        else cout << "Cuvant valid";
    }
    return 0;
}

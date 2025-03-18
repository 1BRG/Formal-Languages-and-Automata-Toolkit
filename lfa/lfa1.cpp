#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <map>
using namespace std;
const int n = 100;
char cuv[n];
class Input
{
    char mat[n][15] = {'\0'};
    ///bool ok = true;
public:
    Input() {}
    Input(const string &filename)
    {
        ifstream f(filename);
        int ct = 0, i = 0;
        char c[200];
        while (f.getline(mat[++i], sizeof(mat[i])) && ct - 3)
            ct +=  (strcmp(mat[i], "END") == 0);
    }
    int findState() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "States:") == 0)
                return i;
    }
    int findTrans() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "Transitions:") == 0)
                return i;
    }
    int findSigma() const
    {
        for(int i = 0; true; i ++)
            if(strcmp(mat[i], "Sigma:") == 0)
                return i;
    }
    void Matrice(char copie[][15]) const
    {
        for (int i = 0; i < n; i++)
        {
            strcpy(copie[i], mat[i]);
        }
    }
    friend ostream& operator<<(ostream& os, const Input& a)
    {
        os << "Despre input \n";
        os << "States incepe la linia: " << a.findState() << "\n";
        os << "Sigma incepe la linia: " << a.findSigma() << "\n";
        os << "Transitions incepe la linia: " << a.findTrans() << "\n";
        return os;
    }
    ~Input() //cout << "Destructor";
    {
    }

};
class States
{
    bool ok = true;
    map<string, int> q;
protected:
    int start = 0;
    bool final[n];
public:
    States() {}
    bool validStates() const
    {
        return ok;
    }
    States(const Input &citire)
    {
        for(int i = 0; i < n; i ++)
            final[i] = 0;
        char mat[n][15], cuv[15];
        citire.Matrice(mat);
        char s[15];
        int ct = 0;
        bool existaStart = false;
        for (int i = citire.findState() + 1; true; i ++)
        {
            if (strcmp("END", mat[i]) == 0)
                break;
            if(mat[i][0] == '#')
                continue;
            strcpy(s, mat[i]);
            char *p = strtok(s, ", ");
            int nod;
            int ct1 = 0;
            while (p)
            {
                strcpy(cuv, p);
                if (cuv[0] == 'S' && ct1 != 0)
                {
                    if (start != 0)
                        ok = false;
                    else start = nod, existaStart = 1;
                }
                else if (cuv[0] == 'F' && ct1 != 0)
                    final[nod] = 1;
                else
                    nod = q[cuv] != 0 ? q[cuv]: ++ ct, q[cuv] = ct;
                ct1 += 1;
                p = strtok(NULL, ", ");
            }
        }
        if (existaStart == 0)
            ok = false;
    }
    int translate(const string& nod) const
    {
        map<string, int>::const_iterator it = q.find(nod);
        if (it != q.end())
            return it->second;
        else return -1;
    }
    bool stareFinala(int stare) const
    {
        return final[stare];
    }
    int nodStart() const
    {
        return this->start;
    }
    friend ostream& operator<<(ostream& os, const States &a)
    {
        os << "Despre States:\n";
        if(a.ok == false || (a.start == 0 ))
        {
            os << "States invalid\n";
            return os;
        }
        os << "Nod de start: " << a.start << "\n";
        os << "Noduri de final: ";
        int ct = 0;
        for(int i = 0; i < n; i ++)
            if(a.final[i])
                os << i << " ", ct += 1;
        if(!ct)
            os << "Automatul nu are stari finale";
        os << "\n";
        return os;
    }
    ~States() //cout << "Destructor";
    {
    }
};
class Sigma
{
    bool ok = true;
protected:
    bool alfabet[257];
public:
    Sigma () {}
    bool validSigma() const
    {
        return ok;
    }
    Sigma(const Input &citire)
    {
        for(int i = 0; i < 257; i ++)
            alfabet[i] = 0;
        char mat[n][15], s;
        citire.Matrice(mat);
        for (int i = citire.findSigma() + 1; true; i ++)
        {
            if (strcmp("END", mat[i]) == 0)
                break;
            if(mat[i][0] == '#')
                continue;
            s = mat[i][0];
            alfabet[s] = 1;
        }
    }
    bool apartineAlfabet(char ch) const
    {
        return alfabet[ch];
    }
    friend ostream& operator<<(ostream& os, const Sigma &a)
    {
        os << "Alfabet: ";
        for(int i = 0; i < 255; i ++)
            if(a.alfabet[i])
                os << char(i) << " ";
        os << "\n";
        return os;
    }
    ~Sigma() //cout << "Destructor";
    {
    }

};
struct nu
{
    int nod;
    char a;
};
class Transitions
{
    bool ok = true;
protected:

    vector<nu> v[n];
    //  map<map<string, int>, vector<int>> w;
public:
    Transitions() {}
    Transitions(const Input &citire, const States &state, const Sigma &sigma)
    {
        char mat[n][15], s[15];
        citire.Matrice(mat);
        for (int i = citire.findTrans() + 1; ok; i ++)
        {
            if (strcmp("END", mat[i]) == 0)
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
                if (ct == 1 || ct == 3)
                {
                    if (state.translate(cuv) == -1)
                    {
                        ok = false;
                        break;
                    }
                    if (ct == 1)
                        nod = state.translate(cuv);
                    else v[nod].push_back({state.translate(cuv), litera});
                }
                else if (strlen(cuv) > 1 || !sigma.apartineAlfabet(cuv[0]))
                    ok = false;
                else litera = cuv[0];
                p = strtok(NULL, ", ");
            }
        }
    }/**
    void trimiteMuchii(vector <nu> w[n]) const
    {
        for (int i = 0; i < n; i ++)
        {
            for (int j = 0; j < v[i].size(); j ++)
            {
                w[i].push_back(v[i][j]);
            }
        }
    }*/
    void toAFD()
    {
        bool auxf[n];
        for(int i = 0; i < n; i ++)
            auxf[i] = 0;
        ///namchef
    }
    bool validTransitions() const
    {
        return ok;
    }
    char caracter(int stare, int i) const
    {
        return v[stare][i].a;
    }
    int Size(int stare)const
    {
        return v[stare].size();
    }
    int nod(int stare, int i) const
    {
        return v[stare][i].nod;
    }
    friend ostream& operator<<(ostream& os, const Transitions &a)
    {
        os << "Despre Transitions: \n";
        for(int i = 0; i < n; i ++)
            if(a.v[i].size() != 0)
            {
                os << i << ": ";
                for(int j = 0; j < a.v[i].size(); j ++)
                    os << "[" << a.v[i][j].a << "," << a.v[i][j].nod << "] ";
                os << "\n";
            }
            return os;
    }
    ~Transitions() //cout << "Destructor";
    {
    }

};
class Automat
{
    States S;
    Transitions T;
    Sigma A;
    bool ok = true;
    void dfs(bool &valid, char cuv[], int stare, int poz, int len) const
    {
        if (valid)
            return;
        if (poz == len)
        {
            if (S.stareFinala(stare))
                valid = true;
            return;
        }
        for (int i = 0; i < T.Size(stare); i++)
        {
            char ch = T.caracter(stare, i);
            int nod = T.nod(stare, i);
            if (!valid && (ch == cuv[poz] || ch == '$'))
                dfs(valid, cuv, nod, poz + 1, len);
        }
    }
public:
    Automat() {}
    Automat(const Input &citire): S(citire),A(citire)
    {
        T = Transitions{citire, S, A};
        bool ok = 1;
        ok = ok & S.validStates() & A.validSigma() & T.validTransitions();
        if(!ok)
            cout << "Automat invalid\n", this->ok = 0;
    }
    Automat(const States &state, const Sigma &sigma, const Transitions &trans):S(state), A(sigma), T(trans)
    {
        bool ok = 1;
        ok = ok & state.validStates() & sigma.validSigma() & trans.validTransitions();
        if(!ok)
            cout << "Automat invalid\n", this->ok = 0;

    }
    bool cuvant(char cuv[])
    {
        bool valid = 0;
        dfs(valid, cuv, S.nodStart(), 0, strlen(cuv));
        return valid;
    }
    bool isValid()
    {
        return ok;
    }
    ~Automat() //cout << "Destructor";
    {
    }
};

int main()
{
    Automat a;

    Input citire("../input.txt");
    cout << citire << "\n";
    States S(citire);
    cout << S << "\n";
    Sigma A(citire);
    cout << A << "\n";
    Transitions T(citire, S, A);
    cout << T << "\n";
    a = Automat{citire};
    cin >> cuv;
    cout << a.cuvant(cuv);
    return 0;
}
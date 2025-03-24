#include <deque>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
using namespace std;
class Input
{
    static const int n = 2000, m = 50;
    string mat[n];
    ///bool ok = true;
public:
    Input() {}
    Input(const string &filename)
    {
        ifstream f(filename);
        int ct = 0, i = 0;
        char c[200];
        while (getline(f, mat[++i]) && ct - 3)
            ct += (mat[i] == "End");
    }
    int findState() const
    {
        for(int i = 0; true; i ++)
            if(mat[i] == "States:")
                return i;
    }
    int findTrans() const
    {
        for(int i = 0; true; i ++)
            if(mat[i] == "Transitions:")
                return i;
    }
    int findSigma() const
    {
        for(int i = 0; true; i ++)
            if(mat[i] == "Sigma:")
                return i;
    }
    void Matrice(string copie[]) const
    {
        for (int i = 0; i < n; i++)
            copie[i] = mat[i];
    }
    friend ostream& operator<<(ostream& os, const Input& a)
    {
        os << "Despre input \n";
        os << "States incepe la linia: " << a.findState() << "\n";
        os << "Sigma incepe la linia: " << a.findSigma() << "\n";
        os << "Transitions incepe la linia: " << a.findTrans() << "\n";
        return os;
    }
    Input& operator=(const Input& other) {
       // std::cout << "Operator egal\n";
        for (int i = 0; i < n; i ++)
            this->mat[i] = other.mat[i];
        return *this;
    }
    Input(const Input& other) {
        //std::cout << "Constructor de Copiere\n";
        for (int i = 0; i < n; i ++)
            this->mat[i] = other.mat[i];
    }
    ~Input()
    {
        //cout << "Destructor";
    }

};
class States
{
    static const int n = 2000, m = 50;
    bool ok = true;
    map<string, int> q;
protected:
    int start = 0;
    bool final[n] = {false};
public:
    States& operator=(const States& other) {
        // std::cout << "Operator egal\n";
        for (int i = 0; i < n; i ++)
            this->final[i] = other.final[i];
        this->start = other.start;
        this->ok = other.ok;
        this->q = other.q;
        return *this;
    }
    States(const States& other) {
        //std::cout << "Constructor de Copiere\n";
        for (int i = 0; i < n; i ++)
            this->final[i] = other.final[i];
        this->start = other.start;
        this->ok = other.ok;
        this->q = other.q;
    }
    States() {}
    States(int start, bool final[])
    {
        this->start = start;
        memcpy(this->final, final, sizeof(final));
        for (int i = 0; i < n; i ++)
            q[to_string(i)] = i;
    }
    States(const Input& citire)
    {
        for(int i = 0; i < n; i ++)
            final[i] = false;
        string mat[n];
        citire.Matrice(mat);
        char s[m];
        int ct = 0;
        bool existaStart = false;
        for (int i = citire.findState() + 1; true; i ++)
        {
            if (mat[i] == "End")
                break;
            if(mat[i][0] == '#')
                continue;
            strcpy(s, mat[i].c_str());
            char *p = strtok(s, ", ");
            int nod;
            int ct1 = 0;
            while (p)
            {
                char cuv[m];
                strcpy(cuv, p);
                if (cuv[0] == 'S' && ct1 != 0)
                {
                    if (start != 0)
                        ok = false;
                    else start = nod, existaStart = true;
                }
                else if (cuv[0] == 'F' && ct1 != 0)
                    final[nod] = true;
                else
                    nod = q[cuv] != 0 ? q[cuv]: ++ ct, q[cuv] = ct;
                ct1 += 1;
                p = strtok(NULL, ", ");
            }
        }
        if (existaStart == 0)
            ok = false;
    }
    bool validStates() const
    {
        return ok;
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

    ~States()
    {
        //cout << "Destructor";
    }
};
class Sigma
{
    static const int n = 2000, m = 50;
    bool ok = true;
protected:
    bool alfabet[257];
public:
    Sigma& operator=(const Sigma& other) {
        // std::cout << "Operator egal\n";
        for (int i = 0; i < 257; i ++)
           this->alfabet[i] = other.alfabet[i];
        this->ok = other.ok;
        return *this;
    }
    Sigma(const Sigma& other) {
        //std::cout << "Constructor de Copiere\n";
        for (int i = 0; i < 257; i ++)
            this->alfabet[i] = other.alfabet[i];
        this->ok = other.ok;
    }
    Sigma () {}
    bool validSigma() const
    {
        return ok;
    }
    Sigma(const Input &citire)
    {
        for(int i = 0; i < 257; i ++)
            alfabet[i] = 0;
        string mat[n];
        char s;
        citire.Matrice(mat);
        for (int i = citire.findSigma() + 1; true; i ++)
        {
            if (mat[i] == "End")
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
    ~Sigma()
    {
        //cout << "Destructor";
    }

};
struct nu
{
    int nod;
    char a;
};
class Transitions
{
    static const int n = 2000, m = 50;
    char cuv[n];
    bool ok = true;
    bool dfa = true;
    int ct = 0;

protected:

    vector<nu> v[n];
    //dfa -> size() = 1 V nod,  nfa -> Ex. size() > 1
    map<char, set<int>> w[n];

public:
    Transitions& operator=(const Transitions& other) {
        // std::cout << "Operator egal\n";
        this->ok = other.ok;
        this->dfa = other.dfa;
        this->ct = other.ct;
        for (int i = 0; i < n; i ++)
            this->v[i] = other.v[i], this->w[i] = other.w[i], this->cuv[i] = other.cuv[i];
        return *this;
    }
    Transitions(const Transitions& other) {
        //std::cout << "Constructor de Copiere\n";
        this->ok = other.ok;
        this->dfa = other.dfa;
        this->ct = other.ct;
        for (int i = 0; i < n; i ++)
            this->v[i] = other.v[i], this->w[i] = other.w[i], this->cuv[i] = other.cuv[i];
    }
    Transitions() {}
    Transitions(const vector<nu> v[n])
    {
        for (int i = 0; i < n; i ++)
        {
            for (int j = 0; j < v[i].size(); j ++)
            {
                this->v[i].push_back(v[i][j]);
                w[i][v[i][j].a].insert(v[i][j].nod);
            }
        }
    }
    Transitions(const Input &citire, const States &state, const Sigma &sigma)
    {
        char s[m];
        string mat[n];
        citire.Matrice(mat);
        for (int i = citire.findTrans() + 1; ok; i ++)
        {
            if (mat[i] == "End")
                break;
            if(mat[i][0] == '#')
                continue;
            strcpy(s, mat[i].c_str());
            char *p = strtok(s, ", "), cuv[m];
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
                    else
                    {
                        int dest = state.translate(cuv);
                        v[nod].push_back({dest, litera});
                        w[nod][litera].insert(dest);
                        if (w[nod][litera].size() > 1)
                            this->dfa = false;
                    }
                }
                else if (strlen(cuv) > 1 || !sigma.apartineAlfabet(cuv[0]))
                    ok = false;
                else litera = cuv[0];
                p = strtok(NULL, ", ");
            }
        }
    }
    void getTransition(map<char, set<int>> w[n]) const
    {
        for (int i = 0; i < 255; i ++)
        {
            if (this->w[i].size() > 0)
            w[i] = this->w[i];
        }
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
    bool isDFA() const
    {
        return dfa;
    }
    bool isNFA()const
    {
        return !dfa;
    }
    friend ostream& operator<<(ostream& os, const Transitions &a)
    {
        os << "Despre Transitions: \n";
        if (a.isDFA())
            cout << "DFA\n";
        else cout << "NFA\n";
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
    void modificareTrans(vector <nu> v[n])
    {
        for (int i = 0; i < n; i ++)
        {
            this->v[i] =v[i];
        }
        dfa = true;

    }
    ~Transitions()
    {
        //cout << "Destructor";
    }

};

class Automat
{
    static const int n = 2000, m = 50;
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
    Automat& operator=(const Automat& other) {
        // std::cout << "Operator egal\n";
        this->S = other.S;
        this->T = other.T;
        this->A = other.A;
        this->ok = other.ok;
        return *this;
    }
    Automat(const Automat& other) {
        //std::cout << "Constructor de Copiere\n";
        this->S = other.S;
        this->T = other.T;
        this->A = other.A;
        this->ok = other.ok;
    }
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
    bool isDFA() const
    {
        return T.isDFA();
    }
    bool isNFA()const
    {
        return T.isNFA();
    }
    void toDFA()
    {
        if (T.isDFA() == true)
            return;
        bool auxf[n];
        for (int i = 0; i < n; i ++)
            auxf[i] = 0;
        auxf[S.nodStart()] = S.stareFinala(S.nodStart());
        vector<nu> aux[n];
        map<char, set<int>> w[n];
        T.getTransition(w);


        // hash pentru un set de noduri
        map<long long, map<char, set<int>>> hash;
        // daca hash a mai fost vizitat
        map<long long, bool> viz;
       // map<long long, bool> viz1;
        // din hash in nod
        map<long long, int> trad;

        const int b = 5009, mod = 1e9 + 7;
        int ct = 0;
        // T.toDFA();
        deque<long long> q;
        q.push_back(S.nodStart());
        // for (map<char, set<int>> :: iterator i = w[S.nodStart()].begin(); i != w[S.nodStart()].end(); i ++)
        //     hash[S.nodStart()][i->first] = i->second;
        for (int i = 0; i < n; i ++) {
            if (!w[i].empty())
                hash[i] = w[i], w[i].clear();
        }

        //[1], alcatuirea hashului
        hash[S.nodStart()][1].insert(S.nodStart());
        trad[S.nodStart()] = ++ct;
        while (!q.empty())
        {
            int nod = q.front();
            q.pop_front();

            viz[nod] = true;
            map<char, set<int>> dest;
            // for (map<char, set<int>> :: iterator i = hash[nod].begin(); i != hash[nod].end(); i ++)
            //     dest[i->first].insert(i->second.begin(), i->second.end());
            for (set<int> :: iterator i = hash[nod][1].begin(); i != hash[nod][1].end(); i ++)
                // if (*i < n)
                //     for (map<char, set<int>> :: iterator j = w[*i].begin(); j != w[*i].end(); j ++)
                //     {
                //         dest[j ->first].insert(j->second.begin(), j->second.end());
                //     }
                // else
                    // if (viz1[*i] == 1)
                        for (map<char, set<int>> :: iterator j = hash[*i].begin(); j != hash[*i].end(); j ++) {
                            if (j->first != 1)
                                dest[j ->first].insert(j->second.begin(), j->second.end());
                        }
                    // for (map<char, set<int>> :: iterator j = hash[*i].begin(); j != hash[*i].end(); j ++)
                    // {
                    //     dest[j ->first].insert(j->second.begin(), j->second.end());
                    // }

            for (map<char, set<int>> :: iterator i = dest.begin(); i != dest.end(); i ++)
            {
                long long node = 0;
                bool ok = 0;
                for (set<int> :: iterator j = i->second.begin(); j != i->second.end(); j ++)
                {
                    ok = ok | S.stareFinala(*j);
                    node *= b, node += *j, node %= mod;
                    // hash[node][i->first].insert(w[*j][i->first].begin(), w[*j][i->first].end());
                }
                if (i->second.size() > 1) {
                    node += n + 1;
                }
                else if (i->second.size() == 0)
                    continue;
                if (viz[node] == 0)
                {
                    hash[node][1].insert(dest[i->first].begin(), dest[i->first].end());
                    hash[nod][i->first] = dest[i->first];
                    viz[node] = 1;
                    q.push_back(node);
                    trad[node] = ++ct;
                    aux[trad[nod]].push_back({ct, i->first});
                    auxf[ct] = ok;
                }
                else
                {
                    aux[trad[nod]].push_back({trad[node], i->first});
                    hash[node][i->first] = dest[i->first];
                }
            }
        }
        T.modificareTrans(aux);
        S = {States {1, auxf}};
    }
    friend ostream& operator<<(ostream& os, const Automat &a)
    {
        os << "Despre Automat: \n";
        os << a.S << "\n" << a.A << "\n" << a.T << "\n";
        return os;
    }
    ~Automat()
    {
        //cout << "Destructor";
    }
};

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
    cout << b;
    a.toDFA();
    cout << "\n\n Automat to DFA\n\n";
    cout << a;
    cin >> cuv;
    cout << a.cuvant(cuv);
    return 0;
}

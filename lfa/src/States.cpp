//
// Created by Gabriel on 4/16/2025.
//

#include "../include/States.h"

    States& States::operator=(const States& other) {
        // std::cout << "Operator egal\n";
        for (int i = 0; i < n; i ++)
            this->final[i] = other.final[i];
        this->start = other.start;
        this->ok = other.ok;
        this->q = other.q;
        return *this;
    }
    States::States(const States& other) {
        //std::cout << "Constructor de Copiere\n";
        for (int i = 0; i < n; i ++)
            this->final[i] = other.final[i];
        this->start = other.start;
        this->ok = other.ok;
        this->q = other.q;
    }
    States::States(int start, bool final1[])
    {
        this->start = start;
        memcpy(this->final, final1,  sizeof(final));
        for (int i = 0; i < n; i ++)
            q[to_string(i)] = i;
    }
    States::States(const Input& citire)
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
    bool States::validStates() const
    {
        return ok;
    }
    int States::translate(const string& nod) const
    {
        map<string, int>::const_iterator it = q.find(nod);
        if (it != q.end())
            return it->second;
        else return -1;
    }
    bool States::stareFinala(int stare) const
    {
        return final[stare];
    }
    int States::nodStart() const
    {
        return this->start;
    }
    ostream& operator<<(ostream& os, const States &a)
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
        for(int i = 0; i < States::n; i ++)
            if(a.final[i])
                os << i << " ", ct += 1;
        if(!ct)
            os << "Automatul nu are stari finale";
        os << "\n";
        return os;
    }

    States::~States()
    {
        //cout << "Destructor";
    }

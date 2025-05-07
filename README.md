## Structura proiectului

Proiectul este organizat pe module și directoare separate pentru a facilita mentenanța și extensibilitatea:

```
LFA/                             # Proiect (root în CLion)
├── cmake-build-debug/          # Directoriul generat de CLion pentru build
├── include/                    # Fișiere header (.h/.hpp)
│   ├── Automat.h
│   ├── Input.h
│   ├── Sigma.h
│   ├── States.h
│   ├── Transitions.h
│   └── json.hpp                # Biblioteca nlohmann::json (header-only)
├── src/                        # Cod sursă și resurse
│   ├── main.cpp                # Punctul de intrare (tema1 și tema2)
│   ├── Automat.cpp
│   ├── Transitions.cpp
│   ├── States.cpp
│   ├── Sigma.cpp
│   ├── Input.cpp
│   └── LFA-Assignment2_Regex_DFA.json  # Set de teste pentru regex → DFA (tema2)
├── input.txt                   # Exemplu de configurare NFA/DFA (tema1)
├── CMakeLists.txt              # Configurație CMake pentru CLion și linie de comandă
└── README.md                   # Documentația proiectului
```

### Descrierea principalelor componente

* **main.cpp**: implementează două fluxuri de lucru (`tema1()` și `tema2()`).

  * `tema1()`: citește un NFA/DFA din `input.txt`, îl validează și convertește în DFA, apoi permite testarea interactivă a cuvintelor.
  * `tema2()`: încarcă un fișier JSON cu expresii regulate și cazuri de test, construiește DFA echivalent și verifică automat apartenența șirurilor.
* **Automat**: clasa de nivel înalt care orchestrează parsing-ul, construcția NFA, conversia în DFA și metodele de testare a cuvintelor.
* **States**: gestionează mulțimea de stări, starea inițială și stările finale.
* **Sigma**: reprezentarea alfabetului acceptat de automat.
* **Transitions**: stochează și manipulează schema de tranziții (NFA sau DFA), inclusiv tranziții ε.
* **Input**: citește și parsează configurația din `input.txt`.
* **json.hpp**: folosit pentru parsarea fișierului JSON de teste (tema2) fără dependințe externe suplimentare.

## Cum se rulează codul

### Precondiții

* Compilator C++17 compatibil (de ex. `g++` >= 7.0)
* Biblioteca header-only `nlohmann::json` inclusă în `include/json.hpp`

### Build cu Makefile

În directorul rădăcină al proiectului, rulează:

```sh
make all
```

Acest lucru va produce executabilul `run_automat`.

Pentru a curăța fișierele obiect generate:

```sh
make clean
```

### Executare

1. **Tema 1** (NFA/DFA din text + conversie interactivă):

   ```sh
   ./run_automat tema1
   ```

   * Citește definiția automatelor din `input.txt`.
   * Afișează automatul inițial și DFA-ul rezultat.
   * Permite introducerea interactivă a cuvintelor pentru testare.

2. **Tema 2** (Regex → DFA + teste automate):

   ```sh
   ./run_automat tema2
   ```

   * Încarcă `src/LFA-Assignment2_Regex_DFA.json`.
   * Convertește expresiile regulate în DFA (utilizând parsare postfix, Thompson, subset construction).
   * Rulează testele din JSON și raportează rezultatele.

> **Notă**: Executabilul analizează argumentul `tema1` sau `tema2` din `argv[1]`. În lipsă, default-ul este `tema2`.

## Decizii de implementare

1. **Fără biblioteci externe pentru automate**

   * Toată logica de parsing, construție NFA și conversie în DFA a fost scrisă "from scratch".

2. **Parser regex & Shunting-Yard**

   * Expresia regulată este întâi tokenizată, se inserează operatorul de concatenare implicit (`.`), apoi se transformă în forma postfixată.

3. **Algoritmul lui Thompson**

   * Construcția NFA folosește clase `State`/`nu` și tranziții ε pentru fiecare operator (`*`, `+`, `?`, `|`, `.`).

4. **Construirea DFA**

   * Subset construction (clasă `Automat::toDFA()`): stările DFA sunt mulțimi de stări NFA, calculate prin epsilon-closure.

5. **Gestionarea stărilor și tranzițiilor**

   * `States` folosește `map<string,int>` pentru traducerea numelor de stări din fișier.
   * `Transitions` stochează vectori de structuri `nu` și un map intern pentru tranziții multiple (pentru NFA).

6. **Testare JSON**

   * Pentru `tema2`, folosește `nlohmann::json` pentru a încărca cazurile de test și a verifica automat rezultatele.

7. **Performanță și limite**

   * Dimensiunea maximă a automatelor este stabilită la `n = 2000` stări și cuvinte de lungime maximă `m = 50`.
   * Utilizare extensivă a containerelor STL (`vector`, `map`, `set`, `deque`) pentru claritate și siguranță.



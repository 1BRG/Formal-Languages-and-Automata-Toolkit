# Proiect LFA - Tema 1, 2 și 3

## Structura proiectului

Proiectul este organizat pe module și directoare separate:

```
LFA/                             # Root proiect
├── cmake-build-debug/          # Directory build CLion
├── include/                    # Headere (.h/.hpp)
│   ├── Automat.h               # Tema 1-2
│   ├── Input.h                 # Tema 1-2
│   ├── Sigma.h                 # Tema 1-2
│   ├── States.h                # Tema 1-2
│   ├── Transitions.h           # Tema 1-2
│   ├── json.hpp                # nlohmann::json
│   └── CFG.h                   # Tema 3
├── src/                        # Sursă și resurse
│   ├── main.cpp                # Punct de intrare (tema1, tema2, tema3, bonus)
│   ├── Automat.cpp             # Tema 1-2
│   ├── Transitions.cpp         # Tema 1-2
│   ├── States.cpp              # Tema 1-2
│   ├── Sigma.cpp               # Tema 1-2
│   ├── Input.cpp               # Tema 1-2
│   ├── CFG.cpp                 # Tema 3
│   ├── LFA-Assignment2_Regex_DFA.json  # Tema 2 tests
│   ├── aSb.in                  # CFG S → aSb | ε (tema 3)
│   └── aNbNcN.in               # CFG „bonus” a^n b^n c^n (tema 3)
├── input.txt                   # Tema 1 config NFA/DFA
├── CMakeLists.txt              # Config CMake (toate temele)
└── README.md                   # Documentație proiect
```

## Cum se rulează codul

### CLion (Recomandat)

1. File → Open → alege directorul root `LFA/`.
2. Build → Build Project (Ctrl+F10).
3. Run → Edit Configurations → adaugă configurări pentru `tema1`, `tema2`, `tema3` și `bonusTema3`.

### Linia de comandă (Linux)

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
# rulează:
./run_automat tema1        # Tema 1: NFA/DFA din input.txt
./run_automat tema2        # Tema 2: Regex → DFA (JSON tests)
./run_automat tema3        # Tema 3: CFG S→aSb|ε (generate, derive, recognize)
./run_automat bonusTema3   # Bonus: a^n b^n c^n (CFG + procedural verify)
```

## Descrierea componentelor principale

### Tema 1 și 2 (Automate)

* **Automat**: clasa centrală parsează NFA/regex, construiește automat, convertește în DFA.
* **States, Sigma, Transitions, Input**: suport pentru citire și manipulare automată.
* **Shunting-Yard & Thompson**: parser regex și construcție NFA.
* **Subset Construction**: generare DFA.

### Tema 3 (Context-Free Grammar)

* **CFG.h / CFG.cpp**: clasa `CFG`:

  * Constructor din fișier `aSb.in` (pentru exemplu), dar **poți folosi orice gramatică independentă de context** validă în același format de intrare.
  * `generate(maxLen, maxCount)`: generează șiruri cu backtracking.
  * `derivation(target)`: returnează pașii derivării leftmost.
  * `recognize(target)`: validare membership cu pruning pe prefixe.
* **main.cpp**: `tema3()` apelează metodele de mai sus și afișează rezultate.

### Bonus (1)

* Fișierul `aNbNcN.in` conține o implementare "simulată" pentru a^n b^n c^n.
* Funcția `verify()` din `main.cpp` contorizează `a`, `b`, `c` procedural pentru recunoaștere.
* Comentariul din cod explică de ce limbajul a^n b^n c^n **nu este** context-free (necesită mai mult de o stivă).
* **Generalitate**: modulul `CFG` poate încărca și procesa orice gramatică independentă de context descrisă conform formatului de intrare (nu doar `aSb`). Dacă fișierul tău de intrare definește un CFG valid, codul tău va genera, deriva și recunoaște șiruri pentru acel CFG.

## Exemple de output pentru tema 3

```bash
./run_automat tema3
```

```
Cuvinte generate de gramatica S→aSb|ε (maxim 10, fiecare max 10 caractere):
ε
ab
aabb
aba…

Derivarea cuvântului "aaabbb":
S -> aSb -> aaSbb -> aaaSbbb -> aaabbb

Recunoaștere pentru "aaaabbb": Fals
```

## Decizii de implementare

1. **Backtracking manual**: fără librării externe pentru CFG.
2. **Pruning**: recunoașterea folosește verificarea prefixelor pentru eficiență.
3. **Structură modulară**: fiecare temă are propriile clase și fișiere.
4. **CMake**: configurat să includă și tema 3 plus bonus.

---

*Universitatea din București – Automate și Limbaje Formale*

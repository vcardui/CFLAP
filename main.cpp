/*
26 de septiembre de 2025
Vanessa Reteguín - 375533

Actividad 8: Práctica para AFND

Universidad Aútonoma de Aguascalientes
Ingeniería en Computación Inteligente (ICI)
Semestre V

Grupo 5 - A
Autómatas I
Ángel Eduardo Villegas Ortíz

Instrucciones:

- Instrucciones generales: Siga las indicaciones de cada etapa hasta construir
un Código en c/c++ que refleje el comportamiento de los AFND.

- Evaluación: Práctica de laboratorio secuencial con varias etapas. La versión
final será la evaluada y debe contener todas las evidencias solicitadas en un
solo documento.

Formato de Entrega:
- Espere las indicaciones para enviar la Etapa Final al espacio de Google
Classrom.
- Modifique este documento para enviar sus evidencias de cada etapa.
- En la etapa Final se envía su código en Formato c/cpp y el documento con las
evidencias solicitadas.

Sugerencias: El nivel del programación puede ser retador. Puede obtener ayuda de
otros compañeros o parejas, sin embargo, intente generar su propia solución.

Etapa 1
Descripción: Implemente un código en C/C++ que permita la definición de
Autómatas funcionales mediante consola (o método gráfico si lo considera
adecuado). Requerimientos:
- El usuario selecciona en un menú la opción “Crear Autómata”.
- En consola se ofrece la notación para declarar las Transiciones de un Autómata
(considere que las transiciones de AFND pueden ser a varios estados, verifique
que el ingreso de los datos permita capturar n estados para m cantidad de
transiciones).

- Implemente una función Estados_s_F que permita asignar el estado inicial  y el
o los nodos finales  del Autómata Creado.

- Muestre en consola la notación del Autómata Creado.

- Almacene en un archivo de texto plano la notación del Autómata Creado y asigne
un mecanismo sencillo para establecer un nombre al inicio del documento.


Pista de la siguiente Etapa:
- Función Generador de Cadenas que dado un Autómata Creado se muestren en
consola cadenas aceptadas.

*/

/* ------------ Resources / Documentation involved ------------- */
// [1] How to Take Multiple String Inputs in a Single Line in C++?:
// https://www.geeksforgeeks.org/cpp/take-multiple-string-inputs-in-single-line-in-cpp/

// [2] JSON for Modern C++: https://github.com/nlohmann/json
// Integrate by package manager:
// https://json.nlohmann.me/integration/package_managers/
// nlohmann JSON C++ Include issue:
// https://stackoverflow.com/questions/51707031/nlohmann-json-c-include-issue?rq=4

/* ------------------------- Libraries ------------------------- */
#include <iostream> /* cin/cout */
#include <map>
#include <nlohmann/json.hpp> /* JSON files manipulation */
#include <sstream>
#include <string> /* stoi() */

using namespace std;

/* ------------------------- Functions ------------------------- */

void diplayMenu() {
    cout << endl
         << "\n.----------------------."
            "\n||    -{ MENU }-     ||"
            "\n.---------------------."
            "\n| [1] Ejercicio 1     |"
            "\n| [2] Ejercicio 2     |"
            "\n| [3] Crear autómata  |"
            "\n| [4] Cargar autómata |"
            "\n|           [5] Salir |"
            "\n.---------------------.\n";
}

void endTitle() {
    cout << "\n  ^~^  , * ------------- *"
            "\n ('Y') ) |  Hasta luego! | "
            "\n /   \\/  * ------------- *"
            "\n(\\|||/)        FIN      \n";
}

void automatonTitle1() {
    cout << "\n          ======  -- 1 -->  ____"
            "\nStart |> || q0 ||          | q1 |"
            "\n  End <|  ======  <-- 1 --  ‾‾‾‾"
            "\n           |  ^             ^  |"
            "\n           0  |             |  0"
            "\n           |  0             0  |"
            "\n           v  |             |  v"
            "\n           ____  -- 1 -->  ____"
            "\n          | q2 |          | q3 |"
            "\n           ‾‾‾‾  <-- 1 --  ‾‾‾‾\n";

    cout << "\n^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^"
            "\n||                     Autómata I                     ||"
            "\n|| A = (Q, Σ, δ, s, F)                                ||"
            "\n|| Conjunto de Estados Posibles  Q: {q0, q1, q2, q3}  ||"
            "\n|| Alfabeto                      Σ: {0, 1}            ||"
            "\n|| Estado Inicial                s: q0                ||"
            "\n|| Conjunto de Estados finales   F: q1                ||"
            "\nv-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v\n";
}

void automatonTitle2() {
    cout << "\n                                                           /\\"
            "\n                                                         _v__|_"
            "\n                                               / - 0 -> |  q3  |"
            "\n                                              /       /  ‾‾‾‾‾‾ "
            " \\    /\\"
            "\n          ____          ____          ====== / <- 1 -/          "
            "  \\ _v__|_"
            "\nStart |> | q0 | - 0 -> | q1 | - 1 -> || q2 || ----------- 1 "
            "-----> |  q4  |"
            "\n          ‾‾‾‾          ‾‾‾‾          ======                    "
            "    ‾‾‾‾‾‾"
            "\n                                       <| End\n";

    cout << "\n^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^"
            "\n||                     Autómata II                        ||"
            "\n|| A = (Q, Σ, δ, s, F)                                    ||"
            "\n|| Conjunto de Estados Posibles  Q: {q0, q1, q2, q3, q4}  ||"
            "\n|| Alfabeto                      Σ: {0, 1}                ||"
            "\n|| Estado Inicial                s: q0                    ||"
            "\n|| Conjunto de Estados finales   F: q2                    ||"
            "\nv-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v\n";
}

string getNextState(string initialState, int transitionInput,
                    map<pair<string, int>, string> transitionMap) {
    auto it = transitionMap.find({initialState, transitionInput});

    if (it != transitionMap.end()) {
        cout << endl << "Estado Resultado: " << it->second << endl;
        cout << "T(" << initialState << ", " << transitionInput
             << ") = " << it->second << endl;
    } else {
        cout << endl << "[!] Transición no válida" << endl;
    }

    return it->second;
}

string getNextState1(string initialState, int transitionInput) {
    map<pair<string, int>, string> transitionMap = {
        {{"q0", 1}, "q1"}, {{"q1", 0}, "q3"}, {{"q2", 0}, "q0"},
        {{"q3", 1}, "q2"}, {{"q0", 0}, "q2"}, {{"q1", 1}, "q0"},
        {{"q2", 1}, "q3"}, {{"q3", 0}, "q1"}};

    auto it = transitionMap.find({initialState, transitionInput});

    if (it != transitionMap.end()) {
        cout << endl << "Estado Resultado: " << it->second << endl;
        cout << "T(" << initialState << ", " << transitionInput
             << ") = " << it->second << endl;
    } else {
        cout << endl << "[!] Transición no válida" << endl;
    }

    return it->second;
}

string getNextState2(string initialState, int transitionInput) {
    map<pair<string, int>, string> transitionMap = {
        {{"q0", 0}, "q1"}, {{"q1", 1}, "q2"}, {{"q2", 0}, "q3"},
        {{"q2", 1}, "q4"}, {{"q3", 0}, "q3"}, {{"q3", 1}, "q2"},
        {{"q4", 0}, "q3"}, {{"q4", 1}, "q4"}};

    auto it = transitionMap.find({initialState, transitionInput});

    if (it != transitionMap.end()) {
        cout << endl << "Estado Resultado: " << it->second << endl;
        cout << "T(" << initialState << ", " << transitionInput
             << ") = " << it->second << endl;
    } else {
        cout << endl << "[!] Transición no válida" << endl;
    }

    return it->second;
}

class Automaton {
   public:
    string automatonName;
    vector<string> posibleStates;
    vector<string> alphabet;
    string initialState;
    vector<string> finalStates;
    map<pair<string, string>, string> transitionMap;

    void printAtributes() {
        int i;

        cout << endl
             << "-------------------<{ " << automatonName
             << " }>-------------------";
        cout << endl << "A = (Q, Σ, δ, s, F)";
        cout << endl << "Conjunto de Estados Posibles  Q: {";
        for (i = 0; i < posibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << posibleStates[i];
        }
        cout << "}";
        cout << endl << "Alfabeto                      Σ: {";
        for (i = 0; i < alphabet.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << alphabet[i];
        }
        cout << "}";
        cout << endl << "Estado Inicial                s: " << initialState;
        cout << endl << "Conjunto de Estados finales   F: {";
        for (i = 0; i < finalStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << finalStates[i];
        }
        cout << "}";

        cout << endl << "Funciones de transición       𝜹:";

        for (auto transition : transitionMap) {
            cout << "    T(" << transition.first.first << ", "
                 << transition.first.second << ") = " << transition.second
                 << endl;
        }

        cout << "---------------------------------------------------------";
    }

    Automaton(string _automatonName, vector<string> _posibleStates,
              vector<string> _alphabet, string _initialState,
              vector<string> _finalStates,
              map<pair<string, string>, string> _transitionMap) {
        automatonName = _automatonName;
        posibleStates = _posibleStates;
        alphabet = _alphabet;
        initialState = _initialState;
        finalStates = _finalStates;
        transitionMap = _transitionMap;
    }
};

/* - Automata - */
vector<Automaton> automata;

void getAutomaton() {
    /* - Auxiliaries - */
    int i;

    /* - Tokenize the input - */
    // [1] Using stringstream to tokenize the input based on the
    // custom delimiter
    string delimiter = ",";
    string token;

    /* - Store automaton attributes - */
    string automatonName;

    string posibleStatesInput;
    vector<string> posibleStates;

    string alphabetInput;
    vector<string> alphabet;

    string initialState;
    string finalState;

    string tempState;
    vector<string> tempPosibleStates;
    vector<string> finalStates;
    string addNewQuestion;

    map<pair<string, string>, string> transitionMap = {};
    string transitionInput;

    // States
    cout << endl
         << "Ingrese el Conjunto de Estados Posibles separados por ',' "
            "(q1,q2,q3):"
         << endl;
    getline(cin >> ws, posibleStatesInput);

    cout << endl << "[*] Estados registrados: ";
    stringstream ss1(posibleStatesInput);  // [1]
    while (getline(ss1, token, delimiter[0])) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace),
                    token.end());
        posibleStates.push_back(token);
        cout << token << " ";
    }
    cout << endl;

    // Alphabet
    cout << endl
         << "Ingrese elementos del alfabeto separados por ',' "
            "(a,1,b):"
         << endl;
    getline(cin >> ws, alphabetInput);

    cout << endl << "[*] Alfabeto registrado: ";
    stringstream ss2(alphabetInput);  // [1]
    while (getline(ss2, token, delimiter[0])) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace),
                    token.end());
        alphabet.push_back(token);
        cout << token << " ";
    }
    cout << endl;

    // Initial state
    cout << endl << "Seleccione un estado inicial (";
    for (i = 0; i < posibleStates.size(); i++) {
        if (i != 0) {
            cout << ", ";
        }
        cout << posibleStates[i];
    }
    cout << "):" << endl;
    while ((cin >> initialState) &&
           !(find(posibleStates.begin(), posibleStates.end(), initialState) !=
             posibleStates.end())) {
        cin.clear();
        cin.ignore();

        cout << endl << "Seleccione un estado inicial (";
        for (i = 0; i < posibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << posibleStates[i];
        }
        cout << "):" << endl;
    }

    cout << endl << "[*] Estado inicial registrado: " << initialState << endl;

    // Final state
    tempPosibleStates = posibleStates;
    addNewQuestion = "si";

    while (!(tempPosibleStates.empty()) &&
           (addNewQuestion == "si" || addNewQuestion == "Si")) {
        cout << endl << "Seleccione un(los) estado(s) final(es) (";
        for (i = 0; i < tempPosibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << tempPosibleStates[i];
        }
        cout << "):" << endl;
        while ((cin >> tempState) &&
               !(find(tempPosibleStates.begin(), tempPosibleStates.end(),
                      tempState) != tempPosibleStates.end())) {
            cin.clear();
            cin.ignore();

            cout << endl << "Seleccione un(los) estado(s) final(es) (";
            for (i = 0; i < tempPosibleStates.size(); i++) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << tempPosibleStates[i];
            }
            cout << "):" << endl;
        }

        finalStates.push_back(tempState);
        tempPosibleStates.erase(find(tempPosibleStates.begin(),
                                     tempPosibleStates.end(), tempState));
        cout << endl << "[*] Estado final registrado: " << tempState << endl;

        if (!(tempPosibleStates.empty())) {
            cout << endl << "¿Desea agregar un nuevo estado final? (si/no): ";
            while ((cin >> addNewQuestion) &&
                   !((addNewQuestion == "si") || (addNewQuestion == "no") ||
                     (addNewQuestion == "Si") || (addNewQuestion == "No"))) {
                cin.clear();
                cin.ignore();
            }
        }
    }

    cout << endl << "[*] Estados finales registrados: ";
    for (i = 0; i < finalStates.size(); i++) {
        cout << finalStates[i] << " ";
    }

    // Transitions
    cout << endl
         << "---> Ingrese las funciones de transición del autómata <---";
    addNewQuestion = "si";
    while (addNewQuestion == "si" || addNewQuestion == "Si") {
        i = 1;
        cout << endl << "     Transición #" << i << endl;

        cout << endl << "Seleccione un estado inicial (";
        for (i = 0; i < posibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << posibleStates[i];
        }
        cout << "):" << endl;
        while ((cin >> initialState) &&
               !(find(posibleStates.begin(), posibleStates.end(),
                      initialState) != posibleStates.end())) {
            cin.clear();
            cin.ignore();

            cout << endl << "Seleccione un estado inicial (";
            for (i = 0; i < posibleStates.size(); i++) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << posibleStates[i];
            }
            cout << "):" << endl;
        }

        cin.clear();
        cin.ignore();

        // [BUG: 29/sep/2025]: Elemento no se captura hasta obtener una segunda
        // entrada
        cout << endl << "Seleccione un elemento del alfabeto (";
        for (i = 0; i < alphabet.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << alphabet[i];
        }
        cout << "):" << endl;
        while ((cin >> transitionInput) &&
               !(find(alphabet.begin(), alphabet.end(), transitionInput) !=
                 alphabet.end())) {
            cin.clear();
            cin.ignore();

            cout << endl << "Seleccione un estado inicial (";
            for (i = 0; i < alphabet.size(); i++) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << alphabet[i];
            }
            cout << "):" << endl;
        }

        auto it = transitionMap.find({initialState, transitionInput});

        if (it != transitionMap.end()) {
            cout << endl
                 << "[!] Transición ya registrada. Por favor ingrese una "
                    "diferente"
                 << endl;
        } else {
            while ((cin >> finalState) &&
                   !(find(posibleStates.begin(), posibleStates.end(),
                          finalState) != posibleStates.end())) {
                cin.clear();
                cin.ignore();

                cout << endl << "Seleccione el estado siguiente (";
                for (i = 0; i < posibleStates.size(); i++) {
                    if (i != 0) {
                        cout << ", ";
                    }
                    cout << posibleStates[i];
                }
                cout << "):" << endl;
            }

            transitionMap.insert({{initialState, transitionInput}, finalState});

            cout << endl
                 << "[*] Transición registrada: " << "T(" << initialState
                 << ", " << transitionInput
                 << ") = " << transitionMap.at({initialState, transitionInput})
                 << endl;

            i++;

            cout << endl << "¿Desea agregar una nueva transición? (si/no): ";
            while ((cin >> addNewQuestion) &&
                   !((addNewQuestion == "si") || (addNewQuestion == "no") ||
                     (addNewQuestion == "Si") || (addNewQuestion == "No"))) {
                cin.clear();
                cin.ignore();
            }
        }
    }

    // Name
    cout << endl << "Ingrese el nombre o identificador del autómata: " << endl;
    cin >> automatonName;

    Automaton newAutomaton(automatonName, posibleStates, alphabet, initialState,
                           finalStates, transitionMap);

    newAutomaton.printAtributes();
    automata.push_back(newAutomaton);
}

void loadAutomaton() {
    // [2]
}

int main() {
    /* ------------------------- Variables ------------------------- */
    /* - Menu - */
    int userChoice;
    bool run = true;
    bool validString = false;

    /* - Auxiliaries - */
    int i;

    string initialState;
    int transitionInput;

    string automatonInput;
    string nextState;
    string currentByte;

    string newTransition;
    map<pair<string, int>, string> transitionMap = {
        {{"q0", 1}, "q1"}, {{"q1", 0}, "q3"}, {{"q2", 0}, "q0"},
        {{"q3", 1}, "q2"}, {{"q0", 0}, "q2"}, {{"q1", 1}, "q0"},
        {{"q2", 1}, "q3"}, {{"q3", 0}, "q1"}};

    /* --------------------------- Code ---------------------------- */
    while (run == true) {
        diplayMenu();
        while (!((cin >> userChoice) && (userChoice >= 1 && userChoice <= 4))) {
            cin.clear();
            cin.ignore();
        }

        switch (userChoice) {
            case 1:
                automatonTitle1();
                while (validString == false) {
                    cout << "Ingrese una cadena: ";
                    cin >> automatonInput;

                    for (int i = 0; i < automatonInput.length(); i++) {
                        if ((automatonInput[i] == '0') ||
                            (automatonInput[i] == '1')) {
                            validString = true;
                        } else {
                            cout << endl
                                 << "    [!] Cadena no válida\n"
                                 << endl;
                            validString = false;
                            break;
                        }
                    }
                }

                cout << endl << "[*] Cadena válida" << endl;
                nextState = "q0";

                cout << endl << "[*] Estado inicial: " << nextState << endl;

                for (i = 0; i < automatonInput.length(); i++) {
                    currentByte = automatonInput[i];
                    // cout << endl << "[" << currentByte << "]";
                    nextState = getNextState1(nextState, stoi(currentByte));
                }

                cout << endl << "[*] Estado final: " << nextState << endl;

                if (nextState == "q0") {
                    cout << endl << "[*] Estado final: " << nextState << endl;
                } else {
                    cout << endl
                         << "[!] Estado final no válido: " << nextState << endl
                         << "[!] Cadena no válida";
                }

                break;

            case 2:
                automatonTitle2();
                while (validString == false) {
                    cout << "Ingrese una cadena: ";
                    cin >> automatonInput;

                    for (int i = 0; i < automatonInput.length(); i++) {
                        if ((automatonInput[i] == '0') ||
                            (automatonInput[i] == '1')) {
                            validString = true;
                        } else {
                            cout << endl
                                 << "    [!] Cadena no válida\n"
                                 << endl;
                            validString = false;
                            break;
                        }
                    }
                }

                cout << endl << "[*] Cadena válida" << endl;
                nextState = "q0";

                cout << endl << "[*] Estado inicial: " << nextState << endl;

                for (i = 0; i < automatonInput.length(); i++) {
                    currentByte = automatonInput[i];
                    // cout << endl << "[" << currentByte << "]";
                    nextState = getNextState2(nextState, stoi(currentByte));
                }

                if (nextState == "q2") {
                    cout << endl << "[*] Estado final: " << nextState << endl;
                } else {
                    cout << endl
                         << "[!] Estado final no válido: " << nextState << endl
                         << "[!] Cadena no válida";
                }
                break;

            case 3:
                getAutomaton();
                break;

            case 4:
                loadAutomaton();
                break;

            case 5:
                endTitle();
                run = false;
                break;
        }
    }

    return 0;
}

/*
 * +----------------------------------------------------------------------------+
 * | CARDUI TECH v1.0.0
 * +----------------------------------------------------------------------------+
 * | Copyright (c) 2024 - 2025, CARDUITECH.COM (www.carduitech.com)
 * | Vanessa Reteguín <vanessa@reteguin.com>
 * | Released under the MIT license
 * | www.carduitech.com/carduiframework/license/license.txt
 * +----------------------------------------------------------
 * | Author.......: Vanessa Reteguín <vanessa@reteguin.com>
 * | First release: September 26th, 2025
 * | Last update..: November 30th, 2025
 * | WhatIs.......: CFLAP - Main
 * +----------------------------------------------------------------------------+
 */

/*
14 de octubre de 2025
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

Etapa 2

Descripción: Modifique el código anterior que implemente un método
GenerarPalabras o GeneradorCadeneas que reciba una estructura Autómata
(Ya sea AFD o AFND) y sea capaz de desplegar las cadenas aceptadas.

Requerimientos:
-El usuario puede construir un Autómata mediante la etapa 1.
-La función GeneradorCadenas debe generar frases que recorran TODOS los
estados válidos del autómata.

*/

/* ------------ Resources / Documentation involved ------------- */
// [1] How to Take Multiple String Inputs in a Single Line in C++?:
// https://www.geeksforgeeks.org/cpp/take-multiple-string-inputs-in-single-line-in-cpp/

// [2] JSON for Modern C++: https://github.com/nlohmann/json
// Integrate by package manager:
// https://json.nlohmann.me/integration/package_managers/
// nlohmann JSON C++ Include issue:
// https://stackoverflow.com/questions/51707031/nlohmann-json-c-include-issue?rq=4

// [3] Alphabets And Permutations:
// https://github.com/vcardui/AlphabetsAndPermutations
// Homemade non-recursive permutations function

/* ------------------------- Libraries ------------------------- */
#include <fstream>  /* ifstream */
#include <iostream> /* cin/cout */
#include <list>
#include <map>
#include <nlohmann/json.hpp> /* [2] JSON files manipulation */
#include <sstream>           /* [1] stringstream tokenizer*/
#include <string>

using namespace std;

using json = nlohmann::json;

/* ------------------------- Functions ------------------------- */
void diplayMainMenu() {
    cout << endl
         << "\n.---------------------------."
            "\n||     -{ MAIN MENU }-     ||"
            "\n.---------------------------."
            "\n| [1] Autómatas de pila     |"
            "\n| [2] Autómatas             |"
            "\n|     finitos deterministas |"
            "\n|     y no deterministas    |"
            "\n|                 [3] Salir |"
            "\n.---------------------------.\n";
}

void diplay_PDA_TuringMachine_Menu() {
    cout << endl
         << "\n.----------------------------------."
            "\n|| -{ PDA y Máquinas de turing }- ||"
            "\n.----------------------------------."
            "\n| [1] Autómata de pila 1           |"
            "\n| [2] Autómata de pila 2           |"
            "\n| [3] Máquina de turing            |"
            "\n|                        [4] Salir |"
            "\n.----------------------------------.\n";
}

void diplay_AFD_AFND_Menu() {
    cout << endl
         << "\n.-----------------------."
            "\n||     -{ MENU }-      ||"
            "\n.-----------------------."
            "\n| [1] Crear autómata    |"
            "\n| [2] Cargar autómata   |"
            "\n| [3] Ejecutar autómata |"
            "\n| [4] Editar autómata   |"
            "\n| [5] Exportar autómata |"
            "\n|             [6] Salir |"
            "\n.-----------------------.\n";
}

void endTitle() {
    cout << "\n  ^~^  , * ------------- *"
            "\n ('Y') ) |  Hasta luego! | "
            "\n /   \\/  * ------------- *"
            "\n(\\|||/)        FIN      \n";
}

class Automaton {
   public:
    string automatonName;
    vector<string> posibleStates;
    vector<string> alphabet;
    string initialState;
    vector<string> finalStates;
    map<pair<string, string>, vector<string>> transitionMap;

    void printPosibleStates() {
        int i;
        cout << endl << "Conjunto de Estados Posibles  Q: {";
        for (i = 0; i < posibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << posibleStates[i];
        }
        cout << "}";
    }

    void printAlphabet() {
        int i;
        cout << endl << "Alfabeto                      Σ: {";
        for (i = 0; i < alphabet.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << alphabet[i];
        }
        cout << "}";
    }

    void printInitialState() {
        cout << endl << "Estado Inicial                s: " << initialState;
    }

    void printFinalStates() {
        int i;
        cout << endl << "Conjunto de Estados finales   F: {";
        for (i = 0; i < finalStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << finalStates[i];
        }
        cout << "}";
    }

    void printTransitionMap() {
        bool AFND = false;
        cout << endl << "Funciones de transición       𝜹:" << endl;

        for (auto transition : transitionMap) {
            cout << "    T(" << transition.first.first << ", "
                 << transition.first.second << ") = ";
            for (auto element : transition.second) {
                cout << element << " ";
            }
            if (transition.second.size() > 1) {
                AFND = true;
            }
            cout << endl;
        }

        cout << "               Tipo de autómata: ";
        if (AFND) {
            cout << "Autómata Finito\n                                 No "
                    "Determinístico (AFND)"
                 << endl;
        } else {
            cout << "Autómata Finito\n                                 "
                    "Determinístico (AFD)"
                 << endl;
        }
    }

    void printAtributes() {
        cout << endl
             << "-------------------<{ " << automatonName
             << " }>-------------------";
        cout << endl << "A = (Q, Σ, δ, s, F)";

        printPosibleStates();

        printAlphabet();

        printInitialState();

        printFinalStates();

        printTransitionMap();

        cout << "---------------------------------------------------------"
             << endl;
    }

    void runAutomaton() {
        /* - Auxiliaries - */
        int i;

        string currentCharacter;
        string automatonInput;
        vector<string> nextState;
        string currentByte;

        bool validChain = true;

        /* - Validators - */
        bool validString = false;

        while (validString == false) {
            cout << "Ingrese una cadena: ";
            cin >> automatonInput;

            for (int i = 0; i < automatonInput.length(); i++) {
                currentCharacter = automatonInput[i];
                auto it =
                    find(alphabet.begin(), alphabet.end(), currentCharacter);

                if (it != alphabet.end()) {
                    validString = true;
                } else {
                    cout << endl << "    [!] Cadena no válida\n" << endl;
                    validString = false;
                    break;
                }
            }
            validString = true;
        }

        cout << endl << "[*] Cadena válida" << endl;
        nextState.push_back(initialState);

        cout << endl << "[*] Estado inicial: " << nextState[0] << endl;

        for (i = 0; i < automatonInput.length(); i++) {
            currentByte = automatonInput[i];
            nextState =
                getNextState(true, nextState, currentByte, transitionMap);
        }

        for (auto state : nextState) {
            auto it = find(finalStates.begin(), finalStates.end(), state);

            if (it != finalStates.end()) {
                cout << endl << "[*] Estado final: " << state;
                cout << endl;
            } else {
                cout << endl << "[!] Estado final no válido: " << state << endl;
                cout << endl << "[!] Cadena no válida";
                validChain = false;
                break;
            }
        }

        cout << endl << "\n\n###### Resultado final ######";
        cout << endl << "Cadena: " << automatonInput;
        if (validChain == false) {
            cout << " NO es válida [X]";
        } else {
            cout << " es válida [✓]";
        }
    }

    void printChains() {
        /* Auxiliaries */
        int i, j;
        string currentPermutation;
        string fullstring;

        vector<string> permutations;
        int validStrings = 0, totalPermutations = 0;

        printAtributes();

        for (i = 0; i < alphabet.size(); i++) {
            permutations.push_back(alphabet[i]);
        }

        // [3] Homemade non-recursive permutations function
        for (i = 0; i <= (pow(alphabet.size(), alphabet.size()) - 1); i++) {
            currentPermutation = "";
            currentPermutation = decimalToNBase(i, alphabet.size(), alphabet);

            permutations.push_back(currentPermutation);
        }

        for (i = 0; i <= (pow(permutations.size(), permutations.size()) - 1);
             i++) {
            currentPermutation = "";
            currentPermutation =
                decimalToNBase(i, permutations.size(), permutations);

            // cout << currentPermutation << ": " <<
            // validChain(currentPermutation)
            //     << endl;

            if (validChain(currentPermutation)) {
                validStrings++;
                cout << "[" << validStrings << "] " << currentPermutation
                     << endl;
            }

            totalPermutations++;
        }

        cout << endl
             << "[*] Mostrando " << validStrings << " cadenas válidas de "
             << totalPermutations << " permutaciones totales generadas" << endl;
    }

    bool validChain(string fullstring) {
        vector<string> nextState;
        string currentByte;
        int i;
        bool validChain = true;

        // cout << "[" << fullstring << "]" << endl;

        nextState.push_back(initialState);

        // cout << endl << "[*] Estado inicial: " << nextState << endl;

        for (i = 0; i < fullstring.length(); i++) {
            currentByte = fullstring[i];
            nextState =
                getNextState(false, nextState, currentByte, transitionMap);
        }

        for (auto state : nextState) {
            auto it = find(finalStates.begin(), finalStates.end(), state);

            if (it != finalStates.end()) {
                // cout << endl << "[*] Estado final: " << state << endl;
                // return true;
            } else {
                // cout << endl
                //     << "[!] Estado final no válido: " << state << endl
                //     << "[!] Cadena no válida";
                validChain = false;
            }
        }

        return validChain;
    }

    Automaton(string _automatonName, vector<string> _posibleStates,
              vector<string> _alphabet, string _initialState,
              vector<string> _finalStates,
              map<pair<string, string>, vector<string>> _transitionMap) {
        automatonName = _automatonName;
        posibleStates = _posibleStates;
        alphabet = _alphabet;
        initialState = _initialState;
        finalStates = _finalStates;
        transitionMap = _transitionMap;
    }
    Automaton() {}

    static vector<string> getNextState(
        bool verbose, vector<string> initialState, string transitionInput,
        map<pair<string, string>, vector<string>> transitionMap) {
        vector<string> nextState;

        for (auto element : initialState) {
            auto it = transitionMap.find({element, transitionInput});

            if (it != transitionMap.end()) {
                if (verbose == true) {
                    cout << endl << "Estado Resultado: ";
                    for (auto state : it->second) {
                        cout << state << " ";
                    }
                    cout << endl;

                    cout << "T(" << element << ", " << transitionInput
                         << ") = ";
                    for (auto state : it->second) {
                        cout << state << " ";
                        nextState.push_back(state);
                    }
                    cout << endl;
                }
            } else {
                if (verbose == true) {
                    cout << endl << "[!] Transición no válida" << endl;
                }
            }
        }

        return nextState;
    }

    static string decimalToNBase(int decimalNum, int base,
                                 vector<string> digits) {
        string result = "";
        list<string> reverseResultList;

        int i;

        // vector<string> digits = {"0", "1", "2", "3", "4", "5", "6", "7", "8",
        // "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
        // "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

        if (decimalNum <= 1) {
            reverseResultList.push_front(digits[0]);
        }

        if (decimalNum == 0) {
            reverseResultList.push_front(digits[0]);
        }

        while (decimalNum > 0) {
            int remainder = decimalNum % base;
            // result += digits[remainder];
            reverseResultList.push_front(digits[remainder]);
            decimalNum /= base;
        }

        list<string>::iterator iter;

        if ((iter = reverseResultList.begin()) != reverseResultList.end()) {
            for (i = 0; i < reverseResultList.size(); ++i) {
                result += *iter;
                ++iter;
            }
        }

        return result;
    }
};

/* - Automata - */
vector<Automaton> automata;

void getAutomaton() {
    /* - Auxiliaries - */
    int i;
    vector<string> resultTransitions;

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

    map<pair<string, string>, vector<string>> transitionMap = {};
    string transitionInput;

    // States
    cout << endl
         << "Ingrese el Conjunto de Estados Posibles separados por ',' "
            "(q1,q2,q3):"
         << endl;
    getline(cin >> ws, posibleStatesInput);

    cout << endl << "[*] Estados registrados: ";
    stringstream ssPosibleStates(posibleStatesInput);  // [1]
    while (getline(ssPosibleStates, token, delimiter[0])) {
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
    stringstream ssAlphabet(alphabetInput);  // [1]
    while (getline(ssAlphabet, token, delimiter[0])) {
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

        // [To Do] Editar para usar do while
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

            cout << endl << "Seleccione un elemento del alfabeto (";
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

            vector<string> temp;
            temp.push_back(finalState);

            transitionMap.insert({{initialState, transitionInput}, temp});

            cout << endl
                 << "[*] Transición registrada: " << "T(" << initialState
                 << ", " << transitionInput << ") = ";

            for (auto transition :
                 transitionMap.at({initialState, transitionInput})) {
                cout << transition << " ";
            }
            cout << endl;

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
    /* - Auxiliaries - */
    int i;
    string fileRoute;

    /* - Automaton atributes - */
    string automatonName;
    vector<string> posibleStates;
    vector<string> alphabet;
    string initialState;
    vector<string> finalStates;
    map<pair<string, string>, vector<string>> transitionMap;

    vector<string> existingAutomata;

    cout << endl << "Ingrese ruta del archivo a cargar: ";
    cin >> fileRoute;  // test.json

    try {
        std::ifstream file(fileRoute);
        if (!file.is_open()) {
            throw std::ios_base::failure("[!] No se pudo abrir el archivo");
        }

        json data = json::parse(file);  // [2] Parse to JSON

        for (i = 0; i < automata.size(); i++) {
            existingAutomata.push_back(automata[i].automatonName);
        }

        for (auto& item : data.items()) {
            auto it = find(existingAutomata.begin(), existingAutomata.end(),
                           item.key());

            if (it != existingAutomata.end()) {
                cout << endl
                     << "[*] Autómata \"" << item.key() << "\" ya existe";
            } else {
                automatonName = item.value()["automatonName"];
                posibleStates = item.value()["posibleStates"];
                alphabet = item.value()["alphabet"];
                initialState = item.value()["initialState"];
                finalStates = item.value()["finalStates"];
                transitionMap = item.value()["transitionMap"];

                Automaton newAutomaton(automatonName, posibleStates, alphabet,
                                       initialState, finalStates,
                                       transitionMap);

                cout << endl << "[*] Nuevo autómata creado" << endl;
                automata.push_back(newAutomaton);
                newAutomaton.printAtributes();
            }
        }

    } catch (const std::ios_base::failure& e) {
        std::cerr << "I/O Error: " << e.what() << std::endl;
        // Log error, exit gracefully
    } catch (const std::exception& e) {
        std::cerr << "General Error: " << e.what() << std::endl;
    }
}

void executeAutomaton(int automatonChoice) {
    Automaton automaton = automata[automatonChoice];
    automaton.printAtributes();
    automaton.runAutomaton();
}

void displayChains(int automatonChoice) {
    Automaton automaton = automata[automatonChoice];
    automaton.printChains();
}

void editAutomaton() {
    int i, automatonChoice, atributeChoice, tempChoice;

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

    map<pair<string, string>, vector<string>> transitionMap = {};
    string transitionInput;

    vector<pair<int, pair<string, string>>> indexTransitionMap;
    int elementToDelete;
    string youSure;

    if (automata.empty()) {
        cout << endl
             << "[!] Memoria vacía. Favor de crear o cargar autómata" << endl;
    } else {
        cout << endl << "--- { Autómatas disponibles } ---" << endl;
        for (i = 0; i < automata.size(); i++) {
            cout << "[" << i + 1 << "] " << automata[i].automatonName << endl;
        }
        cout << "Seleccione un autómata: ";
        while (!(
            (cin >> automatonChoice) &&
            (automatonChoice >= 1 && automatonChoice < automata.size() + 1))) {
            cin.clear();
            cin.ignore();
        }
        automatonChoice--;

        Automaton automaton = automata[automatonChoice];

        automaton.printAtributes();

        cout << "Seleccione un atributo a editar del autómata: " << endl;
        cout << "[1] Conjunto de Estados Posibles" << endl
             << "[2] Alfabeto" << endl
             << "[3] Estado Inicial" << endl
             << "[4] Conjunto de Estados finales" << endl
             << "[5] Funciones de transición" << endl
             << "[6] Eliminar función de transición" << endl
             << "[7] Nombre del autómata" << endl;
        while (!((cin >> atributeChoice) &&
                 (atributeChoice >= 1 && atributeChoice <= 7))) {
            cin.clear();
            cin.ignore();
        }

        switch (atributeChoice) {
            case 1: {
                automaton.printPosibleStates();

                // States
                cout << endl
                     << "Ingrese el Conjunto de Estados Posibles separados "
                        "por ',' "
                        "(q1,q2,q3):"
                     << endl;
                getline(cin >> ws, posibleStatesInput);

                cout << endl << "[*] Estados registrados: ";
                stringstream ssPosibleStates(posibleStatesInput);  // [1]
                while (getline(ssPosibleStates, token, delimiter[0])) {
                    token.erase(
                        remove_if(token.begin(), token.end(), ::isspace),
                        token.end());
                    posibleStates.push_back(token);
                    cout << token << " ";
                }
                cout << endl;

                automaton.posibleStates = posibleStates;
            } break;
            case 2: {
                automaton.printAlphabet();

                // Alphabet
                cout << endl
                     << "Ingrese elementos del alfabeto separados por ',' "
                        "(a,1,b):"
                     << endl;
                getline(cin >> ws, alphabetInput);

                cout << endl << "[*] Alfabeto registrado: ";
                stringstream ssAlphabet(alphabetInput);  // [1]
                while (getline(ssAlphabet, token, delimiter[0])) {
                    token.erase(
                        remove_if(token.begin(), token.end(), ::isspace),
                        token.end());
                    alphabet.push_back(token);
                    cout << token << " ";
                }
                cout << endl;

                automaton.alphabet = alphabet;
            } break;

            case 3:
                automaton.printInitialState();

                // Initial state
                cout << endl << "Seleccione un estado inicial (";
                for (i = 0; i < automaton.posibleStates.size(); i++) {
                    if (i != 0) {
                        cout << ", ";
                    }
                    cout << automaton.posibleStates[i];
                }
                cout << "):" << endl;
                while ((cin >> initialState) &&
                       !(find(automaton.posibleStates.begin(),
                              automaton.posibleStates.end(),
                              initialState) != automaton.posibleStates.end())) {
                    cin.clear();
                    cin.ignore();

                    cout << endl << "Seleccione un estado inicial (";
                    for (i = 0; i < automaton.posibleStates.size(); i++) {
                        if (i != 0) {
                            cout << ", ";
                        }
                        cout << automaton.posibleStates[i];
                    }
                    cout << "):" << endl;
                }

                automaton.initialState = initialState;
                cout << endl
                     << "[*] Estado inicial registrado: "
                     << automaton.initialState << endl;

                break;

            case 4:
                automaton.printFinalStates();
                // automaton.finalStates.clear();

                // Final state
                tempPosibleStates.clear();
                tempPosibleStates = automaton.posibleStates;
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
                           !(find(tempPosibleStates.begin(),
                                  tempPosibleStates.end(),
                                  tempState) != tempPosibleStates.end())) {
                        cin.clear();
                        cin.ignore();

                        cout << endl
                             << "Seleccione un(los) estado(s) final(es) (";
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
                                                 tempPosibleStates.end(),
                                                 tempState));
                    cout << endl
                         << "[*] Estado final registrado: " << tempState
                         << endl;

                    if (!(tempPosibleStates.empty())) {
                        cout << endl
                             << "¿Desea agregar un nuevo estado final? "
                                "(si/no): ";
                        while ((cin >> addNewQuestion) &&
                               !((addNewQuestion == "si") ||
                                 (addNewQuestion == "no") ||
                                 (addNewQuestion == "Si") ||
                                 (addNewQuestion == "No"))) {
                            cin.clear();
                            cin.ignore();
                        }
                    }
                }

                cout << endl << "[*] Estados finales registrados: ";
                for (i = 0; i < automaton.finalStates.size(); i++) {
                    cout << automaton.finalStates[i] << " ";
                }

                automaton.finalStates = finalStates;
                break;

            case 5:
                automaton.printTransitionMap();

                // Transitions
                cout << endl
                     << "---> Ingrese las funciones de transición del autómata "
                        "<---";
                addNewQuestion = "si";
                while (addNewQuestion == "si" || addNewQuestion == "Si") {
                    i = 1;
                    cout << endl << "     Transición #" << i << endl;

                    cout << endl << "Seleccione un estado inicial (";
                    for (i = 0; i < automaton.posibleStates.size(); i++) {
                        if (i != 0) {
                            cout << ", ";
                        }
                        cout << automaton.posibleStates[i];
                    }
                    cout << "):" << endl;
                    while (
                        (cin >> initialState) &&
                        !(find(automaton.posibleStates.begin(),
                               automaton.posibleStates.end(), initialState) !=
                          automaton.posibleStates.end())) {
                        cin.clear();
                        cin.ignore();

                        cout << endl << "Seleccione un estado inicial (";
                        for (i = 0; i < automaton.posibleStates.size(); i++) {
                            if (i != 0) {
                                cout << ", ";
                            }
                            cout << automaton.posibleStates[i];
                        }
                        cout << "):" << endl;
                    }

                    cin.clear();
                    cin.ignore();

                    // [BUG: 29/sep/2025]: Elemento no se captura hasta obtener
                    // una segunda entrada

                    // [To Do] Editar para usar do while
                    cout << endl << "Seleccione un elemento del alfabeto (";
                    for (i = 0; i < automaton.alphabet.size(); i++) {
                        if (i != 0) {
                            cout << ", ";
                        }
                        cout << automaton.alphabet[i];
                    }
                    cout << "):" << endl;
                    while ((cin >> transitionInput) &&
                           !(find(automaton.alphabet.begin(),
                                  automaton.alphabet.end(), transitionInput) !=
                             automaton.alphabet.end())) {
                        cin.clear();
                        cin.ignore();

                        cout << endl << "Seleccione un elemento del alfabeto (";
                        for (i = 0; i < automaton.alphabet.size(); i++) {
                            if (i != 0) {
                                cout << ", ";
                            }
                            cout << automaton.alphabet[i];
                        }
                        cout << "):" << endl;
                    }

                    auto it = automaton.transitionMap.find(
                        {initialState, transitionInput});

                    if (it != automaton.transitionMap.end()) {
                        cout << endl
                             << "[!] Transición ya registrada. Por favor "
                                "ingrese una "
                                "diferente"
                             << endl;
                    } else {
                        while (
                            (cin >> finalState) &&
                            !(find(automaton.posibleStates.begin(),
                                   automaton.posibleStates.end(), finalState) !=
                              automaton.posibleStates.end())) {
                            cin.clear();
                            cin.ignore();

                            cout << endl << "Seleccione el estado siguiente (";
                            for (i = 0; i < automaton.posibleStates.size();
                                 i++) {
                                if (i != 0) {
                                    cout << ", ";
                                }
                                cout << automaton.posibleStates[i];
                            }
                            cout << "):" << endl;
                        }

                        vector<string> temp;
                        temp.push_back(finalState);

                        automaton.transitionMap.insert(
                            {{initialState, transitionInput}, temp});

                        cout << endl
                             << "[*] Transición registrada: " << "T("
                             << initialState << ", " << transitionInput
                             << ") = ";

                        for (auto transition : automaton.transitionMap.at(
                                 {initialState, transitionInput})) {
                            cout << transition << " ";
                        }
                        cout << endl;

                        i++;

                        cout
                            << endl
                            << "¿Desea agregar una nueva transición? (si/no): ";
                        while ((cin >> addNewQuestion) &&
                               !((addNewQuestion == "si") ||
                                 (addNewQuestion == "no") ||
                                 (addNewQuestion == "Si") ||
                                 (addNewQuestion == "No"))) {
                            cin.clear();
                            cin.ignore();
                        }
                    }
                }
                break;
            case 6:
                i = 0;
                for (auto transition : automaton.transitionMap) {
                    cout << "    [" << i << "] T(" << transition.first.first
                         << ", " << transition.first.second << ") = ";
                    indexTransitionMap.push_back(
                        make_pair(i, make_pair(transition.first.first,
                                               transition.first.second)));
                    i++;
                    for (auto element : transition.second) {
                        cout << element << " ";
                    }
                    cout << endl;
                }
                cin >> elementToDelete;
                cout << "¿Está seguro de que quiere eliminar el elemento ["
                     << elementToDelete << "] " << "T("
                     << indexTransitionMap[elementToDelete].second.first << ", "
                     << indexTransitionMap[elementToDelete].second.second
                     << ") = ";
                for (auto element : automaton.transitionMap.at(
                         indexTransitionMap[elementToDelete].second)) {
                    cout << element << " ";
                }
                cout << "? [si/no]" << endl;
                while ((cin >> youSure) &&
                       !((youSure == "si") || (youSure == "Si") ||
                         (youSure == "no") || (youSure == "No"))) {
                    cin.clear();
                    cin.ignore();
                }

                if (youSure == "si" || youSure == "Si") {
                    automaton.transitionMap.erase(
                        indexTransitionMap[elementToDelete].second);
                    cout << endl << "[*] Elemento borrado exitosmanete" << endl;
                }
                break;
            case 7:
                // Name
                cout << endl
                     << "Ingrese el nombre o identificador del autómata: "
                     << endl;
                cin >> automatonName;

                automaton.automatonName = automatonName;
                break;

            default:
                break;
        }

        cout << endl << "### Autómata actualizado ###" << endl;
        automaton.printAtributes();
    }
}

void exportAutomaton() {
    int i, automatonChoice;
    string filename;

    if (automata.empty()) {
        cout << endl
             << "[!] Memoria vacía. Favor de crear o cargar autómata" << endl;
    } else {
        cout << endl << "--- { Autómatas disponibles } ---" << endl;
        for (i = 0; i < automata.size(); i++) {
            cout << "[" << i + 1 << "] " << automata[i].automatonName << endl;
        }
        cout << "Seleccione un autómata: ";
        while (!(
            (cin >> automatonChoice) &&
            (automatonChoice >= 1 && automatonChoice < automata.size() + 1))) {
            cin.clear();
            cin.ignore();
        }
        automatonChoice--;

        Automaton automaton = automata[automatonChoice];

        json automatonJSON;
        automatonJSON[automaton.automatonName] = {
            {{"automatonName", automaton.automatonName},
             {"posibleStates", automaton.posibleStates},
             {"alphabet", automaton.alphabet},
             {"initialState", automaton.initialState},
             {"finalStates", automaton.finalStates},
             {"transitionMap", automaton.transitionMap}}};

        for (auto& item : automatonJSON.items()) {
            cout << item.key() << " : " << item.value();
        }

        cout << endl
             << "Ingrese el nombre o identificador del autómata: " << endl;
        cin >> filename;

        std::ofstream outputFile(filename + ".json");

        // 3. Check if the file was opened successfully
        if (outputFile.is_open()) {
            // 4. Write the JSON object to the file
            // The third argument (indentation level) makes the output
            // human-readable
            outputFile << automatonJSON.dump(4);
            outputFile.close();
            // std::cout << "JSON data successfully saved to output.json" <<
            // std::endl; // Optional: for user feedback

            cout << "### Autómata exportado exitosamente ###" << endl
                 << "[*] Acceda al archivo " << filename
                 << ".json generado en el directorio de este programa para "
                    "visualizarlo";
        } else {
            cout << endl << "[!] Error al escribir dentro del archivo" << endl;
            // std::cerr << "Error: Unable to open file for writing." <<
            // std::endl; // Optional: for error handling
        }
    }
}

void AFD_AFND_manager() {
    /* ------------------------- Variables ------------------------- */
    /* - Menu - */
    int userChoice;
    bool run = true;
    bool validString = false;

    /* - Auxiliaries - */
    int i, a, automatonChoice, methodChoice;
    Automaton automaton;

    /* --------------------------- Code ---------------------------- */
    while (run == true) {
        diplay_AFD_AFND_Menu();
        while (!((cin >> userChoice) && (userChoice >= 1 && userChoice <= 6))) {
            cin.clear();
            cin.ignore();
        }

        switch (userChoice) {
            case 1:
                getAutomaton();
                break;

            case 2:
                loadAutomaton();
                break;

            case 3:

                if (automata.empty()) {
                    cout
                        << endl
                        << "[!] Memoria vacía. Favor de crear o cargar autómata"
                        << endl;
                } else {
                    cout << endl << "--- { Autómatas disponibles } ---" << endl;
                    for (i = 0; i < automata.size(); i++) {
                        cout << "[" << i + 1 << "] "
                             << automata[i].automatonName << endl;
                    }
                    cout << "Seleccione un autómata: ";
                    while (!((cin >> automatonChoice) &&
                             (automatonChoice >= 1 &&
                              automatonChoice < automata.size() + 1))) {
                        cin.clear();
                        cin.ignore();
                    }
                    automatonChoice--;

                    cout << endl
                         << "Seleccione un método: " << endl
                         << "[1] Verificar cadena" << endl
                         << "[2] Mostrar cadenas posibles" << endl;
                    while (!((cin >> methodChoice) &&
                             (methodChoice >= 1 && methodChoice <= 2))) {
                        cin.clear();
                        cin.ignore();
                    }

                    if (methodChoice == 1) {
                        executeAutomaton(automatonChoice);
                    } else if (methodChoice == 2) {
                        displayChains(automatonChoice);
                    }
                }

                break;
            case 4:
                editAutomaton();
                break;

            case 5:
                exportAutomaton();
                break;

            case 6:
                endTitle();
                run = false;
                break;
        }
    }
}

class PushdownAutomaton {
   public:
    string automatonName;

    vector<string> posibleStates;  // Q
    vector<string> alphabet;       // Σ
    vector<string> stackAlphabet;  // Γ
    map<tuple<string, string, string>, pair<string, vector<string>>>
        transitionMap;  // δ

    string startState;           // q0
    string stackStartSymbol;     // Z0
    vector<string> finalStates;  // F

    stack<string> theStack;  // Stack

    PushdownAutomaton(
        string _automatonName, vector<string> _posibleStates,
        vector<string> _alphabet, vector<string> _stackAlphabet,
        map<tuple<string, string, string>, pair<string, vector<string>>>
            _transitionMap,
        string _startState, string _stackStartSymbol,
        vector<string> _finalStates) {
        automatonName = _automatonName;
        posibleStates = _posibleStates;
        alphabet = _alphabet;
        stackAlphabet = _stackAlphabet;
        transitionMap = _transitionMap;
        startState = _startState;
        stackStartSymbol = _stackStartSymbol;
        finalStates = _finalStates;
    }

    void printPosibleStates() {
        int i;
        cout << endl << "Conjunto de Estados Posibles  Q: {";
        for (i = 0; i < posibleStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << posibleStates[i];
        }
        cout << "}";
    }

    void printAlphabet() {
        int i;
        cout << endl << "Alfabeto                      Σ: {";
        for (i = 0; i < alphabet.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << alphabet[i];
        }
        cout << "}";
    }

    void printInitialState() {
        cout << endl << "Estado Inicial                s: " << initialState;
    }

    void printFinalStates() {
        int i;
        cout << endl << "Conjunto de Estados finales   F: {";
        for (i = 0; i < finalStates.size(); i++) {
            if (i != 0) {
                cout << ", ";
            }
            cout << finalStates[i];
        }
        cout << "}";
    }

    void printTransitionMap() {
        bool AFND = false;
        cout << endl << "Funciones de transición       𝜹:" << endl;

        for (auto transition : transitionMap) {
            cout << "    T(" << transition.first.first << ", "
                 << transition.first.second << ") = ";
            for (auto element : transition.second) {
                cout << element << " ";
            }
            if (transition.second.size() > 1) {
                AFND = true;
            }
            cout << endl;
        }

        cout << "               Tipo de autómata: ";
        if (AFND) {
            cout << "Autómata Finito\n                                 No "
                    "Determinístico (AFND)"
                 << endl;
        } else {
            cout << "Autómata Finito\n                                 "
                    "Determinístico (AFD)"
                 << endl;
        }
    }

    void printAtributes() {
        cout << endl
             << "-------------------<{ " << automatonName
             << " }>-------------------";
        cout << endl << "A = (Q, Σ, Γ, q0, Z0, |    δ, s, F)";

        printPosibleStates();

        printAlphabet();

        printInitialState();

        printFinalStates();

        printTransitionMap();

        cout << "---------------------------------------------------------"
             << endl;
    }

    void runAutomaton() {
        /* - Auxiliaries - */
        int i;

        string currentCharacter;
        string automatonInput;
        vector<string> nextState;
        string currentByte;

        bool validChain = true;

        /* - Validators - */
        bool validString = false;

        while (validString == false) {
            cout << "Ingrese una cadena: ";
            cin >> automatonInput;

            for (int i = 0; i < automatonInput.length(); i++) {
                currentCharacter = automatonInput[i];
                auto it =
                    find(alphabet.begin(), alphabet.end(), currentCharacter);

                if (it != alphabet.end()) {
                    validString = true;
                } else {
                    cout << endl << "    [!] Cadena no válida\n" << endl;
                    validString = false;
                    break;
                }
            }
            validString = true;
        }

        cout << endl << "[*] Cadena válida" << endl;
        nextState.push_back(startState);

        cout << endl << "[*] Estado inicial: " << nextState[0] << endl;

        for (i = 0; i < automatonInput.length(); i++) {
            currentByte = automatonInput[i];
            nextState = getNextPDAState(true, nextState, currentByte,
                                        transitionMap, theStack);
        }

        for (auto state : nextState) {
            auto it = find(finalStates.begin(), finalStates.end(), state);

            if (it != finalStates.end()) {
                cout << endl << "[*] Estado final: " << state;
                cout << endl;
            } else {
                cout << endl << "[!] Estado final no válido: " << state << endl;
                cout << endl << "[!] Cadena no válida";
                validChain = false;
                break;
            }
        }

        cout << endl << "\n\n###### Resultado final ######";
        cout << endl << "Cadena: " << automatonInput;
        if (validChain == false) {
            cout << " NO es válida [X]";
        } else {
            cout << " es válida [✓]";
        }
    }

    static vector<string> getNextPDAState(
        bool verbose, vector<string> initialState, string transitionInput,
        map<tuple<string, string, string>, pair<string, vector<string>>>
            transitionMap,
        stack<string> theStack) {
        vector<string> nextState;

        for (auto currentState : initialState) {
            for (auto element : transitionMap) {
                if ((currentState == get<0>(element.first)) &&
                    (transitionInput == get<1>(element.first)) &&
                    (theStack.top() == get<2>(element.first))) {
                    cout << "found!" << endl;

                    nextState.push_back(element.second.first);
                    cout << "siguiente estado: " << nextState.front() << endl;

                    if (element.second.second[0] == "_") {
                        theStack.pop();
                    } else {
                        for (auto i : element.second.second) {
                            theStack.push(i);
                        }
                    }
                } else {
                    if (verbose == true) {
                        cout << endl << "[!] Transición no válida" << endl;
                    }
                }
            }
        }

        return nextState;
    }
};

void PDA1() {
    string automatonName =
        "Prueba #1: Geeks for geeks - Introduction of Pushdown Automata";

    vector<string> posibleStates = {"q0", "q1"};  // Q
    vector<string> alphabet = {"a", "b"};         // Σ
    vector<string> stackAlphabet = {"A", "Z"};    // Γ
    map<tuple<string, string, string>, pair<string, vector<string>>>
        transitionMap = {
            {make_tuple("q0", "", "_"), make_pair("q1", vector<string>{"Z"})},
            {make_tuple("q1", "0", "0"), make_pair("q1", vector<string>{"0"})},
            {make_tuple("q1", "0", "Z"), make_pair("q1", vector<string>{"0"})},
            {make_tuple("q1", "1", "0"), make_pair("q2", vector<string>{"_"})},
            {make_tuple("q2", "", "0"), make_pair("q3", vector<string>{"_"})},
            {make_tuple("q3", "1", "0"), make_pair("q2", vector<string>{"_"})},
            {make_tuple("q3", "", "Z"),
             make_pair("q4", vector<string>{"_"})}};  // δ

    string startState = "q0";             // q0
    string stackStartSymbol = "λ";        // Z0
    vector<string> finalStates = {"q4"};  // F

    PushdownAutomaton automaton1(automatonName, posibleStates, alphabet,
                                 stackAlphabet, transitionMap, startState,
                                 stackStartSymbol, finalStates);

    automaton1.printAtributes();
    automaton1.runAutomaton();
}

void PDA2() {}

void TuringMachine() {}

void PDA_manager() {
    /* ------------------------- Variables ------------------------- */
    /* - Menu - */
    int userChoice;
    bool run = true;
    bool validString = false;

    /* - Auxiliaries - */
    int i, a, automatonChoice, methodChoice;
    Automaton automaton;

    /* --------------------------- Code ---------------------------- */
    while (run == true) {
        diplay_PDA_TuringMachine_Menu();
        while (!((cin >> userChoice) && (userChoice >= 1 && userChoice <= 4))) {
            cin.clear();
            cin.ignore();
        }

        switch (userChoice) {
            case 1:
                PDA1();
                break;

            case 2:
                PDA2();
                break;

            case 3:
                TuringMachine();
                break;

            case 4:
                endTitle();
                run = false;
                break;
        }
    }
}

int main() {
    /* ------------------------- Variables ------------------------- */
    /* - Menu - */
    int userChoice;
    bool run = true;
    bool validString = false;

    /* - Auxiliaries - */
    int i, a, automatonChoice, methodChoice;
    Automaton automaton;

    /* --------------------------- Code ---------------------------- */
    while (run == true) {
        diplayMainMenu();
        while (!((cin >> userChoice) && (userChoice >= 1 && userChoice <= 3))) {
            cin.clear();
            cin.ignore();
        }

        switch (userChoice) {
            case 1:
                PDA_manager();
                break;

            case 2:
                AFD_AFND_manager();
                break;

            case 3:
                endTitle();
                run = false;
                break;
        }
    }

    return 0;
}

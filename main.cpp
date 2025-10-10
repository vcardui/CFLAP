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
 * | Last update..: October 9th, 2025
 * | WhatIs.......: CFLAP - Main
 * +----------------------------------------------------------------------------+
 */

/*
6 de octubre de 2025
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

void diplayMenu() {
    cout << endl
         << "\n.-----------------------."
            "\n||     -{ MENU }-      ||"
            "\n.-----------------------."
            "\n| [1] Crear autómata    |"
            "\n| [2] Cargar autómata   |"
            "\n| [3] Ejecutar autómata |"
            "\n| [4] Exportar autómata |"
            "\n|             [5] Salir |"
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

        cout << endl << "Funciones de transición       𝜹:" << endl;

        for (auto transition : transitionMap) {
            cout << "    T(" << transition.first.first << ", "
                 << transition.first.second << ") = ";
            for (auto element : transition.second) {
                cout << element << " ";
            }
            cout << endl;
        }

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

void exportAutomaton() {
    int i, automatonChoice;

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

        std::ofstream outputFile("output.json");

        // 3. Check if the file was opened successfully
        if (outputFile.is_open()) {
            // 4. Write the JSON object to the file
            // The third argument (indentation level) makes the output
            // human-readable
            outputFile << automatonJSON.dump(4);
            outputFile.close();
            // std::cout << "JSON data successfully saved to output.json" <<
            // std::endl; // Optional: for user feedback
        } else {
            // std::cerr << "Error: Unable to open file for writing." <<
            // std::endl; // Optional: for error handling
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
        diplayMenu();
        while (!((cin >> userChoice) && (userChoice >= 1 && userChoice <= 5))) {
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
                exportAutomaton();
                break;

            case 5:
                endTitle();
                run = false;
                break;
        }
    }

    return 0;
}

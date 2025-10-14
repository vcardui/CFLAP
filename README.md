# CFLAP - Documentación

Autores: Vanessa Reteguín

Primera publicación: 26 de septiembre de 2025

Última actualización: 14 de octubre de 2025

Actividad 8: Práctica para AFND

Universidad Aútonoma de Aguascalientes
Ingeniería en Computación Inteligente (ICI)
Semestre V

Grupo 5 - A
Autómatas I
Ángel Eduardo Villegas Ortíz

# Dependencias

El programa en cuestión depende de la librería [json](https://github.com/nlohmann/json) de Niels Lohmann ([nlohmann](https://github.com/nlohmann)). La integración es sencilla, sólo se requiere invocar el un archivo [`json.hpp`](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp). Para fines prácticos, se ha agregado el mismo dentro del paquete del programa. Sin embargo, es recomendable instalar la librería mediante un manejador de paquetes.

[Lista de manejador de paquetes y sus fórmulas](https://json.nlohmann.me/integration/package_managers/)

**Mac OS**

[Via Homebrew](https://json.nlohmann.me/integration/package_managers/#homebrew): `brew install nlohmann-json`

**Windows** 

[Via vcpkg](https://json.nlohmann.me/integration/package_managers/#vcpkg): `vcpkg install nlohmann-json`

**Linux**

[Se recomienda](https://www.black-sat.org/en/stable/installation/linux.html) instalar desde el respositorio original

```bash
git clone https://github.com/nlohmann/json.git
cd json
mkdir build && cd build
cmake -DJSON_BuildTests=OFF ..
sudo make install
```

# Ejecución

## Compilación directo en terminal

Con librería directo en directorio de proyecto

```bash
cd Directory/to/file; g++ -I nlohmann-json/3.12.0/include main.cpp -o main.out; ./main.out; 
```

Si se instala la librería desde manejador de paquetes (ejemplo con **Homebrew**)

```bash
cd Directory/to/file; g++ -I /opt/homebrew/Cellar/nlohmann-json/3.12.0/include main.cpp -o main.out; ./main.out;
```

Nótese que la ruta `/opt/homebrew/Cellar/nlohmann-json/3.12.0/include` varía en cada manejador de paquetes. Usted debe averiguar qué ruta sigue su manejador.

Una correcta ejecución del programa debe llevar al menú principal:

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
```

# Reconocimiento de librería desde IDE

## Visual Studio Code

Para que el IDE reconozca la dependencia, es necesario ingresar la ruta hacia ella en el apartado corresondiente:

1. Abrir configuración y buscar “`C_Cpp.default.includePath`” (Extensions → C/C++ → IntelliSense → C**_Cpp › Default: Include Path**)
2. Ingresar ruta hacia librería en la caja de texto y guardar dando click en “Add Item”
3. Opcionalmente, puede agregar la ruta directo en el archvio “`settings.json`”, cuya ubicación aproximada es: '/Users/YourUser/Library/Application Support/Code/User/settings.json’
4. Reiniciar aplicación para que los cambios se reflejen

# Manual de usuario

## Librerías

`#include <fstream>`: Uso de `ifstream` para realizar operaciones con archivos 
`#include <iostream>`: Operaciones de flujo de entrada y salida (`cin`/`cout`)
`#include <list>`: Operaciones con listas (conversión entre n bases)
`#include <map>`: Operaciones con mapas (almacenamiento de transiciones)
`#include <nlohmann/json.hpp>`: Manipulación de archivos JSON 
`#include <sstream>`: Uso de `stringstream` para tokenizar la entrada según un delimitador personalizado 
`#include <string>`: Manipulación de datos tipo cadena

## Clases y funciones

### Automaton

Manejador de atributos de un autómata

```cpp
Automaton(string _automatonName, vector<string> _posibleStates,
              vector<string> _alphabet, string _initialState,
              vector<string> _finalStates,
              map<pair<string, string>, vector<string>> _transitionMap)
```

### `printAtributes()`

`void`

Imprimir los estados posibles del autómata

**Ejemplo**

```

-------------------<{ Evluación #2 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q1, q2, q3, q4}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q2, q4}
Funciones de transición       𝜹:
    T(q0, 0) = q1 q3 
    T(q0, 1) = q0 q1 
    T(q1, 1) = q2 
    T(q2, 0) = q2 
    T(q2, 1) = q2 
    T(q3, 0) = q4 
    T(q4, 0) = q4 
    T(q4, 1) = q4 
               Tipo de autómata: Autómata Finito
                                 No Determinístico (AFND)
---------------------------------------------------------
```

**Ejemplo**

```
-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------

```

### `printPosibleStates()`

`void`

Imprimir el conjunto de estados posibles del autómata

**Ejemplo**

```
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
```

### `printAlphabet()`

`void`

Imprimir alfabeto del autómata

**Ejemplo**

```
Alfabeto                      Σ: {a, b}
```

### `printInitialState()`

`void`

Imprimir estado inicial del autómata

**Ejemplo**

```
Estado Inicial                s: A
```

### `printFinalStates()`

`void`

Imprimir el conjunto de esatos del autómata

**Ejemplo**

```
Conjunto de Estados finales   F: {E}
```

### `printTransitionMap()`

`void`

Imprimir transiciones del autómata y su tipo (determinístico o no determinístico)

**Ejemplo**

```
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
```

### `runAutomaton()`

`void`

Ejecutar acciones de un autómata seleccionado de entre los disponibles

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
3

--- { Autómatas disponibles } ---
[1] Actividad 6: Ejercicio 1
[2] Evaluación #1
[3] Evaluación #2
[4] Examen primer parcial: Autómata 1
Seleccione un autómata: 1

Seleccione un método: 
[1] Verificar cadena
[2] Mostrar cadenas posibles
1
```

### `printChains()`

`void`

Impresión de cadenas posibles de acuerdo al mapa de transiciones del autómata

Se imprimen los atributos del autómata

```matlab
printAtributes();
```

Todos los elementos se insertan como permutaciones posibles. Es decir, una cadena a verificar posteriormente

```matlab
for (i = 0; i < alphabet.size(); i++) {
            permutations.push_back(alphabet[i]);
        }
```

De acuerdo con los elementos actuales del alfabeto, se generan las permutaciones posibles desde 0 hasta el resultado de $cantidadElementos^{potencia} - 1$. Se guarda la permutación obtenida en un vector

```matlab
for (i = 0; i <= (pow(alphabet.size(), alphabet.size()) - 1); i++) {
            currentPermutation = "";
            currentPermutation = decimalToNBase(i, alphabet.size(), alphabet);

            permutations.push_back(currentPermutation);
        }
```

 Se obtienen más permutaciones empleando el arreglo obtenido anteriomente como nuevo alfabeto. Por cada cadena obtenida, sí es válida de acuerdo al mapa de transiciones, se muestra en consola.

```matlab
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
```

Se almacena el número total de permutaciones obtenidas vs la cantidad de cadenas válidas

```matlab
cout << endl
             << "[*] Mostrando " << validStrings << " cadenas válidas de "
             << totalPermutations << " permutaciones totales generadas" << endl;
```

**Ejemplo**

```
-------------------<{ Actividad 6: Ejercicio 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q0, q1, q2, q3}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q0}
Funciones de transición       𝜹:
    T(q0, 0) = q2 
    T(q0, 1) = q1 
    T(q1, 0) = q3 
    T(q1, 1) = q0 
    T(q2, 0) = q0 
    T(q2, 1) = q3 
    T(q3, 0) = q1 
    T(q3, 1) = q2 
---------------------------------------------------------
[1] 00
[2] 10
[3] 00
[4] 10
...
[46653] 111111111100
[46654] 111111111110
[46655] 111111111110
[46656] 111111111111

[*] Mostrando 46656 cadenas válidas de 46656 permutaciones totales generadas
```

### `validChain(string fullstring)`

`bool`: Retorna `true` si la cadena es válida o `false` si el estado final obtenido no es válido

Verificar si una cadena es válida de acuerdo con el mapa de transiciones del autómata

Se inicializa un vector de cadenas que contenga el estado inicial

```cpp
nextState.push_back(initialState);
```

Por cada carácter de la cadena ingresada, se verifica si es posible llegar a una siguiente transición válida 

```cpp
for (i = 0; i < fullstring.length(); i++) {
            currentByte = fullstring[i];
            nextState =
                getNextState(false, nextState, currentByte, transitionMap);
        }
```

o llegar a un estado final

```cpp
for (auto state : nextState) {
            auto it = find(finalStates.begin(), finalStates.end(), state);

            if (it != finalStates.end()) {
            } else {
                validChain = false;
            }
        }
```

### `static vector<string> getNextState(
bool verbose, vector<string> initialState, string transitionInput,
map<pair<string, string>, vector<string>> transitionMap)`

`vector<string>`: Conjunto de estados siguientes encontrados

Evalua si un conjunto de transiciones son válidas dentro de un Autómata Finito Determinístico (AFD) y un Autómata Finito No Determinístico (AFND)

Por cada estado inicial dentro del conjunto ingresado

```cpp
for (auto element : initialState)
```

Se busca la transición correspondiente al elemento actual con la entrada dada

```cpp
auto it = transitionMap.find({element, transitionInput});
```

En el caso de que la transición sea válida, es decir encontrada dentro del mapa de transiciones, se imprime la transición encontrada. 

Además, se almacena el estado de la siguiente transición dentro del vector `nextState`

```cpp
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
            } 
```

En el caso contrario, siento el estado verboso activado, se alerta al usuario dentro de la consola

```cpp
else {
                if (verbose == true) {
                    cout << endl << "[!] Transición no válida" << endl;
                }
            }
```

### `static string decimalToNBase(int decimalNum, int base,
vector<string> digits)`

`string` : Retorna cadena correspondiente a número ingresado con base en alfabeto dado

Generador de permutación específica sin emplear recursión

Dado un alfabeto, por ejemplo:

```cpp
vector<string> digits = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
         "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
```

El número 42 transformado en base 26 (cadinalidad del conjunto de elementos del alfabeto)

```cpp
int decimalNum = 42;
int base = digits.size();
```

Seguiría el siguiente proceso:

Se divide el número dado sobre la base y se almacena el caracter correspondiente a la posición del residuo en el arreglo del alfabeto hasta que el número ingresado sea igual a 0

```cpp
while (decimalNum > 0) {
            int remainder = decimalNum % base;
            // result += digits[remainder];
            reverseResultList.push_front(digits[remainder]);
            decimalNum /= base;
        }
```

La lista de caracteres obtenidos se invierte y concatena en una cadena final a retornar

```cpp
 if ((iter = reverseResultList.begin()) != reverseResultList.end()) {
            for (i = 0; i < reverseResultList.size(); ++i) {
                result += *iter;
                ++iter;
            }
        }
```

## Funciones

### `getAutomaton()`

`void`: creación de autómata por medio de datos ingresados por el usuario

**Estados**

Se almacena entrada de Conjunto de Estados Posibles solicitando emplear el delimitador ‘,’

```cpp
cout << endl
         << "Ingrese el Conjunto de Estados Posibles separados por ',' "
            "(q1,q2,q3):"
         << endl;
    getline(cin >> ws, posibleStatesInput);
```

Se confirma almacenamiento de datos ingresados y transforma la entrada del usuario en un flujo de datos (stream) de tipo stringstream

```cpp
cout << endl << "[*] Estados registrados: ";
    stringstream ssPosibleStates(posibleStatesInput);
```

Se tokeniza el flujo de datos con base en delimitador seleccionado ‘,’. Al mismo tiempo, espacios en blanco y saltos de línea son eliminados del elemento actual. El elemento se almacena en el vector de estados posibles `posibleStates` . Se imprime elemento actual para confirmar datos almacenados con usuario.

```cpp
while (getline(ssPosibleStates, token, delimiter[0])) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace),
                    token.end());
        posibleStates.push_back(token);
        cout << token << " ";
    }
```

**Alfabeto**

Se almacena entrada de alfabeto solicitando emplear el delimitador ‘,’

```cpp
cout << endl
         << "Ingrese elementos del alfabeto separados por ',' "
            "(a,1,b):"
         << endl;
    getline(cin >> ws, alphabetInput);
```

Se confirma almacenamiento de datos ingresados y transforma la entrada del usuario en un flujo de datos (stream) de tipo stringstream

```cpp
cout << endl << "[*] Alfabeto registrado: ";
    stringstream ssAlphabet(alphabetInput);
```

Se tokeniza el flujo de datos con base en delimitador seleccionado ‘,’. Al mismo tiempo, espacios en blanco y saltos de línea son eliminados del elemento actual. El elemento se almacena en el vector de alfabeto `alphabet`. Se imprime elemento actual para confirmar datos almacenados con usuario.

```cpp
while (getline(ssAlphabet, token, delimiter[0])) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace),
                    token.end());
        alphabet.push_back(token);
        cout << token << " ";
    }
    cout << endl;
```

**Estado inicial**

Se despliegan estados posibles almacenados

```cpp
cout << endl << "Seleccione un estado inicial (";
    for (i = 0; i < posibleStates.size(); i++) {
        if (i != 0) {
            cout << ", ";
        }
        cout << posibleStates[i];
    }
    cout << "):" << endl;
```

Solicita ingresar un estado inicial al usuario y se valida que el dato ingresado se un estado válido

```cpp
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
```

Se confirma entrada seleccionada

```cpp
cout << endl << "[*] Estado inicial registrado: " << initialState << endl;
```

**Estados finales**

Validando que el usuario pueda ingresar más de un estado final, no repetido y previamente establecido, se despliega una lista de todos los estados posibles

```cpp
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
```

Se solicita al usuario seleccionar uno

```cpp
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
```

Se guarda estado final, se elimina de las opciones a elegir del usuario y se despliega lo almacenado para confirmar dato

```cpp
finalStates.push_back(tempState);
tempPosibleStates.erase(find(tempPosibleStates.begin(),
                        tempPosibleStates.end(), tempState));
cout << endl << "[*] Estado final registrado: " << tempState << endl;
```

Se le pregunta al usuario si desea agregar otro estado final

```cpp
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
```

Se confirman estados finales registrados

```cpp
cout << endl << "[*] Estados finales registrados: ";
    for (i = 0; i < finalStates.size(); i++) {
        cout << finalStates[i] << " ";
    }
```

**Transiciones**

Se le solicitará al usuario ingresar las transiciones del autómata hasta que ingrese un “no” al final del proceso

```cpp
cout << endl
         << "---> Ingrese las funciones de transición del autómata <---";
    addNewQuestion = "si";
    while (addNewQuestion == "si" || addNewQuestion == "Si") {
```

Para mayor control, se despliega el número de transiciones almacenadas hasta el momento. Se le solicita al usuario ingresar el estado inicial de la transición

```cpp
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
```

Solicita ingresar un estado inicial al usuario y se valida que el dato ingresado se un estado válido

```cpp
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
```

Se le solicita al usuario ingresar un elemento de entre los almacenados en el alfabeto preestablecido. Se valida que sea un elemento válido

```cpp
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
```

Se verifica que no exista un par previamente almacenado que coincida con la entrada y la transición dadas

```cpp
auto it = transitionMap.find({initialState, transitionInput});
```

Si el par es encontrado, se alerta al usuario

```cpp
if (it != transitionMap.end()) {
            cout << endl
                 << "[!] Transición ya registrada. Por favor ingrese una "
                    "diferente"
                 << endl;
        }
```

En caso de que sea una transición nueva, se le solicita al usuario que ingrese el conjunto de transiciones resultantes. Se almacenan estados resultantes en vector

```cpp
else {
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
```

La transición con su caractér y estados resultantes son almacenados dentro del mapa de transiciones como un par en la llave un vector de tipo cadena en el valor

```cpp
transitionMap.insert({{initialState, transitionInput}, temp});
```

Se despliega confirmación de transición almacenada para usuario

```cpp
 cout << endl
                 << "[*] Transición registrada: " << "T(" << initialState
                 << ", " << transitionInput << ") = ";

            for (auto transition :
                 transitionMap.at({initialState, transitionInput})) {
                cout << transition << " ";
            }
            cout << endl;
```

Se aumenta contador de transiciones y pregunta al usuario si desea agregar una nueva transición

```cpp
i++;

            cout << endl << "¿Desea agregar una nueva transición? (si/no): ";
            while ((cin >> addNewQuestion) &&
                   !((addNewQuestion == "si") || (addNewQuestion == "no") ||
                     (addNewQuestion == "Si") || (addNewQuestion == "No"))) {
                cin.clear();
                cin.ignore();
            }
```

**Nombre**

Se solicita al usuario que ingrese un identificador (nombre) para almacenar el autómata

```cpp
cout << endl << "Ingrese el nombre o identificador del autómata: " << endl;
    cin >> automatonName;
```

Se instancia un nuevo objeto de la clase `Automaton` con los atributos almacenados. Se llama al método `printAtributes()` para confirmar datos almacenados. El nuevo objeto es agregado al vector de autómatas `vector<Automaton> automata`

```
Automaton newAutomaton(automatonName, posibleStates, alphabet, initialState,
                           finalStates, transitionMap);

    newAutomaton.printAtributes();
    automata.push_back(newAutomaton);
```

**Ejemplo**

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
1

Ingrese el Conjunto de Estados Posibles separados por ',' (q1,q2,q3):
A,B,C 

[*] Estados registrados: A B C 

Ingrese elementos del alfabeto separados por ',' (a,1,b):
k,i,l,o,p

[*] Alfabeto registrado: k i l o p 

Seleccione un estado inicial (A, B, C):
C

[*] Estado inicial registrado: C

Seleccione un(los) estado(s) final(es) (A, B, C):
B

[*] Estado final registrado: B

¿Desea agregar un nuevo estado final? (si/no): si

Seleccione un(los) estado(s) final(es) (A, C):
A 

[*] Estado final registrado: A

¿Desea agregar un nuevo estado final? (si/no): no

[*] Estados finales registrados: B A 
---> Ingrese las funciones de transición del autómata <---
     Transición #1

Seleccione un estado inicial (A, B, C):
A

Seleccione un elemento del alfabeto (k, i, l, o, p):
B

Seleccione un elemento del alfabeto (k, i, l, o, p):
k
k

Seleccione el estado siguiente (A, B, C):
A

[*] Transición registrada: T(A, k) = A 

¿Desea agregar una nueva transición? (si/no): si

     Transición #1

Seleccione un estado inicial (A, B, C):
B

Seleccione un elemento del alfabeto (k, i, l, o, p):
l
l

Seleccione el estado siguiente (A, B, C):
B

[*] Transición registrada: T(B, l) = B 

¿Desea agregar una nueva transición? (si/no): no

Ingrese el nombre o identificador del autómata: 
Prueba1

-------------------<{ Prueba1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C}
Alfabeto                      Σ: {k, i, l, o, p}
Estado Inicial                s: B
Conjunto de Estados finales   F: {B, A}
Funciones de transición       𝜹:
    T(A, k) = A 
    T(B, l) = B 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

### `loadAutomaton()`

`void`

Cargar achivo JSON con atributos de autómata

Se solicita ingresar ruta hacia archivo

```cpp
cout << endl << "Ingrese ruta del archivo a cargar: ";
    cin >> fileRoute;  // test.json
```

Se intenta abrir un flujo de datos hacia la ruta ingresada. En caso de no ser posible, se alerta al usuario.

```cpp
try {
        std::ifstream file(fileRoute);
        if (!file.is_open()) {
            throw std::ios_base::failure("[!] No se pudo abrir el archivo");
        }
```

Empleando la librería JSON, se parsean los datos y almacenan dentro de un objeto te tipo `json` . Si se verifica que no exista actualmente otro autómata con las mismas características, se agrega el nuevo a la lista de autómatas

```cpp
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

    }
```

En caso de que no se pudiera abrir el archivo dado que estuviera en el directorio incorrecto o que no existiera el archivo, se alerta al usuario

```cpp
} catch (const std::ios_base::failure& e) {
        std::cerr << "I/O Error: " << e.what() << std::endl;
        // Log error, exit gracefully
    } catch (const std::exception& e) {
        std::cerr << "General Error: " << e.what() << std::endl;
    }
```

**Ejemplo**

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
3

[!] Memoria vacía. Favor de crear o cargar autómata

.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
2

Ingrese ruta del archivo a cargar: test.json

[*] Nuevo autómata creado

-------------------<{ Actividad 6: Ejercicio 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q0, q1, q2, q3}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q0}
Funciones de transición       𝜹:
    T(q0, 0) = q2 
    T(q0, 1) = q1 
    T(q1, 0) = q3 
    T(q1, 1) = q0 
    T(q2, 0) = q0 
    T(q2, 1) = q3 
    T(q3, 0) = q1 
    T(q3, 1) = q2 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------

[*] Nuevo autómata creado

-------------------<{ Evaluación #1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q1, q2, q3, q4, q5, q6}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q4, q6}
Funciones de transición       𝜹:
    T(q0, 0) = q1 
    T(q0, 1) = q2 
    T(q1, 0) = q4 
    T(q1, 1) = q3 
    T(q2, 0) = q3 
    T(q2, 1) = q5 
    T(q3, 0) = q6 
    T(q4, 0) = q4 
    T(q4, 1) = q6 
    T(q5, 0) = q5 
    T(q5, 1) = q5 
    T(q6, 0) = q6 
    T(q6, 1) = q5 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------

[*] Nuevo autómata creado

-------------------<{ Evaluación #2 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q1, q2, q3, q4}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q2, q4}
Funciones de transición       𝜹:
    T(q0, 0) = q1 q3 
    T(q0, 1) = q0 q1 
    T(q1, 1) = q2 
    T(q2, 0) = q2 
    T(q2, 1) = q2 
    T(q3, 0) = q4 
    T(q4, 0) = q4 
    T(q4, 1) = q4 
               Tipo de autómata: Autómata Finito
                                 No Determinístico (AFND)
---------------------------------------------------------

[*] Nuevo autómata creado

-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------

```

### `executeAutomaton(int automatonChoice)`

`void` 

Instanciar nuevo objeto de autómata con base en su índice dentro del vector de almacenamiento de autómatas, imprimir sus atributos y llamar al método de ejecución del mismo

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
3

--- { Autómatas disponibles } ---
[1] Actividad 6: Ejercicio 1
[2] Evaluación #1
[3] Evaluación #2
[4] Examen primer parcial: Autómata 1
Seleccione un autómata: 1

Seleccione un método: 
[1] Verificar cadena
[2] Mostrar cadenas posibles
1

-------------------<{ Actividad 6: Ejercicio 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q0, q1, q2, q3}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q0}
Funciones de transición       𝜹:
    T(q0, 0) = q2 
    T(q0, 1) = q1 
    T(q1, 0) = q3 
    T(q1, 1) = q0 
    T(q2, 0) = q0 
    T(q2, 1) = q3 
    T(q3, 0) = q1 
    T(q3, 1) = q2 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
Ingrese una cadena: 010101

[*] Cadena válida

[*] Estado inicial: q0

Estado Resultado: q2 
T(q0, 0) = q2 

Estado Resultado: q3 
T(q2, 1) = q3 

Estado Resultado: q1 
T(q3, 0) = q1 

Estado Resultado: q0 
T(q1, 1) = q0 

Estado Resultado: q2 
T(q0, 0) = q2 

Estado Resultado: q3 
T(q2, 1) = q3 

[!] Estado final no válido: q3

[!] Cadena no válida

###### Resultado final ######
Cadena: 010101 NO es válida [X]
```

### `displayChains(int automatonChoice)`

`void`

Instanciar nuevo objeto de autómata con base en su índice dentro del vector de almacenamiento de autómatas y llamar al método de impresión de cadenas `printChains()`

```
[1] 00
[2] 10
[3] 00
[4] 10
...
[46653] 111111111100
[46654] 111111111110
[46655] 111111111110
[46656] 111111111111

[*] Mostrando 46656 cadenas válidas de 46656 permutaciones totales generadas
```

### `editAutomaton()`

`void`

Editar acciones del autómata

**Editar Conjunto de Estados Posibles**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
1

Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Ingrese el Conjunto de Estados Posibles separados por ',' (q1,q2,q3):
X,Y,Z

[*] Estados registrados: X Y Z 

### Autómata actualizado ###

-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {X, Y, Z}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

**Editar Alfabeto**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
2

Alfabeto                      Σ: {a, b}
Ingrese elementos del alfabeto separados por ',' (a,1,b):
i,j,k

[*] Alfabeto registrado: i j k 

### Autómata actualizado ###

-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {i, j, k}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

**Editar Estado inicial**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
3

Estado Inicial                s: q0
Seleccione un estado inicial (q0, q1, q2, q3):
q1

[*] Estado inicial registrado: q1

### Autómata actualizado ###

-------------------<{ Actividad 6: Ejercicio 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q0, q1, q2, q3}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q1
Conjunto de Estados finales   F: {q0}
Funciones de transición       𝜹:
    T(q0, 0) = q2 
    T(q0, 1) = q1 
    T(q1, 0) = q3 
    T(q1, 1) = q0 
    T(q2, 0) = q0 
    T(q2, 1) = q3 
    T(q3, 0) = q1 
    T(q3, 1) = q2 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

**Editar Conjunto de Estados finales**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
4

Conjunto de Estados finales   F: {E}
Seleccione un(los) estado(s) final(es) (A, B, C, D, E):
A

[*] Estado final registrado: A

¿Desea agregar un nuevo estado final? (si/no): si

Seleccione un(los) estado(s) final(es) (B, C, D, E):
B

[*] Estado final registrado: B

¿Desea agregar un nuevo estado final? (si/no): no

[*] Estados finales registrados: E 
### Autómata actualizado ###

-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {A, B}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

**Editar Funciones de transición**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
5

Funciones de transición       𝜹:
    T(q0, 0) = q1 q3 
    T(q0, 1) = q0 q1 
    T(q1, 1) = q2 
    T(q2, 0) = q2 
    T(q2, 1) = q2 
    T(q3, 0) = q4 
    T(q4, 0) = q4 
    T(q4, 1) = q4 
               Tipo de autómata: Autómata Finito
                                 No Determinístico (AFND)

---> Ingrese las funciones de transición del autómata <---
     Transición #1

Seleccione un estado inicial (q1, q2, q3, q4):
q3

Seleccione un elemento del alfabeto (0, 1):
1
1

Seleccione el estado siguiente (q1, q2, q3, q4):
q1

[*] Transición registrada: T(q3, 1) = q1 

¿Desea agregar una nueva transición? (si/no): no

### Autómata actualizado ###

-------------------<{ Evaluación #2 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {q1, q2, q3, q4}
Alfabeto                      Σ: {0, 1}
Estado Inicial                s: q0
Conjunto de Estados finales   F: {q2, q4}
Funciones de transición       𝜹:
    T(q0, 0) = q1 q3 
    T(q0, 1) = q0 q1 
    T(q1, 1) = q2 
    T(q2, 0) = q2 
    T(q2, 1) = q2 
    T(q3, 0) = q4 
    T(q3, 1) = q1 
    T(q4, 0) = q4 
    T(q4, 1) = q4 
               Tipo de autómata: Autómata Finito
                                 No Determinístico (AFND)
---------------------------------------------------------

```

**Eliminar transición**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
6
    [0] T(A, a) = B 
    [1] T(A, b) = C 
    [2] T(B, a) = B 
    [3] T(B, b) = E 
    [4] T(C, a) = B 
    [5] T(C, b) = C 
    [6] T(D, a) = B 
    [7] T(D, b) = C 
    [8] T(E, a) = B 
    [9] T(E, b) = D 
9
¿Está seguro de que quiere eliminar el elemento [9] T(E, b) = D ? [si/no]
si

[*] Elemento borrado exitosmanete

### Autómata actualizado ###

-------------------<{ Examen primer parcial: Autómata 1 }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------
```

**Editar nombre**

```
Seleccione un atributo a editar del autómata: 
[1] Conjunto de Estados Posibles
[2] Alfabeto
[3] Estado Inicial
[4] Conjunto de Estados finales
[5] Funciones de transición
[6] Eliminar función de transición
[7] Nombre del autómata
7

Ingrese el nombre o identificador del autómata: 
Prueba

### Autómata actualizado ###

-------------------<{ Prueba }>-------------------
A = (Q, Σ, δ, s, F)
Conjunto de Estados Posibles  Q: {A, B, C, D, E}
Alfabeto                      Σ: {a, b}
Estado Inicial                s: A
Conjunto de Estados finales   F: {E}
Funciones de transición       𝜹:
    T(A, a) = B 
    T(A, b) = C 
    T(B, a) = B 
    T(B, b) = E 
    T(C, a) = B 
    T(C, b) = C 
    T(D, a) = B 
    T(D, b) = C 
    T(E, a) = B 
    T(E, b) = D 
               Tipo de autómata: Autómata Finito
                                 Determinístico (AFD)
---------------------------------------------------------

```

### `exportAutomaton()`

`void` 

Exportar autómata en formato JSON

Si la memoria está vacía, se alerta al usuario y se omite el proceso de exportación

```cpp
if (automata.empty()) {
        cout << endl
             << "[!] Memoria vacía. Favor de crear o cargar autómata" << endl;
    }
```

En caso de que sí existan autómatas es memoria, se proce a desplegar todos los disponibles y se espera una selección del usuario

```cpp
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
```

Con base en la selección del usuario, se instancia un nuevo objeto de tipo autómata.

```cpp
Automaton automaton = automata[automatonChoice];
```

Se crea un nuevo objeto de tipo JSON con los atributos del autómata seleccionado y se imprimen en consola

```cpp
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
```

Se solicita al usuario ingrese un nombre para el archivo/autómata

```cpp
cout << endl
             << "Ingrese el nombre o identificador del autómata: " << endl;
        cin >> filename;
        
d::ofstream outputFile(filename + ".json");
```

Se escriben datos en archivo. Se verifica que el archivo haya sido abierto correctamente, se escribe, cierra y comunica al usuario éxito en la operación. En caso contrario, se alerta al usuario del fallo en la operación.

```cpp
        if (outputFile.is_open()) {
            outputFile << automatonJSON.dump(4);
            outputFile.close();

            cout << "### Autómata exportado exitosamente ###" << endl
                 << "[*] Acceda al archivo " << filename
                 << ".json generado en el directorio de este programa para "
                    "visualizarlo";
        } else {
            cout << endl << "[!] Error al escribir dentro del archivo" << endl;
        }
```

**Ejemplo**

```
.-----------------------.
||     -{ MENU }-      ||
.-----------------------.
| [1] Crear autómata    |
| [2] Cargar autómata   |
| [3] Ejecutar autómata |
| [4] Editar autómata   |
| [5] Exportar autómata |
|             [6] Salir |
.-----------------------.
5

--- { Autómatas disponibles } ---
[1] Actividad 6: Ejercicio 1
[2] Evaluación #1
[3] Evaluación #2
[4] Examen primer parcial: Autómata 1
Seleccione un autómata: 1
Actividad 6: Ejercicio 1 : [{"alphabet":["0","1"],"automatonName":"Actividad 6: Ejercicio 1","finalStates":["q0"],"initialState":"q0","posibleStates":["q0","q1","q2","q3"],"transitionMap":[[["q0","0"],["q2"]],[["q0","1"],["q1"]],[["q1","0"],["q3"]],[["q1","1"],["q0"]],[["q2","0"],["q0"]],[["q2","1"],["q3"]],[["q3","0"],["q1"]],[["q3","1"],["q2"]]]}]
Ingrese el nombre o identificador del autómata: 
Prueba1
### Autómata exportado exitosamente ###
[*] Acceda al archivo Prueba1.json generado en el directorio de este programa para visualizarlo
```

Prueba1.json

[Prueba1.json](CFLAP%20-%20Documentaci%C3%B3n%2028ce59200efc80658a10fc100d723995/Prueba1.json)

```json
{
    "Actividad 6: Ejercicio 1": [
        {
            "alphabet": [
                "0",
                "1"
            ],
            "automatonName": "Actividad 6: Ejercicio 1",
            "finalStates": [
                "q0"
            ],
            "initialState": "q0",
            "posibleStates": [
                "q0",
                "q1",
                "q2",
                "q3"
            ],
            "transitionMap": [
                [
                    [
                        "q0",
                        "0"
                    ],
                    [
                        "q2"
                    ]
                ],
                [
                    [
                        "q0",
                        "1"
                    ],
                    [
                        "q1"
                    ]
                ],
                [
                    [
                        "q1",
                        "0"
                    ],
                    [
                        "q3"
                    ]
                ],
                [
                    [
                        "q1",
                        "1"
                    ],
                    [
                        "q0"
                    ]
                ],
                [
                    [
                        "q2",
                        "0"
                    ],
                    [
                        "q0"
                    ]
                ],
                [
                    [
                        "q2",
                        "1"
                    ],
                    [
                        "q3"
                    ]
                ],
                [
                    [
                        "q3",
                        "0"
                    ],
                    [
                        "q1"
                    ]
                ],
                [
                    [
                        "q3",
                        "1"
                    ],
                    [
                        "q2"
                    ]
                ]
            ]
        }
    ]
}
```

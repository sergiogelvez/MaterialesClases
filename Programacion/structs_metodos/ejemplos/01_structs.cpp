// 01_structs.cpp — Agrupar datos con struct
// Compilar: g++ -std=c++17 -Wall 01_structs.cpp -o structs
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Estudiante {
    string nombre;
    int codigo;
    double nota;
};

// Paso por referencia constante: no copia y no modifica
void imprimir(const Estudiante &e) {
    cout << e.codigo << "  " << e.nombre << "  " << e.nota << endl;
}

// Paso por referencia: sí modifica el original
void bonificar(Estudiante &e, double puntos) {
    e.nota = e.nota + puntos;
    if (e.nota > 5.0) {
        e.nota = 5.0;
    }
}

double promedio(const vector<Estudiante> &grupo) {
    double suma = 0.0;
    for (const Estudiante &e : grupo) {
        suma += e.nota;
    }
    return suma / grupo.size();
}

int main() {
    Estudiante a;            // campos sin inicializar
    a.nombre = "Ana";
    a.codigo = 2251001;
    a.nota = 4.2;

    Estudiante b{"Luis", 2251002, 3.4};   // inicialización con llaves

    vector<Estudiante> grupo;
    grupo.push_back(a);
    grupo.push_back(b);
    grupo.push_back({"Marta", 2251003, 4.7});

    bonificar(grupo[1], 0.3);

    for (const Estudiante &e : grupo) {
        imprimir(e);
    }
    cout << "Promedio: " << promedio(grupo) << endl;
    return 0;
}

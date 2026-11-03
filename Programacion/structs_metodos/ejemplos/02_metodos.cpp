// 02_metodos.cpp — Funciones que viven dentro del struct
// Compilar: g++ -std=c++17 -Wall 02_metodos.cpp -o metodos
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Rectangulo {
    double ancho;
    double alto;

    // Métodos que solo consultan: llevan const
    double area() const {
        return ancho * alto;
    }

    double perimetro() const {
        return 2 * (ancho + alto);
    }

    bool esCuadrado() const {
        return ancho == alto;
    }

    // Método que modifica el objeto: sin const
    void escalar(double factor) {
        ancho = ancho * factor;
        alto = alto * factor;
    }
};

struct Estudiante {
    string nombre;
    vector<double> notas;

    void agregarNota(double n) {
        notas.push_back(n);
    }

    double promedio() const {
        if (notas.empty()) {
            return 0.0;
        }
        double suma = 0.0;
        for (double n : notas) {
            suma += n;
        }
        return suma / notas.size();
    }

    bool aprobo() const {
        return promedio() >= 3.0;
    }
};

int main() {
    Rectangulo r{3.0, 4.0};
    cout << "Area: " << r.area() << endl;
    cout << "Perimetro: " << r.perimetro() << endl;

    r.escalar(2.0);
    cout << "Nuevo tamano: " << r.ancho << " x " << r.alto << endl;
    cout << "Nueva area: " << r.area() << endl;

    Rectangulo c{5.0, 5.0};
    cout << "c es cuadrado? " << c.esCuadrado() << endl;

    Estudiante e{"Ana", {}};
    e.agregarNota(3.5);
    e.agregarNota(4.0);
    e.agregarNota(2.8);
    cout << e.nombre << ": promedio " << e.promedio()
         << ", aprobo = " << e.aprobo() << endl;
    return 0;
}

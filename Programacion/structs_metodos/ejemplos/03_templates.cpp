// 03_templates.cpp — Una sola definición para muchos tipos
// Compilar: g++ -std=c++17 -Wall 03_templates.cpp -o templates
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
T mayor(T a, T b) {
    if (a > b) {
        return a;
    }
    return b;
}

template <typename T>
T sumar(const vector<T> &v) {
    T total{};               // "cero" del tipo T
    for (const T &x : v) {
        total += x;
    }
    return total;
}

template <typename T>
struct Par {
    T primero;
    T segundo;

    T elMayor() const {
        return mayor(primero, segundo);
    }
};

int main() {
    cout << mayor(3, 7) << endl;          // T = int
    cout << mayor(2.5, 1.75) << endl;     // T = double

    string x = "perro", y = "gato";
    cout << mayor(x, y) << endl;          // T = string

    cout << mayor<double>(3, 2.5) << endl; // tipo explícito

    vector<int> enteros{1, 2, 3, 4};
    vector<double> reales{0.5, 0.25, 0.25};
    vector<string> palabras{"hola", " ", "mundo"};
    cout << sumar(enteros) << endl;
    cout << sumar(reales) << endl;
    cout << sumar(palabras) << endl;

    Par<int> p{3, 8};
    Par<string> n{"Ana", "Luis"};
    cout << p.elMayor() << " " << n.elMayor() << endl;
    return 0;
}

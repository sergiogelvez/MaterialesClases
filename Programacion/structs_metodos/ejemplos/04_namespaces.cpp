// 04_namespaces.cpp — Apellidos para los nombres
// Compilar: g++ -std=c++17 -Wall 04_namespaces.cpp -o namespaces
#include <iostream>

namespace rectangulos {
    double area(double base, double altura) {
        return base * altura;
    }
}

namespace triangulos {
    double area(double base, double altura) {
        return base * altura / 2.0;
    }
}

int main() {
    std::cout << rectangulos::area(3.0, 4.0) << std::endl;   // 12
    std::cout << triangulos::area(3.0, 4.0) << std::endl;    // 6

    using std::cout;
    using std::endl;
    cout << "Ya no hace falta escribir std:: delante de cout" << endl;
    return 0;
}

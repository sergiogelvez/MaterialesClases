// 05_integrador.cpp — struct + métodos + template + namespace
// Compilar: g++ -std=c++17 -Wall 05_integrador.cpp -o integrador
#include <cmath>
#include <iostream>
#include <vector>

namespace geo {

    template <typename T>
    struct Punto {
        T x;
        T y;

        void mover(T dx, T dy) {
            x = x + dx;
            y = y + dy;
        }

        double distancia(const Punto<T> &otro) const {
            double ddx = otro.x - x;
            double ddy = otro.y - y;
            return std::sqrt(ddx * ddx + ddy * ddy);
        }
    };

    template <typename T>
    double longitudRecorrido(const std::vector<Punto<T>> &ruta) {
        double total = 0.0;
        for (std::size_t i = 1; i < ruta.size(); i++) {
            total += ruta[i - 1].distancia(ruta[i]);
        }
        return total;
    }

}

int main() {
    geo::Punto<int> casilla{2, 3};
    casilla.mover(1, 1);
    std::cout << "Casilla: (" << casilla.x << ", " << casilla.y << ")\n";

    std::vector<geo::Punto<double>> ruta{
        {0.0, 0.0}, {3.0, 4.0}, {3.0, 10.0}
    };
    std::cout << "Recorrido: " << geo::longitudRecorrido(ruta) << "\n";
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class Carta {
public:
    int valorCarta;
    string tipoCarta;
    string nombreCarta;
    
    Carta(int valor, string tipo, string nombre) : valorCarta(valor), tipoCarta(tipo), nombreCarta(nombre) {}
};

class Baraja {
private:
    vector<Carta> cartas;
    
public:
    Baraja() {
        const string tipos[] = {"corazones", "diamantes", "treboles", "picas"};
        for (const string& tipo : tipos) {
            for (int valor = 1; valor <= 13; ++valor) {
                string nombre;
                int valorCarta;
                switch (valor) {
                    case 1:
                        nombre = "As";
                        valorCarta = 11;
                        break;
                    case 11:
                        nombre = "J";
                        valorCarta = 10;
                        break;
                    case 12:
                        nombre = "Q";
                        valorCarta = 10;
                        break;
                    case 13:
                        nombre = "K";
                        valorCarta = 10;
                        break;
                    default:
                        nombre = to_string(valor);
                        valorCarta = valor;
                }
                cartas.push_back(Carta(valorCarta, tipo, nombre));
            }
        }
    }

    Carta sacarCarta() {
        if (cartas.empty()) {
            throw runtime_error("No hay más cartas en la baraja");
        }
        int index = rand() % cartas.size();
        Carta carta = cartas[index];
        cartas.erase(cartas.begin() + index);
        return carta;
    }
};

int main() {
    srand(time(NULL));
    Baraja baraja;
    int contador = 0;
    int numAses = 0;
    char opc = 's';

    while (opc == 's' || opc == 'S') {
        Carta miCarta = baraja.sacarCarta();

        if (miCarta.nombreCarta == "As") {
            cout << "Ha salido un As, que valor quieres darle, 11 o 1?: ";
            int valorAs;
            cin >> valorAs;
            while (valorAs != 1 && valorAs != 11) {
                cout << "Valor incorrecto. Por favor, elige 1 o 11: ";
                cin >> valorAs;
            }
            miCarta.valorCarta = valorAs;
            if (valorAs == 11) numAses++;
        }

        cout << "\nHa salido la carta " << miCarta.nombreCarta << " de " << miCarta.tipoCarta << endl;
        contador += miCarta.valorCarta;

        while (contador > 21 && numAses > 0) {
            contador -= 10;
            numAses--;
        }

        if (contador > 21) {
            cout << "Tu puntaje excedio los 21 puntos, has perdido\n";
            break;
        }

        cout << "Tu puntaje actual es: " << contador << "\n\n";
        if (contador == 21) {
            cout << "Felicidades, has acumulado 21 puntos, ganaste\n";
            break;
        }

        cout << "Quieres seguir jugando? S/N: ";
        cin >> opc;
        while (opc != 'n' && opc != 'N' && opc != 'S' && opc != 's') {
            cout << "Input incorrecto. Por favor, ingresa S (si) o N (no): ";
            cin >> opc;
        }
    }

    if (opc == 'N' || opc == 'n') {
        Carta miCarta = baraja.sacarCarta();
        cout << "La siguiente carta era: " << miCarta.nombreCarta << " de " << miCarta.tipoCarta << endl;
    }
    system("pause");
    system("cls");
    return 0;
}

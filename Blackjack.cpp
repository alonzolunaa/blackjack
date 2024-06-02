#include <iostream>
#include <cstdlib>
#include <ctime>
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
public:
    Carta sacarCarta() {
        const string tipos[] = {"corazones", "diamantes", "treboles", "picas"};
        int valor = rand() % 13 + 1;
        string nombre;
        int valorCarta;

        switch (valor) {
            case 1:
                nombre = "As";
                valorCarta = 11;
                break;
            case 11:
            case 12:
            case 13:
                nombre = (valor == 11) ? "J" : (valor == 12) ? "Q" : "K";
                valorCarta = 10;
                break;
            default:
                nombre = to_string(valor);
                valorCarta = valor;
        }

        int tipoIndex = rand() % 4;
        string tipo = tipos[tipoIndex];

        return Carta(valorCarta, tipo, nombre);
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

        cout << "Ha salido la carta " << miCarta.nombreCarta << " de " << miCarta.tipoCarta << endl;
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
            cout << "\nInput incorrecto. Por favor, ingresa S (si) o N (no): ";
            cin >> opc;
        }
        system("cls");
    }

    if (opc == 'N' || opc == 'n') {
        Carta miCarta = baraja.sacarCarta();
        cout << "La siguiente carta era: " << miCarta.nombreCarta << " de " << miCarta.tipoCarta << endl;
        cout<<"Puntaje final: "<<contador<<"\n";
    }

    system("pause");
    system("cls");
    return 0;
}

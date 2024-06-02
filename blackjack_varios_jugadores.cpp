#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cctype>

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

        int tipoIndex = rand() % 4;
        string tipo = tipos[tipoIndex];

        return Carta(valorCarta, tipo, nombre);
    }
};



int main(){
   while(true){
        srand(time(NULL));
        int numJugadores;
        Baraja baraja;

        cout<<"Elige el numero de jugadores: ";
        cin>>numJugadores;
        vector<int> puntajes(numJugadores, 0);
        system("cls");
        
        for(int jugadores = 0; jugadores<numJugadores;jugadores++){
            srand(time(NULL));
            int numAses = 0;
            char opc = 's';
            while(opc== 's' ||opc== 'S'){
                cout<<"Turno del jugador "<< jugadores +1<<"\n\n";
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
                    goto saltar;
                }

                cout << "Ha salido la carta " << miCarta.nombreCarta << " de " << miCarta.tipoCarta << endl;
                saltar:
                puntajes[jugadores] += miCarta.valorCarta;
            
                while (puntajes[jugadores] > 21 && numAses > 0) {
                    cout<<"El valor del As anterior cambio a 1\n";
                    puntajes[jugadores] -= 10;
                    numAses--;
                }
                
                if (puntajes[jugadores] > 21) {
                    cout << "Tu puntaje excedio los 21 puntos, has perdido\n"<<endl;
                    cout<<"Puntaje final: "<<puntajes[jugadores]<<"\n";
                    break;
                }
                cout << "Tu puntaje actual es: " << puntajes[jugadores] << "\n\n";
                if (puntajes[jugadores] == 21) {
                    cout << "Felicidades, has acumulado 21 puntos, ganaste\n";
                    break;
                }
        
                cout << "Quieres agarrar otra carta? S/N: ";
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
            cout<<"Puntaje final: "<<puntajes[jugadores]<<"\n\n";
            }
        }
        
        char resp;
        cout<<"Jugar de nuevo? S/N?: ";
        cin>>resp;
        while (resp != 'n' && resp != 'N' && resp != 'S' && resp != 's') {
            cout << "\nInput incorrecto. Por favor, ingresa S (si) o N (no): ";
            cin >> resp;
        }

        if(resp == 'n'||resp == 'N'){
            system("cls");
            break;
        }
        system("cls");
    
   }

}
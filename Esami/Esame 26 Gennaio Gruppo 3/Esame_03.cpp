#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct Coppia {
	int velocitaX;
	int velocitaY;
};
typedef Coppia* PCop;

//PROTOTIPI
void lettura_elenco_coppie (PCop&, int&);
void riepilogo_coppie (PCop, int);
void scambio_ottimizzato_velocita_min (PCop&, int);
bool verifica_palindromia (PCop, int);

int main() {
	//DICHIARAZIONI VARIABILI UTILI
	PCop Coppie = NULL;
	int numero_coppie = 0;
	
	//CHIAMATE FUNZIONI
	lettura_elenco_coppie(Coppie, numero_coppie);
	cout << "[INFO]Elenco coppie di motori coassiali:" << endl;
	riepilogo_coppie(Coppie, numero_coppie);
	
	if(verifica_palindromia(Coppie, numero_coppie)) {
		cout << "[INFO]L'elenco delle coppie di motori coassiali è PALINDROMO." << endl;
	} else {
		cout << "[INFO]L'elenco delle coppie di motori coassiali non è palindromo." << endl;
	}
	
	scambio_ottimizzato_velocita_min(Coppie, numero_coppie);
	cout << "[INFO]Elenco coppie di motori coassiali post-ottimizzazione:" << endl;
	riepilogo_coppie(Coppie, numero_coppie);
}

void lettura_elenco_coppie (PCop& Coppie, int& numero_coppie) {
	//DICHIARAZIONI VARIABILI UTILI
	ifstream file;
	
	//LETTURA NUMERO COPPIE
	file.open("motori.txt", ios::in);
	if(!file) {
		cout << "[ERRORE]Impossibile accedere all'elenco delle coppie di motori coassiali. Terminazione del programma..." << endl;
		exit(1);
	}
	file >> numero_coppie;
	
	//ALLOCAZIONE E RIMEPIMENTO VETTORE DI COPPIE
	Coppie = new Coppia[numero_coppie];
	numero_coppie = 0;
	while (!file.eof()) {
		file >> (*(Coppie + numero_coppie)).velocitaX;
		file >> (*(Coppie + numero_coppie)).velocitaY;
		numero_coppie++;
	}
	file.close();
}

void riepilogo_coppie (PCop Coppie, int numero_coppie) {
	//STAMPA A VIDEO VETTORE DI COPPIE
	for (int i=0; i<numero_coppie; i++, cout << endl) {
		cout << "[*]Velocita coppia di motori coassiali " << i+1 << ":" << endl;
		cout << "[VELOCITA MOTORE 1]--->" << (*(Coppie + i)).velocitaX << endl; 
		cout << "[VELOCITA MOTORE 2]--->" << (*(Coppie + i)).velocitaY << endl;
	}
}

void scambio_ottimizzato_velocita_min (PCop& Coppie, int numero_coppie) {
	//DICHIARAZIONI VARAIBILI UTILI
	int velocitaX_min = 0, pos_primo_min = 0, pos_ultimo_min = 0;
	bool pos_primo_min_trovata = false;
	Coppia temp;
	
	//CALCOLO VELOCITAX MINIMA
	velocitaX_min = (*Coppie).velocitaX;
	for (int i=0; i<numero_coppie; i++) {
		if ((*(Coppie + i)).velocitaX < velocitaX_min) {
			velocitaX_min = (*(Coppie + i)).velocitaX; 	
		}
	}
	
	//DETERMINAZIONE INDICE PRIMO ELEMENTO A VELOCITAX MINIMA
	for (int i=0; i<numero_coppie; i++) {
		if ((*(Coppie + i)).velocitaX == velocitaX_min) {
			if (pos_primo_min_trovata) {
				pos_ultimo_min = i;
			} else {
				pos_primo_min = i;
				pos_ultimo_min = i;
				pos_primo_min_trovata = true;
			}
		}
	}
	
	//SCAMBIO DELLE COPPIE
	cout << "[INFO]Ottimizzazione delle coppie di motori..." << endl;
	if(pos_primo_min != pos_ultimo_min) {
		temp = *(Coppie + pos_primo_min);
		*(Coppie + pos_primo_min) = *(Coppie + pos_ultimo_min);
		*(Coppie + pos_ultimo_min) = temp;
		cout << "[SUCCESS]Ottimizzazione completata!" << endl;
	} else {
		cout << "[WANRNING]Solo una coppia presente con la velocita minima del motore 1. Ottimizzazione non effettuata." << endl;
	}
}

bool verifica_palindromia (PCop Coppie, int numero_coppie) {
	//VERIFICA PALINDROMIA
	for (int i=0, j=numero_coppie-1; j>i; i++, j--) {
		if ( ( (*(Coppie + i)) .velocitaX != (*(Coppie + j)).velocitaX ) || ( (*(Coppie + i)) .velocitaY != (*(Coppie + j)) .velocitaY ) ) {
			return false;
		}
	}
	return true;
}


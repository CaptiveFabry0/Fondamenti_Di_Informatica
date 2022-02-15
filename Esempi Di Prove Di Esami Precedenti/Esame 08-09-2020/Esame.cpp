#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct Navicella {
	int posX;
	int posY;
	int punteggio;
};
typedef Navicella* PNav;

//PROTOTIPI
void popolamento_campo_di_battaglia (PNav&, int&);
void riepilogo_campo_di_battaglia (PNav, int);
void lancio_missile (PNav, int);
bool cattura_navicella_bonus (PNav&, int&);

int main() {
	PNav Navicelle = NULL;
	int numero_navicelle = 0;
	
	//CHIAMATE FUNZIONI
	popolamento_campo_di_battaglia(Navicelle, numero_navicelle);
	cout << "[INFO]Elenco navicelle schierate sul campo di battaglia:" << endl;
	riepilogo_campo_di_battaglia(Navicelle, numero_navicelle);
	
	lancio_missile(Navicelle, numero_navicelle);
	
	if (cattura_navicella_bonus(Navicelle, numero_navicelle)) {
		cout << "[RISULATO CATTURA]Cattura effettuata!" << endl;
		cout << "[CAMPO DI BATTAGLIA]Elenco aggiornato navicelle schierate sul campo di battaglia:" << endl;
		riepilogo_campo_di_battaglia(Navicelle, numero_navicelle);
	} else {
		cout << "[RISULTATO CATTURA]Cattura fallita. Nessuna navicella bonus schierata!" << endl;
	}
}

void popolamento_campo_di_battaglia (PNav& Navicelle, int& numero_navicelle) {
	//DICHIARZIONI VARIABILI UTILI
	ifstream file;
	
	//CONTEGGIO NUMERO DI NAVICELLE
	file.open("navicelle.txt", ios::in);
	if (!file) {
		cout << "[ERRORE]Impossibile accedere all'elenco delle navicelle sul campo di battaglia. Terminazione del programma..." << endl;
		exit(1);
	}
	file >> numero_navicelle;
	
	//ALLOCAZIONE E RIEMPIMENTO VETTORE DI NAVICELLE
	if (numero_navicelle > 0 && numero_navicelle <= 30) {
		Navicelle = new Navicella[numero_navicelle];
		numero_navicelle = 0;
		if (Navicelle == NULL) {
			cout << "[ERRORE]Memoria insufficiente per un corretto svoglimento del gioco. Terminazione del programma..." << endl;
			exit(1);
		}
		while (!file.eof()) {
			file >> (*(Navicelle + numero_navicelle)).posX;
			file >> (*(Navicelle + numero_navicelle)).posY;
			file >> (*(Navicelle + numero_navicelle)).punteggio;
			
			numero_navicelle++;
		}
		file.close();
	} else {
		cout << "[ERRORE]Numero di navicelle sul campo di battaglia non valido. Terminazione del programma..." << endl;
		exit(1);
	}
}

void riepilogo_campo_di_battaglia (PNav Navicelle, int numero_navicelle) {
	//STAMPA A VIDEO VETTORE DI NAVICELLE
	for (int i=0; i<numero_navicelle; i++, cout << endl) {
		cout << "[*]Informazioni Navicella " << i+1 << ":" << endl;
		cout << "[COORDINATA X]--->" << (*(Navicelle + i)).posX << endl;
		cout << "[COORDINATA Y]--->" << (*(Navicelle + i)).posY << endl;
		cout << "[RICOMPENSA DISTRUZIONE]--->" << (*(Navicelle + i)).punteggio << "PE" << endl;
	}
}

void lancio_missile (PNav Navicelle, int numero_navicelle) {
	//DICHIARAZIONI VARIABILI UTILI
	int posX_missile = 0, posY_missile = 0, punteggio_guadagnato = 0, navicelle_distrutte = 0;
	
	//INSERIMENTO DA TASTIERA POS E POSY DEL MISSILE
	cout << "[LANCIO MISSILE]Inserisci le coordinate di landing del missile:" << endl;
	cout << "[COORDINATA X]--->"; cin >> posX_missile;
	cout << "[COORDINATA Y]--->"; cin >> posY_missile;
	
	//CALCOLO PUNTEGGIO TOTALE GUADAGNATO DALLA DISTRUZIONE DELLE NAVICELLE NEL CAMPO DI ESPLOSIONE DEL MISSILE
	for (int i=0; i<numero_navicelle; i++) {
		if ( ((*(Navicelle + i)).posX >= posX_missile-10 && (*(Navicelle + i)).posX <= posX_missile+10) && ((*(Navicelle + i)).posY >= posY_missile-10 && (*(Navicelle + i)).posY <= posY_missile+10) ) {
			punteggio_guadagnato += (*(Navicelle + i)).punteggio;
			navicelle_distrutte++;
		}
	}
	
	//STAMPA A VIDEO RISULTATO
	if (navicelle_distrutte != 0) {
		cout << "[RISULTATI LANCIO]" << navicelle_distrutte << " navicelle distrutte!" << endl;
		cout << "[RICOMPENSA TOTALE]--->" << punteggio_guadagnato << "PE" << endl;
	} else {
		cout << "[RISULTATI LANCIO]Nessuna navicelle colpita..." << endl;
	}
}

bool cattura_navicella_bonus (PNav& Navicelle, int& numero_navicelle) {
	//RICERCA NAVICELLA CON PUNTEGGIO SUPERIORE A MILLE ED ELIMINAZIONE DAL VETTORE
	cout << "[CATTURA]Cattura della prima navicella bonus schierata in corso..." << endl;
	for (int i=0; i<numero_navicelle; i++) {
		if ((*(Navicelle + i)).punteggio > 1000) {
			numero_navicelle--;
			for (int j=i; j<numero_navicelle; j++) {
				*(Navicelle + j) = *(Navicelle + j + 1);
			}
			return true;
		}
	}
	return false;
}











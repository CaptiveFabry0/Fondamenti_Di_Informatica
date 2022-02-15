#define MAX_STRING 16
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct Pietanza {
	Stringa nome;
	float prezzo;
};
typedef Pietanza* PPiet;

//PROTOTIPI
void inserimento_numero_pietanze (int&);
void inserimento_pietanze (PPiet&, int);
void riepilogo_pietanze (PPiet, int);
void calcolo_prezzo_pietanze (PPiet, int);
void evidenziazione_prima_pietanza_costosa (PPiet&, int);

int main() {
	//DICHIARAZIONI VARIABILI UTILI
	PPiet Pietanze = NULL;
	int numero_pietanze = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_pietanze(numero_pietanze);
	inserimento_pietanze(Pietanze, numero_pietanze);
	cout << "[INFO]Riepilogo pietanze nel menu:" << endl;
	riepilogo_pietanze(Pietanze, numero_pietanze);
	
	calcolo_prezzo_pietanze(Pietanze, numero_pietanze);
	
	evidenziazione_prima_pietanza_costosa(Pietanze, numero_pietanze);
	cout << "[INFO]Riepilogo pietanze nel menu (PRIMA PIETANZA PIU COSTOSA EVIDENZIATA IN MAIUSCOLO):" << endl;
	riepilogo_pietanze(Pietanze, numero_pietanze);
}

void inserimento_numero_pietanze (int& numero_pietanze) {
	//LETTURA DA TASTIERA NUMERO DI PIETANZE
	do {
		cout << "[INSERT]Inserisci il numero di pietanze del menu: "; cin >> numero_pietanze;
		if (numero_pietanze <= 0) {
			cout << "[WARNING]Numero di pietanze inserite non valido. Riprovare." << endl;
		}
	} while (numero_pietanze <= 0);
}

void inserimento_pietanze (PPiet& Pietanze, int numero_pietanze) {
	//ALLOCAZIONE VETTORE DI PIETANZE
	Pietanze = new Pietanza[numero_pietanze];
	if (Pietanze == NULL) {
		cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
		exit(1);
	}
	
	//RIEMPIMENTO VETTORE DI PIETANZE
	for (int i=0; i<numero_pietanze; i++, cout << endl) {
		cout << "[INSERT]Inserisci le informazioni sulla pietanza " << i+1 << ":" << endl;
		cout << "[NOME]--->"; cin >> (*(Pietanze + i)).nome;
		cout << "[PREZZO]{EURO}--->"; cin >> (*(Pietanze + i)).prezzo;
	}
}

void riepilogo_pietanze (PPiet Pietanze, int numero_pietanze) {
	//STAMPA A VIDEO ELEMENTI DEL VETTORE DI PIETANZE
	for (int i=0; i<numero_pietanze; i++, cout << endl) {
		cout << "[*]Pietanza " << i+1 << ":" << endl;
		cout << "[NOME]--->" << (*(Pietanze + i)).nome << endl;
		cout << "[PREZZO]--->" << (*(Pietanze + i)).prezzo << "EURO" << endl;
	}
}

void calcolo_prezzo_pietanze (PPiet Pietanze, int numero_pietanze) {
	//DICHIARAZIONI VARIABILI UTILI
	float prezzo_tot = 0.0;
	Stringa iniziali_pietanze_ricercate = "";
	
	//INSERIMENTO DA TASTIERA DELLE 3 INIZIALI DELLE PIETANZE DA RICERCARE
	cout << "[INSERT]Inserisci le prime 3 lettere delle pietanze di cui calcolare il prezzo complessivo: "; cin >> iniziali_pietanze_ricercate;
	
	//CALCOLO PREZZO TOTALE O USCITA DALLA FUNZIONE
	if (strlen(iniziali_pietanze_ricercate) == 3) {
		for (int i=0; i<numero_pietanze; i++) {
			if(strncmp((*(Pietanze + i)).nome,iniziali_pietanze_ricercate,3) == 0) {
				prezzo_tot += (*(Pietanze + i)).prezzo;
			}
		}
		if (prezzo_tot != 0.0) {
			cout << "[INFO]Prezzo complessivo delle pietanze il cui nome inizia con \"" << iniziali_pietanze_ricercate << "\": " << prezzo_tot << "EURO" << endl;
		} else {
			cout << "[WARNING]Nessuna pietanza trovata il cui nome inizi con \"" << iniziali_pietanze_ricercate << "\"." << endl;
		}
	} else {
		cout << "[WARNING]Impossibile procedere nel calcolo. Numero di caratteri inserito diverso da 3." << endl;
	}
}

void evidenziazione_prima_pietanza_costosa (PPiet& Pietanze, int numero_pietanze) {
	//DICHIARAZIONI VARIABILI UTILI
	float prezzo_max = 0.0;
	int pos_max = 0;
	
	//INDIVIDUAZIONE PRIMA PIETANZA PIU COSTOSA
	prezzo_max = (*Pietanze).prezzo;
	for (int i=0; i<numero_pietanze; i++) {
		if ( (*(Pietanze + i)).prezzo > prezzo_max ) {
			prezzo_max = (*(Pietanze + i)).prezzo;
			pos_max = i;
		}
	}
	
	//EVIDENZIAZIONE PIETANZA A PREZZO MASSIMO
	for (int i=0; i<MAX_STRING; i++) {
		(*(Pietanze + pos_max)).nome[i] = toupper((*(Pietanze + pos_max)).nome[i]);
	}
}


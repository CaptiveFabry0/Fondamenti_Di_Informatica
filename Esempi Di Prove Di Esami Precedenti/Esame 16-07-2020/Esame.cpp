#define MAX_STRING 16
#include <iostream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct Libro {
	Stringa titolo;
	float prezzo;
};
typedef Libro* PLib;

//PROTOTIPI
void inserimento_numero_libri (int&);
void inserimento_libri (PLib&, int);
void elenco_libri (PLib, int);
void inversione_libri (PLib&, int);
void rimozione_libri_costosi (PLib&, int&);

int main() {
	PLib Libri = NULL;
	int numero_libri = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_libri(numero_libri);
	inserimento_libri(Libri, numero_libri);
	cout << "[INFO]Elenco libri sullo scaffale:" << endl;
	elenco_libri(Libri, numero_libri);
	
	inversione_libri(Libri, numero_libri);
	cout << "[INFO]Elenco libri sullo scaffale nelle nuove posizioni:" << endl;
	elenco_libri(Libri, numero_libri);
	
	rimozione_libri_costosi(Libri, numero_libri);
	cout << "[LOADING]Rimozione dei libri piu costosi..." << endl;
	cout << "[INFO]Elenco aggiornato dei libri sullo scaffale:" << endl;
	elenco_libri(Libri, numero_libri);
}

void inserimento_numero_libri (int& numero_libri) {
	//LETTURA DA TASTIERA NUMERO LIBRI SU SCAFFALE
	do {
		cout << "[INSERT]Inserisci il numero di libri sullo scaffale: "; cin >> numero_libri;
		if (numero_libri < 1 || numero_libri > 20) {
			cout << "[WARNING]numero isnerito non valido. Riprovare." << endl;
			cout << "[PROMEMORIA]Lo scaffale ha una capienza massima di 20 libri.[PROMEMORIA]" << endl;
			cout << "[PROMEMORIA]E' necessario aggiungere almeno un libro allo scaffale.[PROMEMORIA]" << endl;
		}
	} while (numero_libri < 1 || numero_libri > 20);
}

void inserimento_libri (PLib& Libri, int numero_libri) {
	//ALLOCAZIONE VETTORE
	Libri = new Libro[numero_libri];
	if(Libri == NULL) {
		cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
		exit(1);
	}
	
	//LETTURA DA TASTIERA CAMPI DEGLI ELEMENTI DEL VETTORE
	for (int i=0; i<numero_libri; i++, cout << endl) {
		cout << "[INSERT]Inserisci i dati del libro " << i+1 << ":" << endl;
		cout << "[TITOLO]{MAX 15 CARATTERI}--->"; cin >> (*(Libri + i)).titolo;
		cout << "[PREZZO]{EURO}--->"; cin >> (*(Libri + i)).prezzo;
	}
}

void elenco_libri (PLib Libri, int numero_libri) {
	//STAMPA A VIDEO CAMPI DEGLI ELEMENTI DEL VETTORE
	for (int i=0; i<numero_libri; i++, cout << endl) {
		cout << "[INDICE " << i << "]Dati del libro " << i+1 << ":" << endl;
		cout << "[TITOLO]--->" << (*(Libri + i)).titolo << endl;
		cout << "[PREZZO]--->" << (*(Libri + i)).prezzo << "EURO" << endl;
	}
}

void inversione_libri (PLib& Libri, int numero_libri) {
	//DICHIARAZIONI VARIABILI UTILI
	Libro temp;
	int ind_inserito = -1;
	
	//INSERIMENTO POSIZIONE SULLO SCAFFALE DALLA QUALE INVERTIRE L'ORDINE DEI LIBRI
	do {
		cout << "[INSERT]Inserisci l'indice del libro a partire dalla cui posizione invertire l'ordine sullo scaffale: "; cin >> ind_inserito;
		if (ind_inserito < 0 || ind_inserito > numero_libri-1) {
			cout <<  "[WARNING]Indice inserito non valido. Riprovare." << endl;
			cout << "[PROMEMORIA]E' possibile inserire indici solo nel range {0-" << numero_libri-1 << "}.[PROMEMORIA]" << endl;
		}
	} while (ind_inserito < 0 || ind_inserito > numero_libri-1);
	
	//INVERSIONE ORDINE
	for (int i=ind_inserito, j=numero_libri-1; j>i; i++, j--) {
		temp = *(Libri + i);
		*(Libri + i) = *(Libri + j);
		*(Libri + j) = temp;
	}
}

void rimozione_libri_costosi (PLib& Libri, int& numero_libri) {
	//DICHIARAZIONI VARIABILI UTILI
	float prezzo_max = (*Libri).prezzo;
	
	//DETERMINAZIONE PREZZO MASSIMO
	for (int i=0; i<numero_libri; i++) {
		if ((*(Libri + i)).prezzo > prezzo_max) {
			prezzo_max = (*(Libri + i)).prezzo;
		}
	}
	
	//ELIMINAZIONE DAL VETTORE ELEMENTI A PREZZO MASSIMO
	for (int i=0; i<numero_libri; i++) {
		if ((*(Libri + i)).prezzo == prezzo_max) {
			numero_libri--;
			for (int j=i; j<numero_libri; j++) {
				*(Libri + j) = *(Libri + j + 1);
			}
			i--;
		}
	}
}


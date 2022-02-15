#define MAX_IMG 20
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Immagine {
	int id;
	float dimX;
	float dimY;
	long bytes;
};

//PROTOTIPI
void inserimento_numero_immagini (int&);
void inserimento_caratteristiche_immagini (Immagine[], int);
void riepilogo_immagini (Immagine[], int);
void rotazione_immagine_maggiore (Immagine[], int);
void duplicazione_immagini(const Immagine[], int, Immagine[], int&);

int main() {
	//DICHIARAZIONI VARIABILI UTILI
	Immagine Immagini[MAX_IMG], Immagini_E_Duplicati[MAX_IMG*2];
	int numero_immagini = 0, numero_immagini_e_duplicati = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_immagini(numero_immagini);
	inserimento_caratteristiche_immagini(Immagini, numero_immagini);
	cout << "[INFO]Elenco immagini salvate su disco:" << endl;
	riepilogo_immagini(Immagini, numero_immagini);
	
	rotazione_immagine_maggiore(Immagini, numero_immagini);
	cout << "[INFO]Elenco immagini salvate su disco (POST ROTAZIONE IMMAGINE MAGGIORE):" << endl;
	riepilogo_immagini(Immagini, numero_immagini);
	
	duplicazione_immagini(Immagini, numero_immagini, Immagini_E_Duplicati, numero_immagini_e_duplicati);
	cout << "[INFO]Elenco immagini salvati su disco ed annessi duplicati:" << endl;
	riepilogo_immagini(Immagini_E_Duplicati, numero_immagini_e_duplicati);
}

void inserimento_numero_immagini (int& numero_immagini) {
	//INSERIMENTO NUMERO IMMAGINI SU DISCO DA TASTIERA
	
	do {
		cout << "[INSERT]Inserisci il numero di immagini presenti su disco: "; cin >> numero_immagini;
		if (numero_immagini < 1 || numero_immagini > 20) {
			cout << "[WARNING]Numero di immagini inserito non valido. Riprovare." << endl;
			cout << "[PROMEMORIA]Il sistema non supporta un numero di immagini su disco superiore a 20.[PROMEMORIA]" << endl;
			cout << "[PROMEMORIA]E'necessario inserire almeno un'immagine su disco.[PROMEMORIA]" << endl;
		}
	} while (numero_immagini < 1 || numero_immagini > 20);
}

void inserimento_caratteristiche_immagini (Immagine Immagini[], int numero_immagini) {
	//INSERIMENTO DA TASTIERA CAMPI DEGLI ELEMENTI DEL VETTORE
	for (int i=0; i<numero_immagini; i++, cout << endl) {
		cout << "[INSERT]Inserisci caratteristiche immagine " << i+1 << ":" << endl;
		cout << "[ID]--->"; cin >> Immagini[i].id;
		cout << "[LUNGHEZZA]{PIXELS}--->"; cin >> Immagini[i].dimX;
		cout << "[LARGHEZZA]{PIXELS}--->"; cin >> Immagini[i].dimY;
		cout << "[DIMENSIONE]{BYTES}--->"; cin >> Immagini[i].bytes;
	}
}

void riepilogo_immagini (Immagine Immagini[], int numero_immagini) {
	//STAMPA A VIDEO ELEMENTI DEL VETTORE
	for (int i=0; i<numero_immagini; i++, cout << endl) {
		cout << "[*]Caratteristiche immagine " << i+1 << ":" << endl;
		cout << "[ID]" << Immagini[i].id << endl;
		cout << "[LUNGHEZZA]{PIXELS}--->" << Immagini[i].dimX << endl;
		cout << "[LARGHEZZA]{PIXELS}--->" << Immagini[i].dimY << endl;
		cout << "[DIMENSIONE]{BYTES}--->" << Immagini[i].bytes << "B" << endl;
	}
}

void rotazione_immagine_maggiore (Immagine Immagini[], int numero_immagini) {
	//DICHIARAZIONI VARIABILI UTILI
	int pos_max = 0;
	long dim_max = 0;
	float temp = 0.0;
	
	//RICERCA IMMAGINE A DIMENSIONE MAGGIORE
	pos_max = 0;
	dim_max = Immagini[0].bytes;
	for (int i=0; i<numero_immagini; i++) {
		if (Immagini[i].bytes > dim_max) {
			pos_max = i;
			dim_max = Immagini[i].bytes;
		}
	}
	
	//ROTAZIONE IMMAGINE A DIMENSIONE MAGGIORE
	temp = Immagini[pos_max].dimX;
	Immagini[pos_max].dimX = Immagini[pos_max].dimY;
	Immagini[pos_max].dimY = temp;
	
	//STAMPA A VIDEO ID DELL'IMMAGINE RUOTATA
	cout << "[INFO]ID dell'immagine ruotata (Dimensione maggiore)--->" << Immagini[pos_max].id << endl;
}

void duplicazione_immagini(const Immagine Immagini[], int numero_immagini, Immagine Immagini_E_Duplicati[], int& numero_immagini_e_duplicati) {
	//AGGIUNTA IMMAGINI ORIGINALI AL VETTORE CONTENENTE ANCHE I DUPLICATI
	for (int i=0; i<numero_immagini; i++) {
		Immagini_E_Duplicati[i] = Immagini[i];
	}
	
	//AGGIUNTA DUPLICATI AL VETTORE CONTENTE ANCHE I DUPLICATI
	numero_immagini_e_duplicati = numero_immagini*2;
	for (int i=0; i<numero_immagini; i++) {
		Immagini_E_Duplicati[numero_immagini + i] = Immagini[i];
	}
}


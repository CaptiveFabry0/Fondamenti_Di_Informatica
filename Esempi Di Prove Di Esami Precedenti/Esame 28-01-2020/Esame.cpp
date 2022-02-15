#include <iostream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct Rettangolo{
	float base;
	float altezza;
};
typedef Rettangolo* PRet;

//PROTOTIPI
void inserimento_numero_rettangoli (int&);
void inserimento_dimensioni_rettangoli (PRet&, int);
void riepilogo_dimensioni_rettangoli (PRet Rettangoli, int numero_rettangoli);
bool verifica_ordinamento_crescente_basi (PRet, int);
void generazione_vettore_pivot (PRet, int, PRet&, int&);

int main() {
	//DICHIARAZIONI VARIABILI UTILI
	PRet Rettangoli = NULL, Rettangoli_Pivot = NULL;
	int numero_rettangoli = 0, numero_rettangoli_pivot = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_rettangoli(numero_rettangoli);
	inserimento_dimensioni_rettangoli(Rettangoli, numero_rettangoli);
	cout << "[INFO]Riepilogo dimensioni dei rettangoli inseriti:" << endl;
	riepilogo_dimensioni_rettangoli(Rettangoli, numero_rettangoli);
	
	if (verifica_ordinamento_crescente_basi(Rettangoli, numero_rettangoli)) {
		cout << "[INFO]Rettangoli ordinati per basi crescenti." << endl;
	} else {
		cout << "[INFO]Rettangoli non ordinati per basi crescenti" << endl;
	}
	
	generazione_vettore_pivot(Rettangoli, numero_rettangoli, Rettangoli_Pivot, numero_rettangoli_pivot);
	if (numero_rettangoli_pivot != 0) {
		cout << "[INFO]Riepilogo dimensioni dei rettangoli di area minore di quella inserita:" << endl;
		riepilogo_dimensioni_rettangoli(Rettangoli_Pivot, numero_rettangoli_pivot);
	}
}

void inserimento_numero_rettangoli (int& numero_rettangoli) {
	//LETTURA DA TASTIERA NUMERO DEI RETTANGOLI
	do {
		cout << "[INSERT]Inserisci il numero dei rettangoli:"; cin >> numero_rettangoli;
		if (numero_rettangoli <= 0) {
			cout << "[WARNING]Numero di rettangoli inserito non valido. Riprovare." << endl;
			cout << "[PROMEMORIA]Il sistema necessita di ALMENO un rettangolo.[PROMEMORIA]" << endl;
		}
	} while (numero_rettangoli <= 0);
}

void inserimento_dimensioni_rettangoli (PRet& Rettangoli, int numero_rettangoli) {
	//DICHIARAZIONI VARIABILI UTILI
	float base = 0, altezza = 0;
	
	//ALLOCAZIONE DINAMICA VETTORE DI RETTANGOLI
	Rettangoli = new Rettangolo[numero_rettangoli];
	if (Rettangoli == NULL) {
		cout << "[ERROR]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'asssistenza." << endl;
		exit(1);
	}
	
	//RIEMPIMENTO VETTORE DI RETTANGOLI
	for (int i=0; i<numero_rettangoli; i++) {
		do {
			cout << "[INSERT]Inserisci le dimensioni del rettangolo " << i+1 << ":" << endl;
			cout << "[BASE]--->"; cin >> base;
			cout << "[ALTEZZA]--->"; cin >> altezza;
			if (base <= 0 || altezza <= 0) {
				cout << "[WARNING]Dimensioni inserite non valide. Riprovare." << endl;
			}
		} while (base <= 0 || altezza <= 0);
		(*(Rettangoli + i)).base = base;
		(*(Rettangoli + i)).altezza = altezza;
	}
}

void riepilogo_dimensioni_rettangoli (PRet Rettangoli, int numero_rettangoli) {
	//STAMPA A VIDEO VETTORE DI RETTANGOLI
	for (int i=0; i<numero_rettangoli; i++, cout << endl) {
		cout << "[*]Dimensioni rettangolo " << i+1 << ":" << endl;
		cout << "[BASE]--->" << (*(Rettangoli + i)).base << endl;
		cout << "[ALTEZZA]--->" << (*(Rettangoli + i)).altezza << endl;
	}
}

bool verifica_ordinamento_crescente_basi (PRet Rettangoli, int numero_rettangoli) {
	//DICHIARAZIONI VARIABILI UTILI
	float prev = 0.0, curr = 0.0;
	
	//VERIFICA
	for (int i=1; i<numero_rettangoli; i++) {
		prev = (*(Rettangoli + i - 1)).base;
		curr = (*(Rettangoli + i)).base;
		if (curr < prev) {
			return false;
		}
	}
	return true;
}

void generazione_vettore_pivot (PRet Rettangoli, int numero_rettangoli, PRet& Rettangoli_Pivot, int& numero_rettangoli_pivot) {
	//DICHIARAZIONI VARIABILI UTILI
	float area_pivot = 0.0, area = 0.0;
	
	//INSERIMENTO DA TASTIERA AREA PIVOT
	do {
		cout << "[INSERT]Inserisci il valore dell'area rispetto alla quale creare il vettore di rettangoli di area minore: "; cin >> area_pivot;
		if (area_pivot <= 0) {
			cout << "[WARNING]Area inserita non valida. Riprovare." << endl;
		}
	} while (area_pivot <= 0);
	
	//CONTEGGIO ELEMENTI DEL VETTORE PIVOT
	for (int i=0; i<numero_rettangoli; i++) {
		area = (*(Rettangoli + i)).base * (*(Rettangoli + i)).altezza;
		if (area < area_pivot) {
			numero_rettangoli_pivot++;
		}
	}
	
	//ALLOCAZIONE E RIEMPIMENTO VETTORE PIVOT
	if (numero_rettangoli_pivot != 0) { //NESSUN RETTANGOLI DI AREA MINORE ALL'AREA PIVOT
		Rettangoli_Pivot = new Rettangolo[numero_rettangoli_pivot];
		numero_rettangoli_pivot = 0;
		if (Rettangoli_Pivot == NULL) {
			cout << "[ERROR]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'asssistenza." << endl;
			exit(1);
		}
		for (int i=0; i<numero_rettangoli; i++) {
			area = (*(Rettangoli + i)).base * (*(Rettangoli + i)).altezza;
			if (area < area_pivot) {
				*(Rettangoli_Pivot + numero_rettangoli_pivot) = *(Rettangoli + i);
				numero_rettangoli_pivot++;
			}
		}
	} else {
		cout << "[WARNING]Nessun rettangoli di area minore di quella inserita." << endl;
	}
}


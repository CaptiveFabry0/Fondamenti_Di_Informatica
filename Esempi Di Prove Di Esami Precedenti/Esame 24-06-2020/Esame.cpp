#define SUP 1
#define INF 0
#define MAX_STRING 6
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct CodiceOperativo {
	Stringa comando;
	long input;
	long output;
};
typedef CodiceOperativo* PCop;

//PROTOTIPI
void inserimento_numero_codici_operativi (int&);
void inserimento_codici_operativi (PCop&, int);
void riepilogo_codici_operativi(PCop, int);
void elenco_codici_operativi_locazioni_estreme (PCop, int, int);
void conta_occorrenze_comandi_assembly (PCop, int);

int main() {
	PCop CodiciOperativi = NULL;
	int numero_codici_operativi = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_codici_operativi(numero_codici_operativi);
	inserimento_codici_operativi(CodiciOperativi, numero_codici_operativi);
	cout << "[INFO]Elenco codici operativi del file assembly:" << endl;
	riepilogo_codici_operativi(CodiciOperativi, numero_codici_operativi);
	
	elenco_codici_operativi_locazioni_estreme(CodiciOperativi, numero_codici_operativi, SUP);
	elenco_codici_operativi_locazioni_estreme(CodiciOperativi, numero_codici_operativi, INF);
	
	conta_occorrenze_comandi_assembly(CodiciOperativi, numero_codici_operativi);
}

void inserimento_numero_codici_operativi (int& numero_codici_operativi) {
	//INSERIMENTO DA TASTIERA NUMERO DEI CODICI OPERATIVI
	do {
		cout << "[INSERT]Inserisci il numero di codici operativi nel file assembly: "; cin >> numero_codici_operativi;
		if (numero_codici_operativi <= 0) {
			cout << "[WARNING]Numero di codici operativi inserito non valido. Riprovare." << endl;
			cout << "[PROMEMORIA]E' necessario inserire almeno un codice operativo[PROMEMORIA]" << endl;
		}
	} while (numero_codici_operativi <= 0);
}

void inserimento_codici_operativi (PCop& CodiciOperativi, int numero_codici_operativi) {
	//ALLOCAZIONE VETTORE DI CODICI OPERATIVI
	CodiciOperativi = new CodiceOperativo[numero_codici_operativi];
	if (CodiciOperativi == NULL) {
		cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma." << endl;
	}
	
	//RIEMPIMENTO VETTORE DI CODICI OPERATIVI
	for (int i=0; i<numero_codici_operativi; i++, cout << endl) {
		cout << "[INSERT]Inserimento caratteristiche codice operativo " << i+1 << ":" << endl;
		cout << "[COMANDO ASSEMBLY]{MAX 5 CHAR}--->"; cin >> (*(CodiciOperativi + i)).comando;
		cout << "[INDIRIZZO PARAMETRO INPUT]--->"; cin >> (*(CodiciOperativi + i)).input;
		cout << "[INDIRIZZO PARAMETRO OUTPUT]--->"; cin >> (*(CodiciOperativi + i)).output;
	}
}

void riepilogo_codici_operativi(PCop CodiciOperativi, int numero_codici_operativi) {
	//STAMPA A A VIDEO VETTORE DI CODICI OPERATIVI
	for (int i=0; i<numero_codici_operativi; i++, cout << endl) {
		cout << "[*]Caratteristiche codice operativo " << i+1 << ":" << endl;
		cout << "[COMANDO ASSEMBLY]{MAX 5 CHAR}--->" << (*(CodiciOperativi + i)).comando << endl;
		cout << "[INDIRIZZO PARAMETRO INPUT]--->" << (*(CodiciOperativi + i)).input << endl;
		cout << "[INDIRIZZO PARAMETRO OUTPUT]--->" << (*(CodiciOperativi + i)).output << endl;
	}
}

void elenco_codici_operativi_locazioni_estreme (PCop CodiciOperativi, int numero_codici_operativi, int criterio) {
	switch (criterio) {
		case SUP:
			{
				//DICHIARAZIONI VARAIBILI UTILI
				long output_max = (*CodiciOperativi).output;
				
				//RICERCA LOCAZIONE DI MEMORIA PER L'OUTPUT CON INDIRIZZO MAGGIORE
				for (int i=0; i<numero_codici_operativi; i++) {
					if ((*(CodiciOperativi + i)).output > output_max) {
						output_max = (*(CodiciOperativi + i)).output;
					}
				}
				
				//STAMPA A VIDEO CODICI OPERATIVI CHE ACCEDONO ALLE LOCAZIONI DI MEMORIA MEGGIORI PER L'OUTPUT
				cout << "[INFO]Elenco dei codici operativi che accedono alle locazioni per il deposito dell'output con indirizzi maggiori:" << endl;
				for (int i=0; i<numero_codici_operativi; i++) {
					if ((*(CodiciOperativi + i)).output == output_max) {
						cout << "[*]Caratteristiche codice operativo " << i+1 << ":" << endl;
						cout << "[COMANDO ASSEMBLY]{MAX 5 CHAR}--->" << (*(CodiciOperativi + i)).comando << endl;
						cout << "[INDIRIZZO PARAMETRO INPUT]--->" << (*(CodiciOperativi + i)).input << endl;
						cout << "[INDIRIZZO PARAMETRO OUTPUT]--->" << (*(CodiciOperativi + i)).output << endl;
						cout << endl;
					}
				}
			}
			break;
		case INF:
			{
				//DICHIARAZIONI VARAIBILI UTILI
				long output_min = (*CodiciOperativi).output;
				
				//RICERCA LOCAZIONE DI MEMORIA PER L'OUTPUT CON INDIRIZZO MAGGIORE
				for (int i=0; i<numero_codici_operativi; i++) {
					if ((*(CodiciOperativi + i)).output < output_min) {
						output_min = (*(CodiciOperativi + i)).output;
					}
				}
				
				//STAMPA A VIDEO CODICI OPERATIVI CHE ACCEDONO ALLE LOCAZIONI DI MEMORIA MEGGIORI PER L'OUTPUT
				cout << "[INFO]Elenco dei codici operativi che accedono alle locazioni per il deposito dell'output con indirizzi minori:" << endl;
				for (int i=0; i<numero_codici_operativi; i++) {
					if ((*(CodiciOperativi + i)).output == output_min) {
						cout << "[*]Caratteristiche codice operativo " << i+1 << ":" << endl;
						cout << "[COMANDO ASSEMBLY]{MAX 5 CHAR}--->" << (*(CodiciOperativi + i)).comando << endl;
						cout << "[INDIRIZZO PARAMETRO INPUT]--->" << (*(CodiciOperativi + i)).input << endl;
						cout << "[INDIRIZZO PARAMETRO OUTPUT]--->" << (*(CodiciOperativi + i)).output << endl;
						cout << endl;
					}
				}
			}
			break;
	}
}

void conta_occorrenze_comandi_assembly (PCop CodiciOperativi, int numero_codici_operativi) {
	//DICHIARAZIONI VARAIBILI UTILI
	Stringa comando;
	int occorenze_comando = 0;
	bool comando_gia_trattato = false;
	
	//CONTEGGIO OCCORRENZE PER COMANDO ASSEMBLY DI OGNI CODICE OPERATIVO
	for (int i=0; i<numero_codici_operativi; i++) {
		//DETRMINIAMO SE IL COMANDO E' GIA STATO TRATTATO
		strcpy(comando,(*(CodiciOperativi + i)).comando);
		for (int j=0; j<=i-1; j++) {
			if (strcmp(comando, (*(CodiciOperativi + j)).comando) == 0) {
				comando_gia_trattato = true;
			}
		}
		
		//DETERMINIAMO LE OCCORRENZE DEL COMANDO SE NON E' STATO GIA TRATTATO
		if (!comando_gia_trattato) {
			for (int j=0; j<numero_codici_operativi; j++) {
			if (strcmp(comando, (*(CodiciOperativi + j)).comando) == 0) {
				occorenze_comando++;
			}
			}
			cout << "[INFO]Occorrenze comando assembly \"" << comando << "\"--->" << occorenze_comando << endl;
		}
		occorenze_comando = 0;
		comando_gia_trattato = false;
	}
}


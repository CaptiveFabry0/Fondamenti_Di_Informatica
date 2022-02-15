#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct Segnale {
	int altezza;
	int frequenza;
};
typedef Segnale* PSig;

//PROTOTIPI
void lettura_report_segnali (PSig&, int&);
void riepilogo_report_segnali (PSig, int);
void creazione_elenchi_massimi (PSig, int, PSig&, int&, PSig&, int&);
void ordinamento_frequenze (PSig&, int);

int main () {
	//DICHIARAZIONI VARIABILI UTILI
	PSig Segnali = NULL, Segnali_Max_Altezza = NULL, Segnali_Max_Frequenza = NULL;
	int numero_segnali = 0, numero_segnali_max_altezza = 0, numero_segnali_max_frequenza = 0;
	
	//CHIAMATE FUNZIONI
	lettura_report_segnali(Segnali, numero_segnali);
	cout << "[INFO]Riepilogo del report sui segnali misurati:" << endl;
	riepilogo_report_segnali(Segnali, numero_segnali);
	
	ordinamento_frequenze(Segnali, numero_segnali);
	cout << "[INFO]Riepilogo del report sui segnali misurati in ordine crescente delle frequenze:" << endl;
	riepilogo_report_segnali(Segnali, numero_segnali);
	
	creazione_elenchi_massimi(Segnali, numero_segnali, Segnali_Max_Altezza, numero_segnali_max_altezza, Segnali_Max_Frequenza, numero_segnali_max_frequenza);
	cout << "[INFO]Elenco dei segnali a maggior altezza:" << endl;
	riepilogo_report_segnali(Segnali_Max_Altezza, numero_segnali_max_altezza);
	cout << "[INFO]Elenco dei segnali a maggior frequenza:" << endl;
	riepilogo_report_segnali(Segnali_Max_Frequenza, numero_segnali_max_frequenza);
}

void lettura_report_segnali (PSig& Segnali, int& numero_segnali) {
	//DICHIARAZIONI VARAIBILI UTILI
	ifstream file;
	
	//CONTEGGIOS SEGNALI NEL FILE DI REPORT
	file.open("segnali.txt", ios::in);
	if (!file) {
		cout << "[ERRORE]Impossibile accedere al file di report dei segnali. Terminazione del programma..." << endl;
		exit(1);
	}
	file >> numero_segnali;
	
	//ALLOCAZIONE E RIEMPIMENTO VETTORE DI SEGNALI
	if (numero_segnali > 0 && numero_segnali <= 30) {
		Segnali = new Segnale[numero_segnali];
		numero_segnali = 0;
		if (Segnali == NULL) {
			cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza del software." << endl;
			exit(1);
		}
		while (!file.eof()) {
			file >> (*(Segnali + numero_segnali)).altezza;
			file >> (*(Segnali + numero_segnali)).frequenza;
			
			numero_segnali++;
		}
		file.close();
	} else {
		cout << "[ERRORE]Numero di segnali misurati non trattabile. Contattare l''assitenza del laboratorio." << endl;
		exit(1);
	}
}

void riepilogo_report_segnali (PSig Segnali, int numero_segnali) {
	//STAMPA A VIDEO VETTORE DI SEGNALI
	for (int i=0; i<numero_segnali; i++, cout << endl) {
		cout << "[*]Dati segnale " << i+1 << ":" << endl;
		cout << "[ALTEZZA]--->" << (*(Segnali + i)).altezza << "A" << endl;
		cout << "[FREQUENZA]--->" << (*(Segnali + i)).frequenza << "HZ" << endl;
	}
}

void creazione_elenchi_massimi (PSig Segnali, int numero_segnali, PSig& Segnali_Max_Altezza, int& numero_segnali_max_altezza, PSig& Segnali_Max_Frequenza, int& numero_segnali_max_frequenza) {
	//DICHIARAZIONI VARIABILI UTILI
	int max_altezza = 0, max_frequenza = 0;
	
	//DETERMINAZIONE ALTEZZA E FREQUENZA MAGGIORE
	for (int i=0; i<numero_segnali; i++) {
		if ((*(Segnali + i)).altezza > max_altezza) {
			max_altezza = (*(Segnali + i)).altezza;
		}
		if ((*(Segnali + i)).frequenza > max_frequenza) {
			max_frequenza = (*(Segnali + i)).frequenza;
		}
	}
	
	//CONTEGGIO SEGNALI A FREQUENZA/ALTEZZA MAGGIORE
	for (int i=0; i<numero_segnali; i++) {
		if ((*(Segnali + i)).altezza == max_altezza) {
			numero_segnali_max_altezza++;
		}
		if ((*(Segnali + i)).frequenza == max_frequenza) {
			numero_segnali_max_frequenza++;
		}
	}
	
	//ALLOCAZIONE E RIMEPIMENTO VETTORI DI SEGNALI A MAGGIOR FREQUENZA/AMPIEZZA
	Segnali_Max_Altezza = new Segnale[numero_segnali_max_altezza];
	Segnali_Max_Frequenza = new Segnale[numero_segnali_max_frequenza];
	numero_segnali_max_altezza = 0;
	numero_segnali_max_frequenza = 0;
	if (Segnali_Max_Altezza == NULL || Segnali_Max_Frequenza == NULL) {
		cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza del software." << endl;
		exit(1);
	}
	for (int i=0; i<numero_segnali; i++) {
		if ((*(Segnali + i)).altezza == max_altezza) {
			*(Segnali_Max_Altezza + numero_segnali_max_altezza) = *(Segnali + i);
			numero_segnali_max_altezza++;
		}
		if ((*(Segnali + i)).frequenza == max_frequenza) {
			*(Segnali_Max_Frequenza + numero_segnali_max_frequenza) = *(Segnali + i);
			numero_segnali_max_frequenza++;
		}
	}
}

void ordinamento_frequenze (PSig& Segnali, int numero_segnali) {
	//DICHIARAZIONI VARAIBILI UTILI
	int pos_min = 0, frequenza_min = 0;
	Segnale temp;
	
	//ORDINAMENTO VETTORE
	for (int i=0; i<numero_segnali-1; i++) {
		pos_min = i;
		frequenza_min = (*(Segnali + i)).frequenza;
		for (int j=i+1; j<numero_segnali; j++) {
			if ((*(Segnali + j)).frequenza < frequenza_min) {
				pos_min = j;
				frequenza_min = (*(Segnali + j)).frequenza;
			}
		}
		temp = *(Segnali + pos_min);
		*(Segnali + pos_min) = *(Segnali + i);
		*(Segnali + i) = temp;
	}
}


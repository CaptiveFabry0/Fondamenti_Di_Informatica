#include <iostream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct PuntoIlluminante {
	int id;
	float luminosita;
	bool stato;
};
typedef PuntoIlluminante* PPunto;

//PROTOTIPI
void inserimento_numero_punti_illuminanti (int&);
void inserimento_caratteristiche_punti_illuminanti (PPunto&, int);
void riepilogo_punti_illuminazione (PPunto, int);
void spegnimento_punti_illuminazione_maggior_consumo (PPunto&, int);
void creazione_lista_punti_illuminazione_rotti (PPunto, int, PPunto&, int&);

int main() {
	PPunto PuntiIlluminanti = NULL, PuntiIlluminanti_Rotti = NULL;
	int numero_punti_illuminanti = 0, numero_punti_illuminanti_rotti = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_punti_illuminanti(numero_punti_illuminanti);
	inserimento_caratteristiche_punti_illuminanti(PuntiIlluminanti, numero_punti_illuminanti);
	cout << "[INFO]Elenco punti luce nell'abitazione:" << endl;
	riepilogo_punti_illuminazione(PuntiIlluminanti, numero_punti_illuminanti);
	
	spegnimento_punti_illuminazione_maggior_consumo(PuntiIlluminanti, numero_punti_illuminanti);
	cout << "[INFO]Elenco punti luce nell'abitazione (POST SPEGNIMENTO PUNTI LUCE A MAGGIOR CONSUMO):" << endl;
	riepilogo_punti_illuminazione(PuntiIlluminanti, numero_punti_illuminanti);
	
	creazione_lista_punti_illuminazione_rotti(PuntiIlluminanti, numero_punti_illuminanti, PuntiIlluminanti_Rotti, numero_punti_illuminanti_rotti);
	cout << "[INFO]Elenco punti luce rotti da sostituire:" << endl;
	riepilogo_punti_illuminazione(PuntiIlluminanti_Rotti, numero_punti_illuminanti_rotti);
}

void inserimento_numero_punti_illuminanti (int& numero_punti_illuminanti) {
	//INSERIMENTO DA TASTIERA DIMENSIONE VETTORE DI PUNTI ILLUMINANTI
	do {
		cout << "[INSERT]Inserisci il numero di punti illuminanti dell'abitazione: "; cin >> numero_punti_illuminanti;
		if (numero_punti_illuminanti<=0) {
			cout << "[WARNING]Numero di punti luce indicato non valido. Riprovare." << endl;
		}
	} while (numero_punti_illuminanti<=0);
}

void inserimento_caratteristiche_punti_illuminanti (PPunto& PuntiIlluminanti, int numero_punti_illuminanti) {
	//ALLOCAZIONE VETTORE DI PUNTI LUCE
	PuntiIlluminanti = new PuntoIlluminante[numero_punti_illuminanti];
	if(PuntiIlluminanti == NULL) {
		cout << "[ERROR]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
		exit(1);
	}
	
	//RIEMPIMENTO VETTORE
	for (int i=0; i<numero_punti_illuminanti; i++, cout << endl) {
		cout << "[*]Inserisci caratteristiche tecniche del punto luce " << i+1 << ":" << endl;
		cout << "[ID]--->"; cin >> (*(PuntiIlluminanti + i)).id;
		cout << "[LUMINOSITA]{0=MIN, 1=MAX}--->"; cin >> (*(PuntiIlluminanti + i)).luminosita;
		cout << "[STATO]{0=SPENTO, 1=ACCESO}--->"; cin >> (*(PuntiIlluminanti + i)).stato;
	}
}

void riepilogo_punti_illuminazione (PPunto PuntiIlluminanti, int numero_punti_illuminanti) {
	//STAMPA ELEMENTI VETTORE DI PUNTI LUCE
	for (int i=0; i<numero_punti_illuminanti; i++, cout << endl) {
		cout << "[*]Caratteristiche tecniche punto luce " << i+1 << ":" << endl;
		cout << "[ID]--->" << (*(PuntiIlluminanti + i)).id << endl;
		cout << "[LUMINOSITA]{0=MIN, 1=MAX}--->" << (*(PuntiIlluminanti + i)).luminosita << endl;
		switch ((*(PuntiIlluminanti + i)).stato) {
			case true:
				cout << "[STATO]--->ACCESO" << endl;
				break;
			case false:
				cout << "[STATO]--->SPENTO" << endl;
				break;
		}
	}
}

void spegnimento_punti_illuminazione_maggior_consumo (PPunto& PuntiIlluminanti, int numero_punti_illuminanti) {
	//DICHIARAZIONI VARIABILI UTILI
	float luminosita_media = 0.0;
	
	//CALCOLO LUMINOSITA MEDIA
	for (int i=0; i<numero_punti_illuminanti; i++) {
		luminosita_media += (*(PuntiIlluminanti + i)).luminosita;
	}
	luminosita_media /= numero_punti_illuminanti;
	
	//SPEGNIMENTO PUNTI LUCE A MAGGIOR CONSUMO
	for (int i=0; i<numero_punti_illuminanti; i++) {
		if ( (*(PuntiIlluminanti + i)).luminosita >= luminosita_media && (*(PuntiIlluminanti + i)).stato ) {
			(*(PuntiIlluminanti + i)).luminosita = 0;
			(*(PuntiIlluminanti + i)).stato = false;
		}
	}
} 

void creazione_lista_punti_illuminazione_rotti (PPunto PuntiIlluminanti, int numero_punti_illuminanti, PPunto& PuntiIlluminanti_Rotti, int& numero_punti_illuminanti_rotti) {
	//CONTEGGIO PUNTI LUCE ROTTI
	for (int i=0; i<numero_punti_illuminanti; i++) {
		if ( (*(PuntiIlluminanti + i)).luminosita != 0 && (*(PuntiIlluminanti + i)).stato == false ) {
			numero_punti_illuminanti_rotti++;
		}
	}
	
	//ALLOCAZIONE VETTORE DI PUNTI LUCE ROTTI
	PuntiIlluminanti_Rotti = new PuntoIlluminante[numero_punti_illuminanti_rotti];
	if(PuntiIlluminanti_Rotti == NULL) {
		cout << "[ERROR]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
		exit(1);
	}
	
	//RIEMPIMENTO VETTORE DI PUNTI LUCE ROTTI
	numero_punti_illuminanti_rotti = 0;
	for (int i=0; i<numero_punti_illuminanti; i++) {
		if ( (*(PuntiIlluminanti + i)).luminosita != 0 && (*(PuntiIlluminanti + i)).stato == false ) {
			*(PuntiIlluminanti_Rotti + numero_punti_illuminanti_rotti) = *(PuntiIlluminanti + i);
			numero_punti_illuminanti_rotti++;
		}
	}
}


#include <iostream>
#include <stdlib.h>
using namespace std;

//TIPI ED ALIAS UTILI
struct Robot {
	int id;
	float velocita;
	float temperatura;
};
typedef Robot* PRobot;

//PROTOTIPI
void inserimento_numero_robot (int&);
void inserimento_caratteristiche_robot (PRobot&, int);
void riepilogo_robot (PRobot, int);
bool ricerca_robot (PRobot, int);
void ottimizzazione_catena_montaggio (PRobot&, int);

int main() {
	PRobot Bracci = NULL;
	int numero_robot = 0;
	
	//CHIAMATE FUNZIONI
	inserimento_numero_robot(numero_robot);
	inserimento_caratteristiche_robot(Bracci, numero_robot);
	cout << "[INFO]Elenco bracci robotici attivi nella catena di montaggio:" << endl;
	riepilogo_robot(Bracci, numero_robot);
	
	if (!ricerca_robot(Bracci, numero_robot)) {
		cout << "[WARNING]Nessun braccio robotico attivo compatibile ai criteri di ricerca." << endl;
	}
	
	ottimizzazione_catena_montaggio(Bracci, numero_robot);
	cout << "[INFO]Elenco bracci robotici attivi nella catena di montaggio POST OTTIMIZZAZIONE:" << endl;
	riepilogo_robot(Bracci, numero_robot);
}

void inserimento_numero_robot (int& numero_robot) {
	//INSERIMENTO DA TASTIERA NUMERO DI ROBOT
	do {
		cout << "[INSERT]Inserisci il numero di bracci robotici attivi nella catena di montaggio: "; cin >> numero_robot;
		if (numero_robot <= 0) {
			cout << "[WARNING]Numero inserito non valido. Il sistema necessita di almeno un braccio robotico attivo. Riprovare." << endl;
		}
	} while (numero_robot <= 0);
}

void inserimento_caratteristiche_robot (PRobot& Bracci, int numero_robot) {
	//ALLOCAZIONE VETTORE DI ROBOT
	Bracci = new Robot[numero_robot];
	if (Bracci == NULL) {
		cout << "[ERROR]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
		exit(1);
	}
	
	//RIEMPIMENTO VETTORE DI ROBOT
	for (int i=0; i<numero_robot; i++, cout << endl) {
		cout << "[INSERT]Inserisci le caratteristiche tecniche di funzionamento del braccio meccanico " << i+1 << ":" << endl;
		cout << "[ID]--->"; cin >> (*(Bracci + i)).id;
		cout << "[VELOCITA DI ROTAZIONE]{rad/s}--->"; cin >> (*(Bracci + i)).velocita;
		cout << "[TEMPERATURA]{C}--->"; cin >> (*(Bracci + i)).temperatura;
	}
}

void riepilogo_robot (PRobot Bracci, int numero_robot) {
	//STAMPA A VIDEO VETTORE DI ROBOT
	for (int i=0; i<numero_robot; i++, cout << endl) {
		cout << "[*]Caratteristiche tecniche di funzionamento braccio robotico " << i+1 << ":" << endl;
		cout << "[ID]--->" << (*(Bracci + i)).id << endl;;
		cout << "[VELOCITA DI ROTAZIONE]{rad/s}--->" << (*(Bracci + i)).velocita << endl;
		cout << "[TEMPERATURA]{C}--->" << (*(Bracci + i)).temperatura << endl;
	}
}

bool ricerca_robot (PRobot Bracci, int numero_robot) {
	//DICHIARAZIONI VARIABILI UTILI
	float velocita_ricercata = 0.0, temperatura_ricercata = 0.0;
	
	//INSERIMENTO DA TASTIERA VELOCITA E TEMPERATURA DEI ROBOT DA RICERCARE
	cout << "[INSERT]Inserisci le caratteristiche tecniche dei bracci robotici da ricercare:" << endl;
	cout << "[VELOCITA DI ROTAZIONE]{rad/s}--->"; cin >> velocita_ricercata;
	cout << "[TEMPERATURA]{C}--->"; cin >> temperatura_ricercata;
	
	//RICERCA ROBOT
	for (int i=0; i<numero_robot; i++) {
		if ( (*(Bracci + i)).temperatura == temperatura_ricercata && (*(Bracci + i)).velocita == velocita_ricercata ) {
			cout << "[INFO]ID primo braccio robotico attivo operante a " << temperatura_ricercata << "C e con una velocita di rotazione di " << velocita_ricercata << "rad/s: " << (*(Bracci + i)).id << endl;
			return true;
		}
	}
	return false; //NESSUN ROBOT TROVATO
}

void ottimizzazione_catena_montaggio (PRobot& Bracci, int numero_bracci) {
	//DICHIARAZIONI VARIABILI UTILI
	float temperatura_max = (*Bracci).temperatura, velocita_max = (*Bracci).velocita;
	
	//DETERMINAZIONE TEMPERATURA MASSIMA E VELOCITA DI ROTAZIONE MASSIMA
	for (int i=0; i<numero_bracci; i++) {
		if ( (*(Bracci + i)).temperatura > temperatura_max ) {
			temperatura_max = (*(Bracci + i)).temperatura;
		}
		if ( (*(Bracci + i)).velocita > velocita_max ) {
			velocita_max = (*(Bracci + i)).velocita;
		}
	}
	
	//OTTIMIZZAZIONE CATENA DI MONTAGGIO
	for (int i=0; i<numero_bracci; i++) {
		if ((*(Bracci + i)).temperatura == temperatura_max) {
			(*(Bracci + i)).velocita = 0.0;
		} else {
			(*(Bracci + i)).velocita = velocita_max;
		}
	}
}

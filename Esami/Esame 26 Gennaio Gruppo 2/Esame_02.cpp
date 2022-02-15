#define MAX_RIG 100
#define MAX_COL 100
#define MIN 0
#define MAX -1
#include <iostream>
using namespace std;

//PROTOTIPI
void inserimento_dimensioni_matrice (int&, int&);
void inserimento_elementi_matrice (int[][MAX_COL], int, int);
void stampa_elementi_matrice (const int[][MAX_COL], int, int);
void ordinamento_colonna(int M[][MAX_COL], int, int, int);
void generazione_vettore_indici (const int[][MAX_COL], int, int, int);

int main() {
	int M[MAX_RIG][MAX_COL];
	int rig_M = 0, col_M = 0;
	inserimento_dimensioni_matrice(rig_M, col_M);
	inserimento_elementi_matrice(M, rig_M, col_M);
	cout << "[INFO]Matrice inserita:" << endl;
	stampa_elementi_matrice(M, rig_M, col_M);
	ordinamento_colonna(M, rig_M, col_M, 0);
	ordinamento_colonna(M, rig_M, col_M, col_M-1);
	cout << "[INFO]Matrice inserita (PRIMA E ULTIMA COLONNA ORDINATE IN SENSO CRESCENTE):" << endl;
	stampa_elementi_matrice(M, rig_M, col_M);
	generazione_vettore_indici(M, rig_M, col_M, MIN);
	generazione_vettore_indici(M, rig_M, col_M, MAX);
}

void inserimento_dimensioni_matrice (int& rig_M, int& col_M) {
	//INSERIMENTO DIMENSIONI MATRICE DA TASTIERA
	do {
		cout << "[INSERT]Inserisci le dimensioni della matrice M:" << endl;
		cout << "[RIGHE]--->"; cin >> rig_M;
		cout << "[COLONNE]--->"; cin >> col_M;
		if ( (rig_M < 2 || rig_M > 100) || (col_M <2 || col_M > 100) ) {
			cout << "[WARNING]Dimensioni inserite non valide. Riprovare." << endl;
		}
	} while ( (rig_M < 2 || rig_M > 100) || (col_M <2 || col_M > 100) );
} 

void inserimento_elementi_matrice (int M[][MAX_COL], int rig_M, int col_M) {
	//INSERIMENTO DA TASTIERA ELEMENTI MATRICE
	for (int i=0; i<rig_M; i++) {
		for (int j=0; j<col_M; j++) {
			cout << "[RIGA " << i+1 << "][COLONNA " << j+1 << "]--->"; cin >> M[i][j];
		}
	}
}

void stampa_elementi_matrice (const int M[][MAX_COL], int rig_M, int col_M) {
	//STAMPA A VIDEO ELEMENTI MATRICE
	for (int i=0; i<rig_M; i++, cout << endl) {
		for (int j=0; j<col_M; j++, cout << "\t") {
			cout << "[RIGA " << i+1 << "][COLONNA " << j+1 << "]--->" << M[i][j];
		}
	}
}

void ordinamento_colonna(int M[][MAX_COL], int rig_M, int col_M, int ind_colonna) {
	//DICHIARAZIONI VARAIBILI UTILI
	int pos_min = 0, min = 0, temp = 0;
	
	//ORDINAMENTO COLONNA
	for (int i=0; i<rig_M-1; i++) {
		pos_min = i;
		min = M[i][ind_colonna];
		for (int j=i+1; j<rig_M; j++) {
			if (M[j][ind_colonna] < min) {
				pos_min = j;
				min = M[j][ind_colonna];
			}
		}
		temp = M[pos_min][ind_colonna];
		M[pos_min][ind_colonna] = M[i][ind_colonna];
		M[i][ind_colonna] = temp;
	}
}

void generazione_vettore_indici (const int M[][MAX_COL], int rig_M, int col_M, int ordinamento) {
	switch (ordinamento) {
		case MIN:
			{
				//DICHIARAZIONI VARAIBILI UTILI
				int min = M[0][0], numero_minimi = 0;
				
				//DETERMINAZIONE MINIMO DI M
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] < min) {
							min = M[i][j];
						}
					}
				}
				
				//CONTEGGIO MINIMI DI M
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] == min) {
							numero_minimi++;
						}
					}
				}
				
				//RIEMPIMENTO VETTORE DI INDICI DI COLONNA DEI MINIMI
				int v2[numero_minimi];
				numero_minimi = 0;
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] == min) {
							v2[numero_minimi] = j;
							numero_minimi++;
						}
					}
				}
				
				//STAMPA VETTORE INDICI
				for (int i=0; i<numero_minimi; i++) {
					cout << "[INDICE DI COLONNA MINIMO " << i+1 << "]--->" << v2[i] << endl;
				}
			}
			break;
		case MAX:
			{
				//DICHIARAZIONI VARAIBILI UTILI
				int max = M[0][0], numero_massimi = 0;
				
				//DETERMINAZIONE MASSIMO DI M
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] > max) {
							max = M[i][j];
						}
					}
				}
				
				//CONTEGGIO MASSIMI DI M
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] == max) {
							numero_massimi++;
						}
					}
				}
				
				//RIEMPIMENTO VETTORE DI INDICI DI RIGA DEI MASSIMI
				int v1[numero_massimi];
				numero_massimi = 0;
				for (int i=0; i<rig_M; i++) {
					for (int j=0; j<col_M; j++) {
						if(M[i][j] == max) {
							v1[numero_massimi] = i;
							numero_massimi++;
						}
					}
				}
				
				//STAMPA VETTORE INDICI
				for (int i=0; i<numero_massimi; i++) {
					cout << "[INDICE DI RIGA MASSIMO " << i+1 << "]--->" << v1[i] << endl;
				}
			}
			break;
	}
}


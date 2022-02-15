#define MAX_COL 100
#define MAX_RIG 100
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Solido {
    int altezza;
    int larghezza;
    int profondita;
};

//PROTOTIPI
void lettura_dimensioni_matrici (int& rig_mat, int& col_mat);
void riempimento_matrice (Solido[][MAX_COL], int&, int);
void stampa_matrice_solidi (const Solido[][MAX_COL], int&, int);
void ordinamento_crescente_colonne (Solido[][MAX_COL], int, int);
void creazione_matrice_ruotata (Solido[][MAX_COL], Solido[][MAX_COL], int, int, int, int);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    Solido Solidi[MAX_RIG][MAX_COL], Solidi_Ruotata[MAX_RIG][MAX_COL];
    int rig_mat = 0, col_mat = 0;
    int& rig_mat_ruotata = col_mat;
    int& col_mat_ruotata = rig_mat;

    //CHIAMATE FUNZIONI
    lettura_dimensioni_matrici(rig_mat, col_mat);
    riempimento_matrice(Solidi, rig_mat, col_mat);
    cout << "[INFO]Elenco dei solidi per l'eleborazione grafica:" << endl << endl;
    stampa_matrice_solidi(Solidi, rig_mat, col_mat);

    ordinamento_crescente_colonne(Solidi, rig_mat, col_mat);
    cout << "[INFO]Elenco dei solidi per l'eleborazione grafica(POST ORDINAMENTO COLONNE):" << endl << endl;
    stampa_matrice_solidi(Solidi, rig_mat, col_mat);

    creazione_matrice_ruotata(Solidi, Solidi_Ruotata, rig_mat, col_mat, rig_mat_ruotata, col_mat_ruotata);
    cout << "[INFO]Elenco della matrice ruotata dei solidi per l'elaborazione grafica:" << endl << endl;
    stampa_matrice_solidi(Solidi_Ruotata, rig_mat_ruotata, col_mat_ruotata);
}

void lettura_dimensioni_matrici (int& rig_mat, int& col_mat) {
    //LETTURA DA TASTIERA DIMESNIONI DELLA MATRICE
    do
    {
        cout << "[PROMEMORIA] Il numero di colonne/righe della matrice di solidi deve essere incluso nell'intervallo [3;100] [PROMEMORIA]" << endl;
        cout << "[INSERT]Inserimento dimensioni della matrice:" << endl;
        cout << "[RIGHE]--->"; cin >> rig_mat;
        cout << "[COLONNE]--->"; cin >> col_mat;
        if (rig_mat < 3 || rig_mat > 100 || col_mat < 3 || col_mat > 100)
        {
            cout << "[WARNING]Dimensioni inserite non valide. Riprovare." << endl;
        }
        
    } while (rig_mat < 3 || rig_mat > 100 || col_mat < 3 || col_mat > 100);
    
}

void riempimento_matrice (Solido Solidi[][MAX_COL], int& rig_mat, int col_mat) {
    //DICHIARAZIONI VARIABILI UTILI
    int altezza = 0;
    int larghezza = 0;
    int profondita = 0;

    //LETTURA DA TASTIERA DIMENSIONI DEI SOLIDI DELLA MATRICE
    for (int i = 0; i < rig_mat; i++)
    {
        for (int j = 0; j < col_mat; j++, cout << endl)
        {
            do
            {
                cout << "[*]Inserimento dimensioni solido " << i*col_mat + j + 1 << ":" << endl;
                cout << "[ALTEZZA]-->"; cin >> altezza;
                cout << "[LARGHEZZA]-->"; cin >> larghezza;
                cout << "[PROFONDITA]-->"; cin >> profondita; 
                if (altezza < 0 || larghezza < 0 || profondita < 0)
                {
                    cout << "[WARNING]Dimensioni inserite non valide. Riprovare." << endl;
                }
            } while (altezza < 0 || larghezza < 0 || profondita < 0); 
            Solidi[i][j].altezza = altezza;
            Solidi[i][j].larghezza = larghezza;
            Solidi[i][j].profondita = profondita;
        }
    }
    
}

void stampa_matrice_solidi (const Solido Solidi[][MAX_COL], int& rig_mat, int col_mat) {
    for (int i = 0; i < rig_mat; i++)
    {
        cout << endl << "[RIGA " << i+1 << "]" << endl << endl;
        for (int j = 0; j < col_mat; j++, cout << endl)
        {
            cout << "[*]Dimensioni solido " << i*col_mat + j + 1 << " nella colonna " << j+1 << " della riga" << ":" << endl;
            cout << "[ALTEZZA]--->" << Solidi[i][j].altezza << endl;
            cout << "[LARGHEZZA]--->" << Solidi[i][j].larghezza << endl;
            cout << "[PROFONDITA]--->" << Solidi[i][j].profondita << endl;
        } 
    }
    
}

void ordinamento_crescente_colonne (Solido Solidi[][MAX_COL], int rig_mat, int col_mat) {
    //DICHIARAZIONI VARIABIILI UTILI
    Solido temp;
    int pos_min = 0;
    int volume = 0;
    int volume_min = 0;
    
    //ORDINAMENTO COLONNE MATRICE
    for (int i = 0; i < col_mat; i++)
    {
        for (int j = 0; j < rig_mat - 1; j++)
        {
            pos_min = j;
            volume_min = Solidi[j][i].altezza * Solidi[j][i].larghezza * Solidi[j][i].profondita;
            for (int z = j + 1; z < rig_mat; z++)
            {
                volume = Solidi[z][i].altezza * Solidi[z][i].larghezza * Solidi[z][i].profondita;
                if (volume < volume_min)
                {
                    volume_min = volume;
                    pos_min = z;
                }
            }
            temp = Solidi[pos_min][i];
            Solidi[pos_min][i] = Solidi[j][i];
            Solidi[j][i] = temp;
        }
    } 
    
}

void creazione_matrice_ruotata (Solido Solidi[][MAX_COL], Solido Solidi_Ruotata[][MAX_COL], int rig_mat, int col_mat, int rig_mat_ruotata, int col_mat_ruotata) {
    //RIEMPIMENTO MATRICE RUOTATA
    for (int curr_riga_mat_ruotata = 0, curr_col_mat = 0; curr_riga_mat_ruotata < rig_mat_ruotata; curr_riga_mat_ruotata++, curr_col_mat++)
    {
        for (int curr_col_mat_ruotata = 0, curr_riga_mat = rig_mat - 1; curr_col_mat_ruotata < col_mat_ruotata; curr_col_mat_ruotata++, curr_riga_mat--)
        {
            Solidi_Ruotata[curr_riga_mat_ruotata][curr_col_mat_ruotata] = Solidi[curr_riga_mat][curr_col_mat];
        }
    }
    
}
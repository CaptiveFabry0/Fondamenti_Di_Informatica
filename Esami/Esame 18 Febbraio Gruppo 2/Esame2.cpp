#define MAX_RIG 100
#define MAX_COL 100
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
enum tipologia {cavaliere = 'C', fantasma = 'F', drago = 'D'};
struct PG{
    int energia;
    tipologia ruolo;
};

//PROTOTIPI
void inserimento_dimensioni_matrice_personaggi (PG[][MAX_COL], int&, int&);
void inserimento_personaggi (PG[][MAX_COL], int, int);
void stampa_matrice_personaggi (const PG[][MAX_COL], int, int);
void valutazione_tipologia_energia_minima(const PG[][MAX_COL], int, int);
void trasformazione_personaggi_energia_minore (PG[][MAX_COL], int, int);

int main() {
    //DICHIARAZIONI VARAIBILI UTILI
    PG Personaggi[MAX_RIG][MAX_COL];
    int rig_mat_pg = 0, col_mat_pg = 0;

    //CHIAMATE FUNZIONI
    inserimento_dimensioni_matrice_personaggi(Personaggi, rig_mat_pg, col_mat_pg);
    inserimento_personaggi(Personaggi, rig_mat_pg, col_mat_pg);
    cout << "[CAMPO DI BATTAGLIA]Scacchiera dei personaggi:" << endl;
    stampa_matrice_personaggi(Personaggi, rig_mat_pg, col_mat_pg);

    valutazione_tipologia_energia_minima(Personaggi, rig_mat_pg, col_mat_pg);

    trasformazione_personaggi_energia_minore(Personaggi, rig_mat_pg, col_mat_pg);
    cout << "[CAMPO DI BATTAGLIA AGGIORNATO]Scacchiera dei personaggi post trasformazioni:" << endl;
    stampa_matrice_personaggi(Personaggi, rig_mat_pg, col_mat_pg);
}

void inserimento_dimensioni_matrice_personaggi (PG Personaggi[][MAX_COL], int& rig_mat_pg, int& col_mat_pg) {
    //LETTURA DA TASTIERA DIMENSIONI MATRICE
    do
    {
        cout << "[INSERT]Inserisci le dimensioni della scacchiera dei personaggi:" << endl;
        cout << "[RIGHE]-->"; cin >> rig_mat_pg;
        cout << "[COLONNE]-->"; cin >> col_mat_pg;
        if ( (rig_mat_pg < 3 || rig_mat_pg > 100) || (col_mat_pg < 3 || col_mat_pg > 100) )
        {
            cout << "[WARNING]Dimensioni inserite non valide. Riprovare" << endl;
        }
    } while ( (rig_mat_pg < 3 || rig_mat_pg > 100) || (col_mat_pg < 3 || col_mat_pg > 100) );
    
}

void inserimento_personaggi (PG Personaggi[][MAX_COL], int rig_mat_pg, int col_mat_pg) {
    //DICHIARAZIONI VARIABILI UTILI
    char ruolo = '\0';
    int energia = 0;

    //INSERIMENTO CARATTERISTICHE PERSONAGGI DA TASTIERA
    for (int i = 0; i < rig_mat_pg; i++)
    {
        for (int j = 0; j < col_mat_pg; j++)
        {
            do
            {
                cout << "[INSERT]Inserisci le caratteristiche del personaggio " << i*col_mat_pg + j + 1 << ":" << endl;
                cout << "[RUOLO][CAVALIERE=C, FANTASMA=F, DRAGO=D]-->"; cin >> ruolo;
                cout << "[ENERGIA]-->"; cin >> energia;
                if (energia < 0 || (ruolo != 'C' && ruolo != 'D' && ruolo != 'F'))
                {
                    cout << "[WARNING]Caratteristiche del personaggio inserite non valide. Riprovare" << endl;
                } else {
                    switch (ruolo)
                    {
                    case 'C':
                        Personaggi[i][j].ruolo = cavaliere;
                        break;
                    case 'F':
                        Personaggi[i][j].ruolo = fantasma;
                        break;
                    case 'D':
                        Personaggi[i][j].ruolo = drago;
                        break;
                    }
                    Personaggi[i][j].energia = energia;
                }
            } while (energia < 0 || (ruolo != 'C' && ruolo != 'D' && ruolo != 'F'));
        }
    }
    
}

void stampa_matrice_personaggi (const PG Personaggi[][MAX_COL], int rig_mat_pg, int col_mat_pg) {
    //STAMPA A VIDEO DELLA MATRICE
    for (int i = 0; i < rig_mat_pg; i++, cout << endl)
    {
        for (int j = 0; j < col_mat_pg; j++, cout << '\t')
        {
            cout << "Personaggio " << i*col_mat_pg + j + 1 << ": ";
            switch (Personaggi[i][j].ruolo)
            {
            case 'C':
                cout << "[RUOLO]--->Cavaliere ";
                break;
            case 'F':
                cout << "[RUOLO]--->Fantasma ";
                break;
            case 'D':
                cout << "[RUOLO]--->Drago ";
                break;
            }
            cout << "[ENERGIA]--->" << Personaggi[i][j].energia << "HP ";
        }  
    }
    
}

void valutazione_tipologia_energia_minima(const PG Personaggi[][MAX_COL], int rig_mat_pg, int col_mat_pg) {
    //DICHIARAZIONI VARIABILI UTILI
    int energia_tot_cavalieri = 0, energia_tot_fantasmi = 0, energia_tot_draghi = 0;

    //DETERMINAZIONE ENERGIE COMPLESSIVE DELLE SINGOLE TIPOLGIE
    for (int i = 0; i < rig_mat_pg; i++)
    {
        for (int j = 0; j < col_mat_pg; j++)
        {
            switch (Personaggi[i][j].ruolo)
            {
            case 'C':
                energia_tot_cavalieri += Personaggi[i][j].energia;
                break;
            case 'F':
                energia_tot_fantasmi += Personaggi[i][j].energia;
                break;
            case 'D':
                energia_tot_draghi += Personaggi[i][j].energia;
                break;
            }
        }
    }

    //STAMPA TIPOLOGIA/E CON ENERGIA COMPLESSIVA MINIMA
    cout << "[RISULTATI LOTTA]Ruolo/i ad energia minore: ";
    if (energia_tot_cavalieri <= energia_tot_draghi && energia_tot_cavalieri <= energia_tot_fantasmi)
    {
        cout << "[CAVALIERI]";
        if (energia_tot_cavalieri == energia_tot_draghi)
        {
            cout << ", [DRAGHI]";
        }
        if (energia_tot_cavalieri == energia_tot_fantasmi)
        {
            cout << ", [FANTASMI]";
        }  
        cout << endl;  
    } else {
        if (energia_tot_draghi <= energia_tot_cavalieri && energia_tot_draghi <= energia_tot_fantasmi)
        {
            cout << "[DRAGHI]";
            if (energia_tot_draghi == energia_tot_cavalieri)
            {
                cout << ", [CAVALIERI]";
            }
            if (energia_tot_draghi == energia_tot_fantasmi)
            {
                cout << ", [FANTASMI]";
            }  
            cout << endl;  
        } else {
            if (energia_tot_fantasmi <= energia_tot_draghi && energia_tot_fantasmi <= energia_tot_cavalieri)
            {
                cout << "[FANTASMI]";
                if (energia_tot_fantasmi == energia_tot_draghi)
                {
                    cout << ", [DRAGHI]";
                }
                if (energia_tot_fantasmi == energia_tot_cavalieri)
                {
                    cout << ", [CAVALIERI]";
                }  
                cout << endl;  
            }
        }
    }
    
}

void trasformazione_personaggi_energia_minore (PG Personaggi[][MAX_COL], int rig_mat_pg, int col_mat_pg) {
    //DICHIARAZIONI VARIABILI UTILI
    int energia_media = 0;

    //DETERMINAZIONE ENERGIA MEDIA
    for (int i = 0; i < rig_mat_pg; i++)
    {
        for (int j = 0; j < col_mat_pg; j++)
        {
            energia_media += Personaggi[i][j].energia;
        }
    }
    energia_media /= rig_mat_pg*col_mat_pg;

    //TASFORMAZIONE PEROSNAGGI AD ENERGIA MINORE (ENERGIA < ENERGIA MEDIA)
    for (int i = 0; i < rig_mat_pg; i++)
    {
        for (int j = 0; j < col_mat_pg; j++)
        {
            if (Personaggi[i][j].energia <= energia_media)
            {
                Personaggi[i][j].ruolo = fantasma;
            } 
        }
    }
    
}

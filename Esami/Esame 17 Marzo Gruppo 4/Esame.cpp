//SVOLGIMENTO SEMI-ERRATO. L'utente deve poter inserire un numero di righe diverso dal numero di colonne. Piccole correzzioni necessarie
#define MAX_STRING 16
#define MAX_RIG 100
#define MAX_COL 100
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct Partecipante{
    float video;
    bool mute;
    Stringa nome;
};

//PROTOTIPI
void inserimento_dimensioni_riunione(int&, int&);
void inserimento_partecipanti_riunione(Partecipante[][MAX_COL], int, int);
void elenco_partecipanti(const Partecipante[][MAX_COL], int, int);
void ban_partecipanti(Partecipante[][MAX_COL], int, int);

int main() {
    Partecipante Riunione[MAX_RIG][MAX_COL];
    int rig_mat_riunione = 0, col_mat_riunione;

    //CHIAMATE FUNZIONI
    inserimento_dimensioni_riunione(rig_mat_riunione, col_mat_riunione);
    inserimento_partecipanti_riunione(Riunione, rig_mat_riunione, col_mat_riunione);
    cout << "[INFO]Elenco partecipanti alla riunione:" << endl;
    elenco_partecipanti(Riunione, rig_mat_riunione, col_mat_riunione);

    ban_partecipanti(Riunione, rig_mat_riunione, col_mat_riunione);
    cout << "[BANHAMMER RESULTS]Elenco partecipanti alla riunione :" << endl;
    elenco_partecipanti(Riunione, rig_mat_riunione - 1, col_mat_riunione);
}

void inserimento_dimensioni_riunione(int& rig_mat_riunione, int& col_mat_riunione) {
    //LETTURA DA TASTIERA DELLE DIMENSIONI DELLA MATRICE QUADRA
    cout << "[PROMEMORIA]A causa di limitazioni di sistema, la Matrice contente i partecipanti della riunione è limitato a 100*100 e non inferiore a 3*3[PROMEMORIA]" << endl;
    do
    {
        cout << "[RIGHE]Inserisci il numero di righe della matrice contenente i partecipanti alla riunione: "; cin >> rig_mat_riunione;
        cout << "[COLONNE]Inserisci il numero di colonne della matrice contenente i partecipanti alla riunione: "; cin >> col_mat_riunione;
        if ((rig_mat_riunione < 3 || rig_mat_riunione > 100) || (col_mat_riunione < 3 || col_mat_riunione > 100))
        {
            cout << "[WARNING]Dimensioni inserite non valide. Il numero di righe ed il numero di colonne devono essere appartenenti all'intervallo [3;100]." << endl;
        }
    } while ((rig_mat_riunione < 3 || rig_mat_riunione > 100) || (col_mat_riunione < 3 || col_mat_riunione > 100));
    
}

void inserimento_partecipanti_riunione(Partecipante Riunione[][MAX_COL], int rig_mat_riunione, int col_mat_riunione) {
    //INSERIMENTO DA TASTIERA DATI DI CIASCUN PARTECIPANTE
    for (int i = 0; i < rig_mat_riunione; i++)
    {
        for (int j = 0; j < col_mat_riunione; j++)
        {
            cout << "[*]Inserimento dati del partecipante:" << endl;
            cout << "[VIDEO QUALITY][MIN=0---1=MAX]--->"; cin >> Riunione[i][j].video;
            cout << "[MUTE]{0=OFF,1=ON}--->"; cin >> Riunione[i][j].mute;
            cout << "[NAME][MAX 15 CHARACTERS]--->"; cin >> Riunione[i][j].nome;
        }
    }
    
}

void elenco_partecipanti(const Partecipante Riunione[][MAX_COL], int rig_mat_riunione, int col_mat_riunione) {
    //STAMPA MATRICE
    for (int i = 0; i < rig_mat_riunione; i++)
    {
        cout << endl << "[RIGA NUMERO " << i+1 << "]:" << endl << endl;
        for (int j = 0; j < col_mat_riunione; j++, cout << endl)
        {
            cout << "[NAME]--->" << Riunione[i][j].nome << endl;
            cout << "[VIDEO QUALITY]--->" << Riunione[i][j].video << endl;
            switch (Riunione[i][j].mute)
            {
            case 1:
                cout << "[MUTE]--->ATTIVO" << endl;
                break;
            case 0:
                cout << "[MUTE]--->DISATTIVO" << endl;
                break;
            }
            if (Riunione[i][j].mute == 0)
            {
                if (Riunione[i][j].video > 0.5)
                {
                    cout << "[SUFFICIENT CONNECTION QUALITY]" << endl;
                } else  {
                    cout << "[BAD CONNECTION QUALITY]" << endl;
                }
            }
        }
    }
    
}

void ban_partecipanti(Partecipante Riunione[][MAX_COL], int rig_pre_ban, int col_pre_ban) {
    //DICHIARAZIONI VARIABILI UTILI
    int indice_riga_ban = -1;
    int rig_post_ban = rig_pre_ban - 1;
    int col_post_ban = col_pre_ban;

    //LETTURA DA TASTIERA RIGA DELLA MATRICE DA ELIMINARE
    do
    {
        cout << "[BANHAMMER]Inserisci l'indice (0-" << rig_pre_ban -1 << ") della riga di cui bannare i partecipanti: "; cin >> indice_riga_ban;
        if (indice_riga_ban < 0 || indice_riga_ban > rig_pre_ban - 1)
        {
            cout << "[WARNING]Indice riga indicato non consentito. Riprovare.";
        }
    } while (indice_riga_ban < 0 || indice_riga_ban > rig_pre_ban - 1);

    //ELIMINAZIONE RIGA DALLA MATRICE
    for (int i = indice_riga_ban; i < rig_post_ban; i++)
    {
        for (int j = 0; j < col_post_ban; j++)
        {
            Riunione[i][j] = Riunione[i+1][j];
        }
    }
    
}
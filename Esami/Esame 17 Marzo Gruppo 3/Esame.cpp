#define MAX_RIEMP 100
#define MAX_RIG 100
#define MAX_COL 100
#define MAX_STRING 16
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct Partecipante {
    Stringa nome;
    float video;
    bool mute;
};


//PROTOTIPI
void inserimento_dimensioni_riunione (int&, int&);
void aggiunta_partecipanti_riunione (Partecipante[][MAX_COL], int, int);
void elenco_partecipanti(const Partecipante[][MAX_COL], int, int);
void evidenziazione_miglior_partecipante (Partecipante[][MAX_COL], int, int);
void creazione_chat (const Partecipante[][MAX_COL], int, int, Partecipante[], int&);

int main() {
    //DICHIARAZIONI VARAIBILI UTILI
    Partecipante Riunione[MAX_RIG][MAX_COL], Chat[MAX_RIEMP];
    int rig_mat_riunione = 0, col_mat_riunione = 0, numero_partecipanti_chat = 0;

    //CHIAMATE FUNZIONI
    inserimento_dimensioni_riunione(rig_mat_riunione, col_mat_riunione);
    aggiunta_partecipanti_riunione(Riunione, rig_mat_riunione, col_mat_riunione);
    cout << "[INFO]Elenco partecipanti alla riunione:" << endl;
    elenco_partecipanti(Riunione, rig_mat_riunione, col_mat_riunione);

    creazione_chat(Riunione, rig_mat_riunione, col_mat_riunione, Chat, numero_partecipanti_chat);

    evidenziazione_miglior_partecipante(Riunione, rig_mat_riunione, col_mat_riunione);
    cout << "[INFO]Elenco riunione con evidenziazione di uno dei partecipanti a miglior qualita video:" << endl;
    elenco_partecipanti(Riunione, rig_mat_riunione, col_mat_riunione);

}

void inserimento_dimensioni_riunione (int& rig_mat_riunione, int& col_mat_riunione) {
    //INSERIMENTO DIMENSIONI DA TASTIERA
    do
    {
        cout << "[INSERT]Inserisci le dimensioni della riunione:" << endl;
        cout << "[RIGHE]--->"; cin >> rig_mat_riunione;
        cout << "[COLONNE]--->"; cin >> col_mat_riunione;
        if ( (rig_mat_riunione < 3 || rig_mat_riunione > 100) || (col_mat_riunione < 3 || col_mat_riunione > 100) )
        {
            cout << "[WARNING]Dimensioni inserite non valide. Riprovare." << endl;
            cout << "[PROMEMORIA]L'applicativo non è realizzato per supportare riunioni a meno di 9 o a più di 1000 partecipanti[PROMEMORIA]" << endl;
        }
    } while ( (rig_mat_riunione < 3 || rig_mat_riunione > 100) || (col_mat_riunione < 3 || col_mat_riunione > 100) );
    
}

void aggiunta_partecipanti_riunione (Partecipante Riunione[][MAX_COL], int rig_mat_riunione, int col_mat_riunione) {
    //DICHIARAZIONI VARIABILI UTILI
    Stringa nome;
    float video;
    int mute;
    
    //AGGIUNTA ELEMENTI DELLA MATRICE DA TASTIERA
    for (int i = 0; i < rig_mat_riunione; i++)
    {
        for (int j = 0; j < col_mat_riunione; j++, cout << endl)
        {
            do
            {
                cout << "[*]Aggiunta partecipante " << i*col_mat_riunione + j + 1 << ":" << endl;
                cout << "[NOME]--->"; cin >> nome;
                cout << "[QUALITA VIDEO]{1=MAX, 0=MIN}--->"; cin >> video;
                cout << "[MUTO]{1=ATTVO, 0=DISABILITATO}--->"; cin >> mute;
                if ( (video < 0.0 || video > 1.0) || (mute != 0 && mute != 1) )
                {
                    cout << "[WARNING]Dati inseriti non validi. Riprovare." << endl;
                } else {
                    strcpy(Riunione[i][j].nome, nome);
                    Riunione[i][j].video = video;
                    Riunione[i][j].mute = mute;
                }
            } while ( (video < 0.0 || video > 1.0) || (mute != 0 && mute != 1) );
        }
    }
    
}

void elenco_partecipanti(const Partecipante Partecipanti[][MAX_COL], int rig_mat_partecipanti, int col_mat_partecipanti) {
    //STAMPA A VIDEO MATRICE
    for (int i = 0; i < rig_mat_partecipanti; i++)
    {
        for (int j = 0; j < col_mat_partecipanti; j++, cout << endl)
        {
            cout << "[*]Dati partecipante " << i*col_mat_partecipanti + j + 1 << ":" << endl;
            cout << "[NOME]--->" << Partecipanti[i][j].nome << endl;
            switch (Partecipanti[i][j].mute)
            {
            case 0:
                cout << "[MUTE]--->DISABILITATO" << endl;
                break;
            case 1:
                cout << "[MUTE]--->ATTIVO" << endl;
                break;
            }
            cout << "[QUALITA VIDEO]--->" << Partecipanti[i][j].video << endl;
        } 
    }
    
}

void evidenziazione_miglior_partecipante (Partecipante Riunione[][MAX_COL], int rig_mat_riunione, int col_mat_riunione) {
    //DICHIARAZIONI VARIABILI UTILI
    float video_miglior_partecipante = 0.0;
    int rig_miglior_partecipante = 0, col_miglior_partecipante = 0;
    Partecipante temp;

    //RICERCA PRIMO PARTECIPANTE MAGGIOR QUALITA E DEVIDENZIAZIONE ALTRI PARTECIPANTI
    for (int i = 0; i < rig_mat_riunione; i++)
    {
        for (int j = 0; j < col_mat_riunione; j++)
        {
            if (Riunione[i][j].video > video_miglior_partecipante)
            {
                video_miglior_partecipante = Riunione[i][j].video;
                rig_miglior_partecipante = i;
                col_miglior_partecipante = j;
            }
            Riunione[i][j].mute = true;
            if (Riunione[i][j].nome[0] >= 65 && Riunione[i][j].nome[0] <= 90)
            {
                Riunione[i][j].nome[0] += 32;
            }
        }
    }

    //SPOSTAMENTO IN PRIMA POSIZIONE ED EVIDENZIAZIONE DEL PRIMO MIGLIOR PARTECIPANTE
    temp = Riunione[rig_miglior_partecipante][col_miglior_partecipante];
    Riunione[rig_miglior_partecipante][col_miglior_partecipante] = Riunione[0][0];
    Riunione[0][0] = temp;
    Riunione[0][0].mute = false;
    if (Riunione[0][0].nome[0] >= 97 && Riunione[0][0].nome[0] <= 122)
    {
        Riunione[0][0].nome[0] -= 32;
    }
    
}

void creazione_chat (const Partecipante Riunione[][MAX_COL], int rig_mat_riunione, int col_mat_riunione, Partecipante Chat[], int& numero_partecipanti_chat) {
    //DICHIARAZIONI VARIABILI UTILI
    char iniziali_partecipanti_chat[4];
    int pos_max = 0;
    float video_max = 0.0;
    Partecipante temp;

    //INSERIMENTO DA TASTIERA INIZIALI DEI PARTECIPANTI ALLA CHAT DA CREARE
    cout << "[INSERT]Inserisci le iniziali dei nomi dei partecipanti alla riunione da aggiungere alla chat: "; cin >> iniziali_partecipanti_chat;

    //RICERCA PARTECIPANTI ALLA RIUNIONE DALLE INIZIALI INDICATE ED AGGIUNTA ALLA CHAT
    for (int i = 0; i < rig_mat_riunione; i++)
    {
        for (int j = 0; j < col_mat_riunione; j++)
        {
            if ( strncmp(Riunione[i][j].nome, iniziali_partecipanti_chat, 3) == 0)
            {
                Chat[numero_partecipanti_chat] = Riunione[i][j];
                numero_partecipanti_chat++;
            }
        }
    }

    if (numero_partecipanti_chat != 0)
    {
        //ORDINAMENTO VETTORE CHAT
        for (int i = 0; i < numero_partecipanti_chat-1; i++)
        {
            pos_max = i;
            video_max = Chat[i].video;
            for (int j = i+1; j < numero_partecipanti_chat; j++)
            {
                if (Chat[j].video > video_max)
                {
                    video_max = Chat[j].video;
                    pos_max = j;
                }
            }
            temp = Chat[pos_max];
            Chat[pos_max] = Chat[i];
            Chat[i] = temp;
        }

        //STAMPA VETTORE CHAT
        cout << "[INFO]Chat creata con successo! Elenco partecipanti alla chat:" << endl;
        for (int i = 0; i < numero_partecipanti_chat; i++, cout << endl)
        {
            cout << "[*]Dati partecipante " << i + 1 << " della chat:" << endl;
            cout << "[NOME]--->" << Chat[i].nome << endl;
            switch (Chat[i].mute)
            {
            case 0:
                cout << "[MUTE]--->DISABILITATO" << endl;
                break;
            case 1:
                cout << "[MUTE]--->ATTIVO" << endl;
                break;
            }
            cout << "[QUALITA VIDEO]--->" << Chat[i].video << endl;
        }
        
    } else {
        cout << "[WARNING]Nessun partecipante alla riunione dalle iniziali indicate. Impossibile creare una chat." << endl;
    }

}
#define MAX_STRING 16
#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
enum Polarizzazione {orizzontale, verticale};
struct Ripetitore {
    float longitudine;
    float latitudine;
    Polarizzazione pol;
    Stringa operatore;
};
typedef Ripetitore* PRip;

//PROTOTIPI
void lettura_elenco_ripetitori(PRip&, int&);
void elenco_ripetitori(PRip, int);
void ricerca_ripetitori(PRip, int);
void eliminazione_ripetitori_orizzontali (PRip&, int&);

int main() {
    PRip Ripetitori = NULL;
    int numero_ripetitori = 0;

    //CHIAMATE FUNZIONI
    lettura_elenco_ripetitori(Ripetitori, numero_ripetitori);
    cout << "[INFO]Elenco dei ripetitori attivi:" << endl;
    elenco_ripetitori(Ripetitori, numero_ripetitori);

    ricerca_ripetitori(Ripetitori, numero_ripetitori);

    eliminazione_ripetitori_orizzontali(Ripetitori, numero_ripetitori);
    cout << "[INFO]Elenco dei ripetitori verticali attivi:" << endl;
    elenco_ripetitori(Ripetitori, numero_ripetitori);

}

void lettura_elenco_ripetitori(PRip& Ripetitori, int& numero_ripetitori) {
    //DICHIARAZIONI VARIABILI UTILI
    float longitudine = 0.0;
    float latitudine = 0.0;
    int pol = 0;
    Stringa operatore = "";
    ifstream file;

    //CONTEGGIO RIPETITORI
    file.open("ripetitori.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile aprire l'elenco dei ripetitori attivi. Contattare l'assistenza." << endl;
        exit(1);
    }
    file >> numero_ripetitori;
    numero_ripetitori *= 2;
    if (numero_ripetitori > 30 || numero_ripetitori <= 0)
    {
        cout << "[ERRORE]Numero dei ripetitori attivi non gestibile. Contattare l'assistenza per un upgrade del software alla versione PRO." << endl;
        exit(1);
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI RIPETITORI
    Ripetitori = new Ripetitore[numero_ripetitori];
    if (Ripetitori == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contatatre l'assistenza." << endl;
        exit(1);
    }
    for (int i = 0; i < numero_ripetitori; i++)
    {
        file >> latitudine;
        (*(Ripetitori + i)).latitudine = latitudine;
        file >> longitudine;
        (*(Ripetitori + i)).longitudine = longitudine;
        file >> pol;
        switch (pol)
        {
        case 1:
            (*(Ripetitori + i)).pol = verticale;
            break;
        case 0:
            (*(Ripetitori + i)).pol = orizzontale;
            break;    
        }
        file >> operatore;
        strcpy((*(Ripetitori + i)).operatore, operatore);
    }  
    file.close();
    
}

void elenco_ripetitori(PRip Ripetitori, int numero_ripetitori) {
    //STAMPA VETTORE DI RIPETITORI
    for (int i = 0; i < numero_ripetitori; i++, cout << endl)
    {
        cout << "[*]Scheda Tecnica Ripetitore " << i+1 << ":" << endl;
        cout << "[LAT]--->" << (*(Ripetitori + i)).latitudine << endl;
        cout << "[LONG]--->" << (*(Ripetitori + i)).longitudine << endl;
        switch ((*(Ripetitori + i)).pol)
        {
        case verticale:
            cout << "[POLARIZZAZIONE]--->Verticale" << endl;
            break;
        case orizzontale:
            cout << "[POLARIZZAZIONE]--->Orizzontale" << endl;
            break;
        }
        cout << "[OPERATORE]--->" << (*(Ripetitori + i)).operatore << endl;
    }
    
}

void ricerca_ripetitori(PRip Ripetitori, int numero_ripetitori) {
    //DICHIARAZIONI VARIABILI AUSILIARIE
    float lat_utente = 0.0, long_utente = 0.0, min_distanza_utente_ripetitore = 99999.99999;
    int pos_ripetitore_vicino = -1, distanza_utente_ripetitore = 0;
    Stringa operatore_ricercato = "";

    //INSERIMENTO COORDINATE UTENTE ED OPERATORE RICERCATO
    cout << "[INSERT LAT]Inserimento latitudine dell'utente: "; cin >> lat_utente;
    cout << "[INSERT LONG]Inserimento longitudine dell'utente: "; cin >> long_utente;
    cout << "[INSERT OPERATORE]Inserimento operatore ricercato: "; cin >> operatore_ricercato;

    //RICERCA RIPETITORE A DISTANZA MINIMA DELL'OPERATORE INDICATO
    for (int i = 0; i < numero_ripetitori; i++)
    {
        if (strcmp((*(Ripetitori + i)).operatore, operatore_ricercato) == 0)
        {
            distanza_utente_ripetitore = ( ((*(Ripetitori + i)).latitudine - lat_utente)*((*(Ripetitori + i)).latitudine - lat_utente) + ((*(Ripetitori + i)).longitudine - long_utente)*((*(Ripetitori + i)).longitudine - long_utente) );
            if (distanza_utente_ripetitore < min_distanza_utente_ripetitore)
            {
                min_distanza_utente_ripetitore = distanza_utente_ripetitore;
                pos_ripetitore_vicino = i;
            }
        }       
    }

    //STAMPA A VIDEO CARATTERISTICHE RIPETITORE A MINORE DISTANZA
    if (pos_ripetitore_vicino == -1)
    {
        cout << "[WARNING]Nessun ripetitore disponibile dell'operatore " << operatore_ricercato << "." << endl;
        cout << endl;
    } else {
        cout << "[*]Scheda tecnica del ripetitore " << operatore_ricercato << " a minore distanza dall'utente:" << endl;
        cout << "[LAT]--->" << (*(Ripetitori + pos_ripetitore_vicino)).latitudine << endl;
        cout << "[LONG]--->" << (*(Ripetitori + pos_ripetitore_vicino)).longitudine << endl;
        switch ((*(Ripetitori + pos_ripetitore_vicino)).pol)
        {
        case verticale:
            cout << "[POLARIZZAZIONE]--->Verticale" << endl;
            break;
        case orizzontale:
            cout << "[POLARIZZAZIONE]--->Orizzontale" << endl;
            break;
        }
        cout << "[OPERATORE]--->" << (*(Ripetitori + pos_ripetitore_vicino)).operatore << endl;
        cout << endl;
    }
        
}

void eliminazione_ripetitori_orizzontali (PRip& Ripetitori, int& numero_ripetitori) {
    //ELIMINAZIONE RIPETITORI ORIZZONTALI
    for (int i = 0; i < numero_ripetitori; i++)
    {
        if ((*(Ripetitori + i)).pol == orizzontale)
        {
            numero_ripetitori--;
            for (int j = i; j < numero_ripetitori; j++)
            {
                *(Ripetitori + j) = *( Ripetitori + (j + 1) );
            }
            i--;
        }
    }
    
}
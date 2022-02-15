#include <iostream>
#include <fstream>
#define MAX_STRING 16
using namespace std;

//TIPI ED ALIS UTILI
typedef char Stringa[MAX_STRING];
enum Tipo {lavastoviglie = 1, lavasciuga = 2, lavatrice = 3, asciugatrice = 4};
struct Elettrodomestico {
    float prezzo;
    Tipo tipologia;
    Stringa marca;
    bool disponibilita;
};
typedef Elettrodomestico* PElettrodomestico;

//PROTOTIPI
void aggiornamento_magazzino (PElettrodomestico&, int&, float&, float&, float&, float&);
void display_prezzi(float, float, float, float);
void resoconto (PElettrodomestico, int);
void ricerca_elettrodomestici (PElettrodomestico, PElettrodomestico&, int, int&);

int main() {
    PElettrodomestico Magazzino = NULL, Risultati_Ricerca = NULL;
    int riempimento_magazzino = 0, riempimento_risultati_ricerca = 0;
    float prezzo_lavastoviglie = 0, prezzo_lavasciughe = 0, prezzo_lavatrici = 0, prezzo_asciugatrici = 0;

    aggiornamento_magazzino(Magazzino, riempimento_magazzino, prezzo_lavastoviglie, prezzo_lavasciughe, prezzo_lavatrici, prezzo_asciugatrici);
    if (riempimento_magazzino != 0)
    {
    cout << "[INFO]RESOCONTO MAGAZZINO:" << endl << endl;
    resoconto(Magazzino, riempimento_magazzino);
    cout << "[INFO]PREZZI COMPLESSIVI PER TIPOLOGIE:" << endl << endl;
    display_prezzi(prezzo_lavastoviglie, prezzo_asciugatrici, prezzo_lavatrici, prezzo_asciugatrici);
    }

    ricerca_elettrodomestici(Magazzino, Risultati_Ricerca, riempimento_magazzino, riempimento_risultati_ricerca);
    if (riempimento_risultati_ricerca != 0)
    {
    cout << "[INFO]RISULTATI RICERCA:" << endl << endl;
    resoconto(Risultati_Ricerca, riempimento_risultati_ricerca);
    }
    
}

void aggiornamento_magazzino (PElettrodomestico& Magazzino, int& riempimento_magazzino, float& prezzo_lavastoviglie, float& prezzo_lavasciughe, float& prezzo_lavatrici, float& prezzo_asciugatrici) {
    //DICHIARAZIONI VARIABILI AUSILIARIE
    float prezzo; char tipologia; Stringa marca; bool disponibilita;
    ifstream file;
    
    //CONTA ELEMENTI MAGAZZINO
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERROR]Impossibile aprire il file del magazzino." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        riempimento_magazzino++;
        file.ignore(100, '\n');
    }
    file.close();

    //AGGIUNTA ELETTRODOMESTICI A RESOCONTO MAGAZZINO
    Magazzino = new Elettrodomestico[riempimento_magazzino];
    if (Magazzino == NULL)
    {
        cout << "[ERROR]Memoria insufficiente per aggiungere elettrodomestici al magazzino.";
        exit(1);
    }
    riempimento_magazzino = 0;
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERROR]Impossibile aprire il file del magazzino." << endl;
        exit(1);
    }
    while (!file.eof())
    {
  
        file >> prezzo;
        (*(Magazzino + riempimento_magazzino)).prezzo = prezzo;

        file >> tipologia;
        switch (tipologia)
        {
        case '1':
            (*(Magazzino + riempimento_magazzino)).tipologia = lavastoviglie;
            prezzo_lavastoviglie += prezzo;
            break;
        case '2':
            (*(Magazzino + riempimento_magazzino)).tipologia = lavasciuga;
            prezzo_lavasciughe += prezzo;
            break;
        case '3':
            (*(Magazzino + riempimento_magazzino)).tipologia = lavatrice;
            prezzo_lavatrici += prezzo;
            break;
        case '4':
            (*(Magazzino + riempimento_magazzino)).tipologia = asciugatrice;
            prezzo_asciugatrici += prezzo;
            break;
        default:
            break;
        }

        file >> marca;
        for (int i = 0; i < MAX_STRING; i++)
        {
            (*(Magazzino + riempimento_magazzino)).marca[i] = marca[i];
        }

        file >> disponibilita;
        (*(Magazzino + riempimento_magazzino)).disponibilita = disponibilita;
        
        riempimento_magazzino++;
    }
    file.close();
}

void display_prezzi(float prezzo_lavastoviglie, float prezzo_lavasciughe, float prezzo_lavatrici, float prezzo_asciugatrici) {
    //CREAZIONE ARRAY DI PREZZI
    float* Prezzi_Tipologie = new float[4];
    *(Prezzi_Tipologie + 0) = prezzo_lavastoviglie;
    *(Prezzi_Tipologie + 1) = prezzo_lavasciughe;
    *(Prezzi_Tipologie + 2) = prezzo_lavatrici;
    *(Prezzi_Tipologie + 3) = prezzo_asciugatrici;

    //ORDINAMENTO ARRAY DI PREZZI
    for (int i = 0; i < 3; i++)
    {
        float temp;
        int pos_max = i;
        for (int j = i+1; j < 4; j++)
        {
            if (*(Prezzi_Tipologie + j) > *(Prezzi_Tipologie + pos_max))
            {
                pos_max = j;
            }
        }
        temp = *(Prezzi_Tipologie + pos_max);
        *(Prezzi_Tipologie + pos_max) = *(Prezzi_Tipologie + i);
        *(Prezzi_Tipologie + i) = temp;
    }

    //DISPLAY PREZZI
    for (int i = 0; i < 4; i++)
    {
        if (*(Prezzi_Tipologie + i) == prezzo_lavastoviglie)
        {
            cout << "[LAVASTOVIGLIE] Prezzo Totale Articoli: " << *(Prezzi_Tipologie + i) << endl;
            continue;
        }
        if (*(Prezzi_Tipologie + i) == prezzo_lavasciughe)
        {
            cout << "[LAVASCIUGHE] Prezzo Totale Articoli: " << *(Prezzi_Tipologie + i) << endl;
            continue;
        }
        if (*(Prezzi_Tipologie + i) == prezzo_lavatrici)
        {
            cout << "[LAVATRICI] Prezzo Totale Articoli: " << *(Prezzi_Tipologie + i) << endl;
            continue;
        }
        if (*(Prezzi_Tipologie + i) == prezzo_asciugatrici)
        {
            cout << "[ASCIUGATRICI] Prezzo Totale Articoli: " << *(Prezzi_Tipologie + i) << endl;
            continue;
        }    
    }
}

void resoconto (PElettrodomestico Elettrodomestici, int numero_elettrodomestici) {
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        switch ((*(Elettrodomestici + i)).tipologia)
        {
        case 1:
            cout << "[TIPOLOGIA]---> Lavastoviglie" << endl;
            break;
        case 2:
            cout << "[TIPOLOGIA]---> Lavasciuga" << endl;
            break;
        case 3:
            cout << "[TIPOLOGIA]---> Lavatrice" << endl;
            break;
        case 4:
            cout << "[TIPOLOGIA]---> Asciugatrice" << endl;
            break;
        default:
            break;
        }
        cout << "[PREZZO]---> " << (*(Elettrodomestici + i)).prezzo << endl; 
        cout << "[MARCA]---> " << (*(Elettrodomestici + i)).marca << endl;
        switch ((*(Elettrodomestici + i)).disponibilita)
        {
        case 1:
            cout << "[DISPONIBILITA]---> SI" << endl << endl; 
            break;
        case 0:
            cout << "[DISPONIBILITA]---> NO" << endl << endl; 
            break;
        }
    }
}

void ricerca_elettrodomestici (PElettrodomestico Magazzino, PElettrodomestico& Risultati_Ricerca, int riempimento_magazzino, int& riempimento_ricerca) {
    //INSERIMENTO PREZZO
    float prezzo_inserito = 0;
    do
    {
        cout << "[ACTION]Inserisci prezzo degli elettrodomestici da ricercare: ";
        cin >> prezzo_inserito;
        if (prezzo_inserito <= 0)
        {
            cout << "[WARNING]Prezzo inserito non accettabile. Riprovare." << endl;
            prezzo_inserito = 0;
        }
         
    } while (prezzo_inserito <= 0);
    
    //CALCOLO NUMERO ELETTRODMESTICI TROVATI
    for (int i = 0; i < riempimento_magazzino; i++)
    {
        if ((*(Magazzino + i)).prezzo == prezzo_inserito)
        {
            riempimento_ricerca++;
        }
    }

    //CREAZIONE LISTA DEGLI ELETTRODOMESTICI TROVATI
    if (riempimento_ricerca == 0)
    {
        cout << "[WARNING]Nessun elettrodomestico trovato con il prezzo indicato." << endl;;
    } else
    {
        Risultati_Ricerca = new Elettrodomestico[riempimento_ricerca];
        riempimento_ricerca = 0;
        if (Risultati_Ricerca == NULL)
        {
            cout << "[ERROR]Memoria insufficiente per effettuare una ricerca.";
            exit(1);
        }
        for (int i = 0; i < riempimento_magazzino; i++)
        {
            if ((*(Magazzino + i)).prezzo == prezzo_inserito)
            {
                (*(Risultati_Ricerca + riempimento_ricerca)).prezzo = (*(Magazzino + i)).prezzo;
                (*(Risultati_Ricerca + riempimento_ricerca)).tipologia = (*(Magazzino + i)).tipologia;
                for (int j = 0; j < MAX_STRING; j++)
                {
                    (*(Risultati_Ricerca + riempimento_ricerca)).marca[j] = (*(Magazzino + i)).marca[j];
                }
                (*(Risultati_Ricerca + riempimento_ricerca)).disponibilita = (*(Magazzino + i)).disponibilita;
                riempimento_ricerca++;
            }
        }
    }

    //ORDINAMENTO ALFABETICO LISTA DEGLI ELEMENTI TROVATI
    for (int i = 0; i < riempimento_ricerca - 1; i++)
    {
        Elettrodomestico tmp;
        int pos_scambio = i;
        for (int j = i+1; j < riempimento_ricerca; j++)
        {
            if ( strcmp((*(Risultati_Ricerca + j)).marca, (*(Risultati_Ricerca + pos_scambio)).marca) < 0)
            {
                pos_scambio = j;
            }
        }
        tmp = *(Risultati_Ricerca + pos_scambio);
        *(Risultati_Ricerca + pos_scambio) = *(Risultati_Ricerca + i);
        *(Risultati_Ricerca + i) = tmp;
    }
}
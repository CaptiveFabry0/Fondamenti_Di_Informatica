#include <iostream>
#include <fstream>
#define MAX_STRINGA 11
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRINGA];
struct Pietanza {
    Stringa nome;
    float prezzo;
};
typedef Pietanza* Ppietanza;

//PROTOTIPI
void lettura_pietanze(Ppietanza&, int&);
void elenco_pietanze(Ppietanza, int);
void ricerca_pietanze (Ppietanza, int);
void evidenziazione_pietanze_costose (Ppietanza&, int);

int main() {
    Ppietanza Pietanze = NULL;
    int numero_pietanze = 0;

    lettura_pietanze(Pietanze, numero_pietanze);
    cout << "[INFO]Elenco Pietanze Disponibili:" << endl;
    elenco_pietanze(Pietanze, numero_pietanze);
    ricerca_pietanze(Pietanze, numero_pietanze);
    evidenziazione_pietanze_costose(Pietanze, numero_pietanze);
    cout << "[INFO]Elenco Pietanze Disponibili (Pietanze costose evidenziate):" << endl;
    elenco_pietanze(Pietanze, numero_pietanze);
}

void lettura_pietanze(Ppietanza& Pietanze, int& numero_pietanze) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //CONTEGGIO NUMERO PIETANZE
    file.open("pietanze.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Elenco delle pietanze non disponibile. Contattare personalmente la cucina." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_pietanze++;
        file.ignore(100, '\n');
    }
    file.close();

    //CREAZIONE VETTORE DI PIETANZE
    Pietanze = new Pietanza[numero_pietanze];
    if (Pietanze == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare personalmente la cucina." << endl;
        exit(1);
    }
    numero_pietanze = 0;
    file.open("pietanze.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Elenco delle pietanze non disponibile. Contattare personalmente la cucina." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> (*(Pietanze + numero_pietanze)).nome;
        file >> (*(Pietanze + numero_pietanze)).prezzo;
        numero_pietanze++;
    }
    file.close();

}

void elenco_pietanze(Ppietanza Pietanze, int numero_pietanze) {
    //STAMPA A VIDEO VETTORE DI PIETANZE
    for (int i = 0; i < numero_pietanze; i++, cout << endl)
    {
        cout << "[*]PIETANZA " << i+1 << ":" << endl;
        cout << "[NOME]--->" << (*(Pietanze + i)).nome << endl;
        cout << "[PREZZO]--->" << (*(Pietanze + i)).prezzo << endl;
    }
}

void ricerca_pietanze (Ppietanza Pietanze, int numero_pietanze) {
    //DICHIARAZIONI VARIABILI UTILI
    char carattere_inserito = '\0';
    int numero_pietanze_ricercate = 0;
    int posizioni_pietanze_ricercate[2] = {0};

    //INSERIMENTO DA TASTIERA DELL'INIZIALE DA RICERCARE
    do
    {
        cout << "[INSERT]Inserisci l'iniziale (minuscola) delle pietanze da ricercare: ";
        cin >> carattere_inserito;
        if (carattere_inserito < 97 || carattere_inserito > 122)
        {
            cout << "[WARNING]Carattere inserito non valido. Riprovare." << endl;
        }
    } while ( carattere_inserito < 97 || carattere_inserito > 122 );

    //CONTEGGIO NUMERO PIETANZE IL CUI NOME INIZI CON IL CARATTERE INDICATO
    for (int i = 0; i < numero_pietanze; i++)
    {
        if ((*(Pietanze + i)).nome[0] == carattere_inserito && numero_pietanze_ricercate != 2)
        {
            *(posizioni_pietanze_ricercate + numero_pietanze_ricercate) = i;
            numero_pietanze_ricercate++;
        }
    }

    //STAMPA PIETANZE RICERCATE
    switch (numero_pietanze_ricercate)
    {
    case 0:
        cout << "[WARNING]Nessuna pietanza trovata con l'iniziale indicata. Dovrai adattarti al menu..." << endl;
        break;

    case 1:
        cout << "[WARNING]Solo una pietanza trovata nell'elenco con l'iniziale indicata. Speriamo ti basti..." << endl;
        cout << "[NOME]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate))).nome << endl;
        cout << "[PREZZO]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate))).prezzo << endl;
        break;
    
    default:
        cout << "[INFO]Prime due pietanze disponibili con l'iniziale indicata. Perchè solo le prime due? Il Boss mi ha detto di fare così..." << endl;
        cout << "[NOME]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate))).nome << endl;
        cout << "[PREZZO]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate))).prezzo << endl;
        cout << "[NOME]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate + 1))).nome << endl;
        cout << "[PREZZO]--->" << (*(Pietanze + *(posizioni_pietanze_ricercate + 1))).prezzo << endl;
        break;
    }
    
}

void evidenziazione_pietanze_costose (Ppietanza& Pietanze, int numero_pietanze) {
    //DICHIARAZIONI VARIABILI UTILI
    float prezzo_medio = 0;

    //DETERMINAZIONE PREZZO MEDIO DELLE PIETANZE
    for (int i = 0; i < numero_pietanze; i++)
    {
        prezzo_medio += (*(Pietanze + i)).prezzo;
    }
    prezzo_medio /= numero_pietanze;

    //EVIDENZIAZIONE PIETANZE COSTOSE
    for (int i = 0; i < numero_pietanze; i++)
    {
        if ((*(Pietanze + i)).prezzo > prezzo_medio)
        {
            (*(Pietanze + i)).nome[0] -= 32;
        }
    }

}
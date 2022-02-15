#include <iostream>
#include <fstream>
#define MAX_STRING 16
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
struct Copia {
    Stringa titolo;
    float prezzo;
    int pagine;
};
typedef Copia* PCop;

//PROTOTIPI
void lettura_copie_libreria(PCop&, int&);
void elenco_copie (PCop, int);
void ricerca_copie_libro(PCop, int);
void creazione_carrello (PCop, int, PCop&, int&);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    PCop Copie_Libreria = NULL, Copie_Carrello = NULL;
    int numero_copie_libreria = 0, numero_copie_carrello = 0;

    //CHIAMATE FUNZIONI
    lettura_copie_libreria(Copie_Libreria, numero_copie_libreria);
    cout << "[INFO]Elenco delle copie disponibili in libreria:" << endl;
    elenco_copie(Copie_Libreria, numero_copie_libreria);

    ricerca_copie_libro(Copie_Libreria, numero_copie_libreria);

    creazione_carrello(Copie_Libreria, numero_copie_libreria, Copie_Carrello, numero_copie_carrello);
    cout << "[INFO]Elenco delle copie nel carrello standard (MAX 100 EURO):" << endl;
    elenco_copie(Copie_Carrello, numero_copie_carrello);
}

void lettura_copie_libreria(PCop& Copie_Libreria, int& numero_copie_libreria) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //CONTEGGIO NUMERO COPIE
    file.open("copie.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere il file contenente le copie dei libri disponibili. Terminazione del programma." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_copie_libreria++;
        file.ignore(100, '\n');
    }
    file.close();

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI COPIE
    Copie_Libreria = new Copia[numero_copie_libreria];
    if (Copie_Libreria == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
    }
    numero_copie_libreria = 0;
    file.open("copie.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere il file contenente le copie dei libri disponibili. Terminazione del programma." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> (*(Copie_Libreria + numero_copie_libreria)).titolo;
        file >> (*(Copie_Libreria + numero_copie_libreria)).prezzo;
        file >> (*(Copie_Libreria + numero_copie_libreria)).pagine;
        numero_copie_libreria++;
    }
    file.close();
    
}

void elenco_copie (PCop Copie, int numero_copie) {
    //STAMPA VETTORE
    for (int i = 0; i < numero_copie; i++, cout << endl)
    {
        cout << "[*]Copia " << i+1 << endl;
        cout << "[TITOLO LIBRO]--->" << (*(Copie + i)).titolo << endl;
        cout << "[PREZZO]--->" << (*(Copie + i)).prezzo << endl;
        cout << "[PAGINE]--->" << (*(Copie + i)).pagine << endl;
    }

}

void ricerca_copie_libro(PCop Copie_Libreria, int numero_copie_libreria) {
    //DICHIARAZIONI VARIABILI UTILI
    Stringa titolo_ricercato = "DEFAULT";
    float prezzo_minimo = 9999.9999;
    int numero_copie_prezzo_minimo = 0;

    //INSERIMENTO DA TASTIERA TITOLO DA RICERCARE
    cout << "[INSERT]inserisci il titolo del libro da ricercare(MAX 15 CARATTERI): ";
    cin.get(titolo_ricercato, MAX_STRING);

    //CONTEGGIO COPIE DAL TITOLO SPECIFICATO
    for (int i = 0; i < numero_copie_libreria; i++)
    {
        if (strcmp((*(Copie_Libreria + i)).titolo, titolo_ricercato) == 0)
        {
            if ((*(Copie_Libreria + i)).prezzo == prezzo_minimo)
            {
                numero_copie_prezzo_minimo++;
            }
            if ((*(Copie_Libreria + i)).prezzo < prezzo_minimo)
            {
                prezzo_minimo = (*(Copie_Libreria + i)).prezzo;
                numero_copie_prezzo_minimo = 1;
            }
        }
    }

    //STAMPA A VIDEO DEI RISULTATI DELLA RICERCA
    if (numero_copie_prezzo_minimo == 0) //NESSUNA COPIA DAL TITOLO RICERCATO PRESENTE NELLA LIBRERIA
    {
        cout << "[WARNING]Nessuna libro dal titolo indicato presente sui nostri scaffali..." << endl;
    } else {
        cout << "[SEARCH RESULT]Sono presenti in libreria " << numero_copie_prezzo_minimo << " copie dal prezzo minimo di " << prezzo_minimo << " EURO" << endl;
    }
    
}

void creazione_carrello (PCop Copie_Libreria, int numero_copie_libreria, PCop& Copie_Carrello, int& numero_copie_carrello) {
    //DICHIARAZIONI VARIABILI UTILI
    float costo_carrello = 0.0;
    bool costo_eccessivo = false;

    //CONTEGGIO ELELEMENTI DEL CARRELLO
    for (int i = 0; i < numero_copie_libreria && costo_eccessivo == false; i++)
    {
        costo_carrello += (*(Copie_Libreria + i)).prezzo;
        if (costo_carrello > 100)
        {
            costo_eccessivo = true;
        } else {
            numero_copie_carrello++;
        }    
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DELLE COPIE NEL CARRELLO
    Copie_Carrello = new Copia[numero_copie_carrello];
    if (Copie_Carrello == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
    }
    for (int i = 0; i < numero_copie_carrello; i++)
    {
        *(Copie_Carrello + i) = *(Copie_Libreria + i);
    }

}
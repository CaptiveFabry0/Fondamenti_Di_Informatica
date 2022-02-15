#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[16];
struct Libro {
    Stringa titolo;
    float prezzo;
    int pagine;
    int copie;
};
typedef Libro* PLibro;

//PROTOTIPI
void riempimento_libreria (PLibro&, int&);
void elenco_libri(PLibro, int);
void riempimento_carrello_non_disponibili (PLibro, int, PLibro&, int&, float&);
void ricerca_libri(PLibro, int, PLibro&, int&);

int main() {
    PLibro Libri = NULL, Carrello_Non_Disponibili = NULL, Libri_Ricercati = NULL;
    int numero_libri = 0, numero_libri_non_disponibili = 0, numero_libri_ricercati = 0;
    float costo_carrello_non_disponibili = 0;

    riempimento_libreria(Libri, numero_libri);
    if (numero_libri != 0)
    {
        cout << "[INFO]RIEPILOGO LIBRI:" << endl;
        elenco_libri(Libri, numero_libri);

        riempimento_carrello_non_disponibili(Libri, numero_libri, Carrello_Non_Disponibili, numero_libri_non_disponibili, costo_carrello_non_disponibili);
        if (numero_libri_non_disponibili != 0)
        {
            cout << "[CARRELLO]RIEPILOGO LIBRI NEL CARRELLO:" << endl;
            elenco_libri(Carrello_Non_Disponibili, numero_libri_non_disponibili);
            cout << "[CARRELLO]COSTO PRODOTTI NEL CARRELLO(x2):" << costo_carrello_non_disponibili << "$" << endl;
        }

        ricerca_libri(Libri, numero_libri, Libri_Ricercati, numero_libri_ricercati);
        if (numero_libri_ricercati != 0)
        {
            cout << "[RICERCA]RISULTATI RICERCA:" << endl;
            elenco_libri(Libri_Ricercati, numero_libri_ricercati);
        }
    }
    
}

void riempimento_libreria (PLibro& Libri, int& numero_libri) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //LETTURA DA FILE
    file.open("copie.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere l'elenco dei libri. Contattare l'assistenza." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_libri++;
        file.ignore(100, '/n');
    }
    file.close();

    //RIEMPIMENTO LIBRERIA
    Libri = new Libro[numero_libri];
    numero_libri = 0;
    if (Libri == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per la corretta esecuzione del programma. Contattare l'assistenza." << endl;
        exit(1);
    }
    file.open("copie.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere l'elenco dei libri. Contattare l'assistenza." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> (*(Libri + numero_libri)).titolo;
        file >> (*(Libri + numero_libri)).prezzo;
        file >> (*(Libri + numero_libri)).pagine;
        file >> (*(Libri + numero_libri)).copie;
        numero_libri++;
    }
    file.close();
    
}

void elenco_libri(PLibro Libri, int numero_libri) {
    //STAMPA VETTORE
    for (int i = 0; i < numero_libri; i++, cout << endl)
    {
        cout << "[TITOLO]--->" << (*(Libri + i)).titolo << endl;
        cout << "[PREZZO]--->" << (*(Libri + i)).prezzo << "$" << endl;
        cout << "[PAGINE]--->" << (*(Libri + i)).pagine << endl;
        cout << "[COPIE]--->" << (*(Libri + i)).copie << endl;
    }
}

void riempimento_carrello_non_disponibili (PLibro Libri, int numero_libri, PLibro& Carrello_Non_Disponibili, int& numero_libri_non_disponibili, float& costo_carrello_non_disponibili) {
    //CONTEGGIO LIBRI NON DISPONIBILI
    for (int i = 0; i < numero_libri; i++)
    {
        if ((*(Libri + i)).copie == 0)
        {
            numero_libri_non_disponibili++;
        }
    }

    //ALLOCAZIONE E RIEMPIMENTO CARRELLO DI LIBRI NON DISPONIBILI
    if (numero_libri_non_disponibili == 0)
    {
        cout << "[FAILURE]Nessun libro non disponibile da acquistare. Goditi la lettura!" << endl;
    } else
    {
        Carrello_Non_Disponibili = new Libro[numero_libri_non_disponibili];
        numero_libri_non_disponibili = 0;
        if (Carrello_Non_Disponibili == NULL)
        {
            cout << "[ERRORE]Memoria insufficiente per la corretta esecuzione del programma. Contattare l'assistenza." << endl;
            exit(1);
        }
        for (int i = 0; i < numero_libri; i++)
        {
            if ((*(Libri + i)).copie == 0)
            {
                *(Carrello_Non_Disponibili + numero_libri_non_disponibili) = *(Libri + i);
                numero_libri_non_disponibili++;
                costo_carrello_non_disponibili += ((*(Libri + i)).prezzo)*2;
            }
        }
    }
    
}

void ricerca_libri(PLibro Libri, int numero_libri, PLibro& Libri_Ricercati, int& numero_libri_ricercati) {
    //DICHIARAZIONI VARIABILI UTILI
    char carattere_ricercato = '\0';

    //INSERIMENTO CARATTERE
    do
    {
        cout << "[INSERT]Inserisci l'iniziale (minuscola) dei libri da ricercare: ";
        cin >> carattere_ricercato;
        if (carattere_ricercato=='\0' || carattere_ricercato<97 || carattere_ricercato>122)
        {
            cout << "[WARNING]Carattere inserito non valido. Riprovare." << endl;
            carattere_ricercato = '\0';
        }
    } while (carattere_ricercato=='\0' || carattere_ricercato<97 || carattere_ricercato>122);

    //CONTEGGIO LIBRI TROVATI
    for (int i = 0; i < numero_libri; i++)
    {
        if ((*(Libri + i)).titolo[0] == carattere_ricercato)
        {
            numero_libri_ricercati++;
        }
    }
    
    //ALLOCAZIONE VETTORE DI LIBRI TROVATI
    if (numero_libri_ricercati == 0)
    {
        cout << "[FAILURE]Nessun libro disponibile il cui titolo inizi con il carattere indicato." << endl;
    } else
    {
        Libri_Ricercati = new Libro[numero_libri_ricercati];
        if (Libri_Ricercati == NULL)
        {
            cout << "[ERRORE]Memoria insufficiente per la corretta esecuzione del programma. Contattare l'assistenza." << endl;
            exit(1);
        }
        numero_libri_ricercati = 0;
        for (int i = 0; i < numero_libri; i++)
        {
            if ((*(Libri + i)).titolo[0] == carattere_ricercato)
            {
                *(Libri_Ricercati + numero_libri_ricercati) = *(Libri + i);
                numero_libri_ricercati++;
            }
        }
    }
    
}
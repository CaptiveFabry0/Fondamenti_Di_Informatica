#define MAX_STRING 16
#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
enum Tipologia {lavastoviglie, lavasciuga, asciugatrice, lavatrice};
struct Elettrodomestico {
    Stringa nome;
    Tipologia tipo;
    float prezzo;
    bool disponibilita;
};
typedef Elettrodomestico* PElettr;

//PROTOTIPI
void lettura_inventario_magazzino(PElettr&, int&);
void riepilogo_elettrodomestici(PElettr, int);
void raggruppamento_elettrodomestici_disponibili(PElettr, int, PElettr&, int&, PElettr&, int&);
void ordinamento_elettrodomestici_prezzo(PElettr&, int);
void ricerca_elettrodomestici_prezzo_massimo(PElettr&, int);

int main() {
    //DICHIARAZIONI E VARIABILI UTILI
    PElettr Elettrodomestici = NULL, Elettrodomestici_disponibili = NULL, Elettrodomestici_esauriti = NULL;
    int numero_elettrodomestici = 0, numero_elettrodomestici_disponibili = 0, numero_elettrodomestici_esauriti = 0;

    //CHIAMATE FUNZIONI
    lettura_inventario_magazzino(Elettrodomestici, numero_elettrodomestici);
    cout << "[INFO]Elettrodmestici in magazzino:" << endl;
    riepilogo_elettrodomestici(Elettrodomestici, numero_elettrodomestici);

    raggruppamento_elettrodomestici_disponibili(Elettrodomestici, numero_elettrodomestici, Elettrodomestici_disponibili, numero_elettrodomestici_disponibili, Elettrodomestici_esauriti, numero_elettrodomestici_esauriti);
    ordinamento_elettrodomestici_prezzo(Elettrodomestici_disponibili, numero_elettrodomestici_disponibili);
    ordinamento_elettrodomestici_prezzo(Elettrodomestici_esauriti, numero_elettrodomestici_esauriti);
    cout << "[INFO]Elettrodomestici disponibili in magazzino:" << endl;
    riepilogo_elettrodomestici(Elettrodomestici_disponibili, numero_elettrodomestici_disponibili);
    cout << "[INFO]Elettrodomestici esauriti:" << endl;
    riepilogo_elettrodomestici(Elettrodomestici_esauriti, numero_elettrodomestici_esauriti);

    ricerca_elettrodomestici_prezzo_massimo(Elettrodomestici, numero_elettrodomestici);
    cout << "[INFO]Elettrodmestici in magazzino (PRODOTTI PIU COSTOSI DELLA TIPOLGIA INDICATA EVIDENZIATI CON INIZIALE MAIUSCOLA):" << endl;
    riepilogo_elettrodomestici(Elettrodomestici, numero_elettrodomestici);
}

void lettura_inventario_magazzino(PElettr& Elettrodomestici, int& numero_elettrodomestici) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;
    Stringa nome;
    int tipo;
    float prezzo;
    bool disponibilita;

    //CONTEGGIO ELETTRODOMESTICI NEL MAGAZZINO
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'inventario del magazzino. Contatatre l'assistenza." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_elettrodomestici++;
        file.ignore(100, '\n');
    }
    file.close();
    
    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI ELETTRODOMESTICI
    Elettrodomestici = new Elettrodomestico[numero_elettrodomestici];
    if (Elettrodomestici == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma. Contattare l'assistenza." << endl;
        exit(1);
    }
    numero_elettrodomestici = 0;
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'inventario del magazzino. Contatatre l'assistenza." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> nome;
        file >> tipo;
        file >> prezzo;
        file >> disponibilita;

        strcpy( (*(Elettrodomestici + numero_elettrodomestici)).nome, nome );
        switch (tipo)
        {
        case 0:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavastoviglie;
            break;
        case 1:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavasciuga;
            break;
        case 2:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = asciugatrice;
            break;
        case 3:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavatrice;
            break;
        }
        (*(Elettrodomestici + numero_elettrodomestici)).prezzo = prezzo;
        switch (disponibilita)
        {
        case 0:
            (*(Elettrodomestici + numero_elettrodomestici)).disponibilita = false;
            break;
        case 1:
            (*(Elettrodomestici + numero_elettrodomestici)).disponibilita = true;
            break;
        }

        numero_elettrodomestici++;
    }
    file.close();
    
}

void riepilogo_elettrodomestici(PElettr Elettrodomestici, int numero_elettrodomestici) {
    //STAMPA VETTORE DI ELETTRODOMESTICI
    for (int i = 0; i < numero_elettrodomestici; i++, cout << endl)
    {
        cout << "[*]Scheda tecnica elettrodomestico " << i+1 << ":" << endl;
        cout << "[NOME]--->" << (*(Elettrodomestici + i)).nome << endl;
        switch ((*(Elettrodomestici + i)).tipo)
        {
        case 0:
            cout << "[TIPOLOGIA]--->Lavastoviglie" << endl;
            break;
        case 1:
            cout << "[TIPOLOGIA]--->Lavasciuga" << endl;
            break;
        case 2:
            cout << "[TIPOLOGIA]--->Asciugatrice" << endl;
            break;
        case 3:
            cout << "[TIPOLOGIA]--->Lavatrice" << endl;
            break;
        }
        cout << "[PREZZO]--->" << (*(Elettrodomestici + i)).prezzo << "Euro" << endl;
        switch ((*(Elettrodomestici + i)).disponibilita)
        {
        case 1:
            cout << "[DISPONIBILITA]--->IMMEDIATA" << endl;
            break;
        case 0:
            cout << "[DISPONIBILITA]--->ESAURITO" << endl;
            break;
        }
    }
    
}

void raggruppamento_elettrodomestici_disponibili(PElettr Elettrodomestici, int numero_elettrodomestici, PElettr& Elettrodomestici_disponibili, int& numero_elettrodomestici_disponibili, PElettr& Elettrodomestici_esauriti, int& numero_elettrodomestici_esauriti) {
    //CONTEGGIO ELETTRDOMESTICI ESAURITI E DISPONIBILI
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        if ((*(Elettrodomestici + i)).disponibilita)
        {
            numero_elettrodomestici_disponibili++;
        } else {
            numero_elettrodomestici_esauriti++;
        }
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI ELETTRODOMESTICI DISPONIBILI ED ESAURITI
    Elettrodomestici_disponibili = new Elettrodomestico[numero_elettrodomestici_disponibili];
    Elettrodomestici_esauriti = new Elettrodomestico[numero_elettrodomestici_esauriti];
    numero_elettrodomestici_disponibili = 0;
    numero_elettrodomestici_esauriti = 0;
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        if ((*(Elettrodomestici + i)).disponibilita)
        {
            *(Elettrodomestici_disponibili + numero_elettrodomestici_disponibili) = *(Elettrodomestici + i);
            numero_elettrodomestici_disponibili++;
        } else {
            *(Elettrodomestici_esauriti + numero_elettrodomestici_esauriti) = *(Elettrodomestici + i);
            numero_elettrodomestici_esauriti++;
        }
    }

}

void ordinamento_elettrodomestici_prezzo(PElettr& Elettrodomestici, int numero_elettrodomestici) {
    //DICHIARAZIONI VARIABILI UTILI
    int pos_min = 0;
    float prezzo_min = 0.0;
    Elettrodomestico temp;

    //ORDINAMENTO VETTORE
    for (int i = 0; i < numero_elettrodomestici - 1; i++)
    {
        pos_min = i;
        prezzo_min = (*(Elettrodomestici + i)).prezzo;
        for (int j = i+1; j < numero_elettrodomestici; j++)
        {
            if ((*(Elettrodomestici + j)).prezzo < prezzo_min)
            {
                pos_min = j;
                prezzo_min = (*(Elettrodomestici + j)).prezzo;
            }
        }
        temp = *(Elettrodomestici + pos_min);
        *(Elettrodomestici + pos_min) = *(Elettrodomestici + i);
        *(Elettrodomestici + i) = temp;
    }
    
}

void ricerca_elettrodomestici_prezzo_massimo(PElettr& Elettrodomestici, int numero_elettrodomestici) {
    //DICHIARAZIONI VARAIBILI UTILI
    int tipo_ricercato = -1;
    float prezzo_max = 0.0;

    //INSERIMENTO TIPOLOGIA DA RICERCARE DA TASTIERA
    do
    {
        cout << "[INSERT]Inserisci la tipologia di cui ricercare gli elettrodomestici piu costosi:" << endl;
        cout << "[Lavastoviglie=0, Lavasciuga=1, Asciugatrice=2, Lavatrice=3]--->"; cin >> tipo_ricercato;
        if (tipo_ricercato != 0 && tipo_ricercato != 1 && tipo_ricercato != 2 && tipo_ricercato != 3)
        {
            cout << "[WARNING]Tipologia inserita non valida. Riprovare." << endl;
        }
    } while (tipo_ricercato != 0 && tipo_ricercato != 1 && tipo_ricercato != 2 && tipo_ricercato != 3);

    //DETERMINAZIONE PREZZO MAGGIORE DELLA TIPOLOGIA INDICATA
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        if ((*(Elettrodomestici + i)).tipo == tipo_ricercato && (*(Elettrodomestici + i)).prezzo > prezzo_max)
        {
            prezzo_max = (*(Elettrodomestici + i)).prezzo;
        }
    }

    //EVIDENZIAZIONE ELETTRODOMESTICI DELLA TIPOGIA INDICATA DAL PREZZO MASSIMO
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        if ((*(Elettrodomestici + i)).tipo == tipo_ricercato && (*(Elettrodomestici + i)).prezzo == prezzo_max)
        {
            (*(Elettrodomestici + i)).nome[0] -= 32;
        }
    }
    
}
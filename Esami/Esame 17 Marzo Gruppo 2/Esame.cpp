#define MAX_STRING 16
#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[MAX_STRING];
enum tipologia {lavatrice, asciugatrice, lavasciuga, lavastoviglie, LAVATRICE, ASCIUGATRICE, LAVASCIUGA, LAVASTOVIGLIE};
struct Elettrodomestico
{
    Stringa marca;
    tipologia tipo;
    float prezzo;
    bool disponibilita;
};
typedef Elettrodomestico* PElettr;

//PROTOTIPI
void lettura_inventario(PElettr&, int&);
void riepilogo_elettrodomestici (PElettr, int);
void separazione_tipolgie (PElettr, int, PElettr&, int&, PElettr&, int&, PElettr&, int&, PElettr&, int&);
void ordinamento_elettrodomestici_marca (PElettr&, int);
void evidenziazione_tipologie_elettrodomestici_economici_disponibili (PElettr&, int);

int main() {
    PElettr Elettrodomestici = NULL, Lavatrici = NULL, Asciugatrici = NULL, Lavasciughe = NULL, Lavastoviglie = NULL;
    int numero_elettrodomestici = 0, numero_lavatrici = 0, numero_asciugatrici = 0, numero_lavasciughe = 0, numero_lavastoviglie = 0;

    //CHIAMATE FUNZIONI
    //PUNTO 1-2
    lettura_inventario(Elettrodomestici, numero_elettrodomestici);
    cout << "[INFO]Elenco elettrodomestici in magazzino:" << endl;
    riepilogo_elettrodomestici(Elettrodomestici, numero_elettrodomestici);

    //PUNTO 3
    separazione_tipolgie(Elettrodomestici, numero_elettrodomestici, Lavatrici, numero_lavatrici, Asciugatrici, numero_asciugatrici, Lavasciughe, numero_lavasciughe, Lavastoviglie, numero_lavastoviglie);
    if (numero_lavatrici != 0)
    {
        ordinamento_elettrodomestici_marca(Lavatrici, numero_lavatrici);
        cout << "[INFO]Elenco lavatrici in magazzino:" << endl;
        riepilogo_elettrodomestici(Lavatrici, numero_lavatrici);
    } else {
        cout << "[INFO]Nessuna lavatrice presente in magazzino." << endl << endl;
    }
    if (numero_asciugatrici != 0)
    {
        ordinamento_elettrodomestici_marca(Asciugatrici, numero_asciugatrici);
        cout << "[INFO]Elenco asciugatrici in magazzino:" << endl;
        riepilogo_elettrodomestici(Asciugatrici, numero_asciugatrici);
    } else {
        cout << "[INFO]Nessuna asciugatrice presente in magazzino." << endl << endl;
    }
    if (numero_lavasciughe != 0)
    {
        ordinamento_elettrodomestici_marca(Lavasciughe, numero_lavasciughe);
        cout << "[INFO]Elenco lavasciughe in magazzino:" << endl;
        riepilogo_elettrodomestici(Lavasciughe, numero_lavasciughe);
    } else {
        cout << "[INFO]Nessuna lavasciuga presente in magazzino." << endl << endl;
    }
    if (numero_lavastoviglie != 0)
    {
        ordinamento_elettrodomestici_marca(Lavastoviglie, numero_lavastoviglie);
        cout << "[INFO]Elenco lavastoviglie in magazzino:" << endl;
        riepilogo_elettrodomestici(Lavastoviglie, numero_lavastoviglie);
    } else {
        cout << "[INFO]Nessuna lavastoviglie presente in magazzino." << endl << endl;
    }

    //PUNTO 4
    evidenziazione_tipologie_elettrodomestici_economici_disponibili(Elettrodomestici, numero_elettrodomestici);
    cout << "[INFO]Elenco elettrodomestici in magazzino (Elettrodomestici disponibili ed economici della/e marca/e ricercata/e evidenziati dalla Tipologia in maiuscolo):" << endl;
    riepilogo_elettrodomestici(Elettrodomestici, numero_elettrodomestici);
}

void lettura_inventario(PElettr& Elettrodomestici, int& numero_elettrodomestici) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;
    Stringa marca;
    int tipo;
    float prezzo;
    bool disponibilita;

    //CONTEGGIO ELETTRODOMESTICI NELL'INVENTARIO
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'inventario del magazzino. Rivolgersi al personale sul posto." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_elettrodomestici++;
        file.ignore(100, '\n');
    }
    file.close();

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI ELETTRODOMESTICI IN MAGAZZINO
    Elettrodomestici = new Elettrodomestico[numero_elettrodomestici];
    numero_elettrodomestici = 0;
    file.open("magazzino.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'inventario del magazzino. Rivolgersi al personale sul posto." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> marca;
        file >> tipo;
        file >> prezzo;
        file >> disponibilita;

        strcpy( (*(Elettrodomestici + numero_elettrodomestici)).marca, marca );
        switch ( tipo )
        {
        case 0:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavatrice;
            break;
        case 1:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = asciugatrice;
            break;
        case 2:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavasciuga;
            break;
        case 3:
            (*(Elettrodomestici + numero_elettrodomestici)).tipo = lavastoviglie;
            break;
        }
        (*(Elettrodomestici + numero_elettrodomestici)).prezzo = prezzo;
        (*(Elettrodomestici + numero_elettrodomestici)).disponibilita = disponibilita;

        numero_elettrodomestici++;
    }
    file.close();
    
}

void riepilogo_elettrodomestici (PElettr Elettrodomestici, int numero_elettrodomestici) {
    //STAMPA A VIDEO VETTORE DI ELETTRODOMESTICI
    for (int i = 0; i < numero_elettrodomestici; i++, cout << endl)
    {
        cout << "[*]Scheda tecnica elettrodomestico " << i+1 << ":" << endl;
        cout << "[MARCA]-->" << (*(Elettrodomestici + i)).marca << endl;
        switch ((*(Elettrodomestici + i)).tipo)
        {
        //TIPOLOGIE NON EVIDENZIATE
        case 0:
            cout << "[TIPOLOGIA]-->lavatrice" << endl;
            break;
        case 1:
            cout << "[TIPOLOGIA]-->asciugatrice" << endl;
            break;
        case 2:
            cout << "[TIPOLOGIA]-->lavasciuga" << endl;
            break;
        case 3:
            cout << "[TIPOLOGIA]-->lavastoviglie" << endl;
            break;
        //TIPOLOGIE EVIDENZIATE
        case 4:
            cout << "[TIPOLOGIA]-->LAVATRICE" << endl;
            break;
        case 5:
            cout << "[TIPOLOGIA]-->ASCIUGATRICE" << endl;
            break;
        case 6:
            cout << "[TIPOLOGIA]-->LAVASCIUGA" << endl;
            break;
        case 7:
            cout << "[TIPOLOGIA]-->LAVASTOVIGLIE" << endl;
            break;
        }
        cout << "[PREZZO]-->" << (*(Elettrodomestici + i)).prezzo << "EURO" << endl;
        switch ((*(Elettrodomestici + i)).disponibilita)
        {
        case true:
            cout << "[DISPONIBILITA]-->DISPONIBILE" << endl;
            break;
        case false:
            cout << "[DISPONIBILITA]-->ESAURITO" << endl;
            break;
        }
    }
    
}

void separazione_tipolgie (PElettr Elettrodomestici, int numero_elettrodomestici, PElettr& Lavatrici, int& numero_lavatrici, PElettr& Asciugatrici, int& numero_asciugatrici, PElettr& Lavasciughe, int& numero_lavasciughe, PElettr& Lavastoviglie, int& numero_lavastoviglie) {
    //CONTEGGIO ELEETTRODOMESTICI PER OGNI TIPOLOGIA
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        switch ((*(Elettrodomestici + i)).tipo)
        {
        case 0:
            numero_lavatrici++;
            break;
        case 1:
            numero_asciugatrici++;
            break;
        case 2:
            numero_lavasciughe++;
            break;
        case 3:
            numero_lavastoviglie++;
            break;
        }
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORI PER OGNI TIPOLOGIA
    Lavatrici = new Elettrodomestico[numero_lavatrici];
    Asciugatrici = new Elettrodomestico[numero_asciugatrici];
    Lavasciughe = new Elettrodomestico[numero_lavasciughe];
    Lavastoviglie = new Elettrodomestico[numero_lavastoviglie];
    numero_lavatrici = 0;
    numero_asciugatrici = 0;
    numero_lavasciughe = 0;
    numero_lavastoviglie = 0;
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        switch ((*(Elettrodomestici + i)).tipo)
        {
        case 0:
            *(Lavatrici + numero_lavatrici) = *(Elettrodomestici + i);
            numero_lavatrici++;
            break;
        case 1:
            *(Asciugatrici + numero_asciugatrici) = *(Elettrodomestici + i);
            numero_asciugatrici++;
            break;
        case 2:
            *(Lavasciughe + numero_lavasciughe) = *(Elettrodomestici + i);
            numero_lavasciughe++;
            break;
        case 3:
            *(Lavastoviglie + numero_lavastoviglie) = *(Elettrodomestici + i);
            numero_lavastoviglie++;
            break;
        }
    }
    
}

void ordinamento_elettrodomestici_marca (PElettr& Elettrodomestici, int numero_elettrdomestici) {
    //DICHIARAZIONI VARIABILI UTILI
    int pos_min_alfabetico;
    Stringa min_alfabetico;
    Elettrodomestico temp;

    //ORDINAMENTO ALFABETICO VETTORE DI ELETTRDOMESTICI
    for (int i = 0; i < numero_elettrdomestici-1; i++)
    {
        pos_min_alfabetico = i;
        strcpy(min_alfabetico,(*(Elettrodomestici + i)).marca );
        for (int j = i+1; j < numero_elettrdomestici; j++)
        {
            if ( strcmp((*(Elettrodomestici + j)).marca, min_alfabetico) < 0 )
            {
                pos_min_alfabetico = j;
                strcpy(min_alfabetico,(*(Elettrodomestici + j)).marca );
            }
        }
        temp = *(Elettrodomestici + pos_min_alfabetico);
        *(Elettrodomestici + pos_min_alfabetico) = *(Elettrodomestici + i);
        *(Elettrodomestici + i) = temp;
    }
    
}

void evidenziazione_tipologie_elettrodomestici_economici_disponibili (PElettr& Elettrodomestici, int numero_elettrodomestici) {
    //DICHIARAZIONI VARIABILI UTILI
    char iniziali_marca_ricercata[4];
    float prezzo_min = 0;

    //INSERIMENTO DA TASTIERA INIZIALI MARCA DEGLI ELETTRDOMESTICI ECONOMICI E DISPONIBILI DA EVIDENZIARE
    cout << "[INSERT]Inserisci le prime tre lettere della/e marca/e di cui evidenziare la tipolgia piu economica di elettrdomestici disponibili: "; cin >> iniziali_marca_ricercata;

    //DETRMINAZIONE PREZZO ELETTR DISPONIBILI E A PREZZO MINIMO LA CUI MARCA INIZI CON I CARATTERI INDICATI
    prezzo_min = (*Elettrodomestici).prezzo;
    for (int i = 1; i < numero_elettrodomestici; i++)
    {
        if ( (*(Elettrodomestici + i)).disponibilita && ( strncmp((*(Elettrodomestici + i)).marca, iniziali_marca_ricercata, 3) == 0 ) && ( (*(Elettrodomestici + i)).prezzo < prezzo_min ) )
        {
            prezzo_min = (*(Elettrodomestici + i)).prezzo;
        }
    }

    //EVIDENZIAZIONE TIPOLOGIA ELETTR DISPONIBILI E A PREZZO MINIMO LA CUI MARCA INIZI CON I CARATTERI INDICATI
    for (int i = 0; i < numero_elettrodomestici; i++)
    {
        if ( (*(Elettrodomestici + i)).disponibilita && ( strncmp((*(Elettrodomestici + i)).marca, iniziali_marca_ricercata, 3) == 0 ) && ( (*(Elettrodomestici + i)).prezzo == prezzo_min ) )
        {
            switch ((*(Elettrodomestici + i)).tipo)
            {
            case 0:
                (*(Elettrodomestici + i)).tipo = LAVATRICE;
                break;
            case 1:
                (*(Elettrodomestici + i)).tipo = ASCIUGATRICE;
                break;
            case 2:
                (*(Elettrodomestici + i)).tipo = LAVASCIUGA;
                break;
            case 3:
                (*(Elettrodomestici + i)).tipo = LAVASTOVIGLIE;
                break;
            }
        }
    }
    
}
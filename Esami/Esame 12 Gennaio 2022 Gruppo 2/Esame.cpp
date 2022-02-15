#define MAX_PARKINGS 100
#include <iostream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Parcheggio
{
    int id;
    int capienza_corrente;
    int capienza_massima;
    float costo; //Costo orario per autovettura
};

//PROTOTIPI
void inserimento_numero_parcheggi (int&);
void inserimento_caratteristiche_parcheggi (Parcheggio[], int);
void riepilogo_parcheggi (const Parcheggio[], int);
void ordinamento_parcheggi_ricavo (Parcheggio[], int);
void aggiunta_nuovo_parcheggio (Parcheggio Parcheggi[], int& numero_parcheggi);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    Parcheggio Parcheggi[MAX_PARKINGS];
    int numero_parcheggi = 0;

    //CHIAMATE FUNZIONI
    inserimento_numero_parcheggi(numero_parcheggi);
    inserimento_caratteristiche_parcheggi(Parcheggi, numero_parcheggi);
    cout << "[INFO]Riepilogo parcheggi attivi nella giornata odierna:" << endl;
    riepilogo_parcheggi(Parcheggi, numero_parcheggi);

    ordinamento_parcheggi_ricavo(Parcheggi, numero_parcheggi);
    cout << "[INFO]Riepilogo parcheggi attivi nella giornata odierna in ordine crescente in base al ricavo:" << endl;
    riepilogo_parcheggi(Parcheggi, numero_parcheggi);

    aggiunta_nuovo_parcheggio(Parcheggi, numero_parcheggi);
    cout << "[INFO]Riepilogo finale (POST AGGIUNTA) parcheggi attivi nella giornata odierna:" << endl;
    riepilogo_parcheggi(Parcheggi, numero_parcheggi);
}

void inserimento_numero_parcheggi (int& numero_parcheggi) {
    //LETTURA DA TASTIERA RIEMPIMENTO DEL VETTORE DI PARCHEGGI
    do
    {
        cout << "[INSERT]Inserisci il numero di parcheggi attivi nella giornata odierna: "; cin >> numero_parcheggi;
        if (numero_parcheggi<1 || numero_parcheggi>99)
        {
            cout << "[WARNING]Valore inserito non valido. Riprovare." << endl;
            cout << "[PROMEMORIA]E' necessario attivare almeno un parcheggio[PROMEMORIA]" << endl;
            cout << "[PROMEMORIA]Il numero massimo di parcheggi inseribili è attualmente pari a 99.[PROMEMORIA]" << endl;
        }
    } while (numero_parcheggi<1 || numero_parcheggi>99);
    
}

void inserimento_caratteristiche_parcheggi (Parcheggio Parcheggi[], int numero_parcheggi) {
    //INSERIMENTO ELEMENTI DEL VETTORE DI PARCHEGGI DA TASTIERA
    for (int i = 0; i < numero_parcheggi; i++)
    {
        do
        {
            cout << "[INSERT]Inserisci le caratteristiche tecniche del parcheggio " << i+1 << ":" << endl;
            cout << "[ID]--->"; cin >> Parcheggi[i].id;
            cout << "[CAPIENZA CORRENTE]--->"; cin >> Parcheggi[i].capienza_corrente;
            cout << "[CAPIENZA MASSIMA]--->"; cin >> Parcheggi[i].capienza_massima;
            cout << "[COSTO ORARIO PER AUTOVETTURA]--->"; cin >> Parcheggi[i].costo;
            if (Parcheggi[i].capienza_corrente > Parcheggi[i].capienza_massima)
            {
                cout << "[WARNING]Dati inseriti non validi. La capienza corrente non puo eccedere la capienza massima. Riprovare." << endl;
            }
        } while (Parcheggi[i].capienza_corrente > Parcheggi[i].capienza_massima);
    }
    
}

void riepilogo_parcheggi (const Parcheggio Parcheggi[], int numero_parcheggi) {
    //STAMPA A VIDEO VETTORE DI PARCHEGGI
    for (int i = 0; i < numero_parcheggi; i++, cout << endl)
    {
        cout << "[*]Caratteristiche tecniche parcheggio " << i+1 << ":" << endl;
        cout << "[ID]--->" << Parcheggi[i].id << endl;
        cout << "[CAPIENZA CORRENTE]--->" << Parcheggi[i].capienza_corrente << endl;
        cout << "[CAPIENZA MASSIMA]--->" << Parcheggi[i].capienza_massima << endl;
        cout << "[COSTO ORARIO PER AUTOVETTURA]--->" << Parcheggi[i].costo << "EURO" << endl;
    }
    
}

void ordinamento_parcheggi_ricavo (Parcheggio Parcheggi[], int numero_parcheggi) {
    //DICHIARAZIONI VARIABILI UTILI
    float ricavo = 0.0;
    int pos_min = 0;
    float ricavo_min = 0.0;
    Parcheggio temp;

    //ORDINAMENTO IN BASE AL RICAVO
    for (int i = 0; i < numero_parcheggi-1; i++)
    {
        pos_min = i;
        ricavo_min = Parcheggi[i].costo * Parcheggi[i].capienza_corrente;
        for (int j = i+1; j < numero_parcheggi; j++)
        {
            ricavo = Parcheggi[j].costo * Parcheggi[j].capienza_corrente;
            if (ricavo < ricavo_min)
            {
                pos_min = j;
                ricavo_min = ricavo;
            }
        }
        temp = Parcheggi[pos_min];
        Parcheggi[pos_min] = Parcheggi[i];
        Parcheggi[i] = temp;
    }
    
}

void aggiunta_nuovo_parcheggio (Parcheggio Parcheggi[], int& numero_parcheggi) {
    //DICHIARAZIONI VARIABILI UTILI
    int id_nuovo_parcheggio = 0;;
    int capienza_corrente_nuovo_parcheggio = 0;
    int capienza_massima_nuovo_parcheggio = 0;
    float costo_nuovo_parcheggio = 0.0;
    int pos_min = 0;
    int capienza_massima_min = 0;

    //INSERIMENTO CAMPI NUOVO ELEMENTO DEL VETTORE DI PARCHEGGI 
    do
    {
        cout << "[INSERT]Inserisci le caratteristiche tecniche del nuovo parcheggio da aggiungere:" << endl;
        cout << "[ID]--->"; cin >> id_nuovo_parcheggio;
        cout << "[CAPIENZA CORRENTE]--->"; cin >> capienza_corrente_nuovo_parcheggio;
        cout << "[CAPIENZA MASSIMA]--->"; cin >> capienza_massima_nuovo_parcheggio;
        cout << "[COSTO ORARIO PER AUTOVETTURA]--->"; cin >> costo_nuovo_parcheggio;
        if (capienza_corrente_nuovo_parcheggio > capienza_massima_nuovo_parcheggio)
        {
            cout << "[WARNING]Dati inseriti non validi. La capienza corrente non puo eccedere la capienza massima. Riprovare." << endl;
        }
    } while (capienza_corrente_nuovo_parcheggio > capienza_massima_nuovo_parcheggio);

    //DETERMINAZIONE PRIMO ELEMENTO DEL VETTORE A MINIMA CAPACITA'
    pos_min = 0;
    capienza_massima_min = Parcheggi[0].capienza_massima;
    for (int i = 0; i < numero_parcheggi; i++)
    {
        if (Parcheggi[i].capienza_massima < capienza_massima_min)
        {
            pos_min = i;
            capienza_massima_min = Parcheggi[i].capienza_massima;
        }
    }
    

    //INSERIMENTO NUOVO ELEMENTO NEL VETTORE DI PARCHEGGI DOPO PRIMO ELEMENTO A CAPIENZA MINIMA
    numero_parcheggi++;
    for (int i = numero_parcheggi-1; i > pos_min+1; i--)
    {
        Parcheggi[i] = Parcheggi[i-1];
    }
    Parcheggi[pos_min+1].id = id_nuovo_parcheggio;
    Parcheggi[pos_min+1].capienza_corrente = capienza_corrente_nuovo_parcheggio;
    Parcheggi[pos_min+1].capienza_massima = capienza_massima_nuovo_parcheggio;
    Parcheggi[pos_min+1].costo = costo_nuovo_parcheggio;
    
}
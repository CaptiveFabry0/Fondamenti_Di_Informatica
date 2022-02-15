#include <iostream>
#define MAX_FURGONI 100
using namespace std;

//TIPI ED ALIAS UTILI
struct Furgone {
    int id;
    int consegne_mancanti;
    int capienza;
    float incasso_consegne;
};

//Prototipi
void inserimento_furgoni_attivi (Furgone[], int&);
void riepilogo_furgoni (const Furgone[], int);
void riepilogo_furgoni_efficienti (const Furgone[], int);
void eliminazione_furgoni_vuoti (Furgone[], int&);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    Furgone Furgoni[MAX_FURGONI];
    int numero_furgoni_attivi = 0;

    //CHIAMATE FUNZIONI
    inserimento_furgoni_attivi(Furgoni, numero_furgoni_attivi);
    cout << "[INFO]Riepilogo furgoni attivi in data odierna:" << endl;
    riepilogo_furgoni(Furgoni, numero_furgoni_attivi); 

    cout << "[INFO]Riepilogo furgoni più efficienti in data odierna:" << endl;
    riepilogo_furgoni_efficienti(Furgoni, numero_furgoni_attivi);

    eliminazione_furgoni_vuoti(Furgoni, numero_furgoni_attivi);
    cout << "[INFO]Riepilogo furgoni attivi in data odierna con consegne da effettuare:" << endl;
    riepilogo_furgoni(Furgoni, numero_furgoni_attivi);

}

void inserimento_furgoni_attivi (Furgone Furgoni[], int& numero_furgoni_attivi) {
    //INSERIMENTO DA TASTIERA NUMERO DI FURGONI ATTIVI IN GIORNATA
    do
    {
        cout << "[PROMEMORIA]Il numero massimo corrente di furgoni è pari a 100 unità[PROMEMORIA]" << endl;
        cout << "[INSERT]Inserisci il numero dei furgoni attivi nella giornata odierna: ";
        cin >> numero_furgoni_attivi;
        if (numero_furgoni_attivi < 1 || numero_furgoni_attivi > 100)
        {
            cout << "[WARNING]Numero di furgoni attivi inserito non consentito. Riprovare." << endl;
        }
    } while (numero_furgoni_attivi < 1 || numero_furgoni_attivi > 100);

   //INSERIMENTO CARATTERISTICHE FURGONI ATTIVI IN GIORNATA
   for (int i = 0; i < numero_furgoni_attivi; i++, cout << endl)
   {
       cout << "[INSERT]Inserisci dati del furgone numero " << i+1 << ":" << endl;
       cout << "[ID]--->"; cin >> Furgoni[i].id;
       cout << "[CONSEGNE MANCANTI]--->"; cin >> Furgoni[i].consegne_mancanti;
       cout << "[CAPIENZA]--->"; cin >> Furgoni[i].capienza;
       cout << "[INCASSO GIORNALIERO STIMATO]--->"; cin >> Furgoni[i].incasso_consegne;
   }

}

void riepilogo_furgoni (const Furgone Furgoni[], int numero_furgoni) {
    //STAMPA VETTORE DI FURGONI
    for (int i = 0; i < numero_furgoni; i++, cout << endl)
    {
        cout << "[ID]--->" << Furgoni[i].id << endl;
        cout << "[CONSEGNE MANCANTI]--->" << Furgoni[i].consegne_mancanti << endl;
        cout << "[CAPIENZA]--->" << Furgoni[i].capienza << endl;
        cout << "[INCASSO GIORNALIERO STIMATO]--->" << Furgoni[i].incasso_consegne << endl;
    }
    
}

void riepilogo_furgoni_efficienti (const Furgone Furgoni[], int numero_furgoni) {
    //DICHIARAZIONI VARIABILI UTILI
    float efficienza_max = Furgoni[0].capienza - Furgoni[1].consegne_mancanti;

    //DETRMINAZIONE EFFICIENZA MASSIMA
    for (int i = 0; i < numero_furgoni; i++)
    {
        if ( (Furgoni[i].capienza - Furgoni[i].consegne_mancanti) > efficienza_max )
        {
            efficienza_max = (Furgoni[i].capienza - Furgoni[i].consegne_mancanti);
        }
    }

    //STAMPA CARATTERISTICHE FURGONI + EFFICIENTI
    for (int i = 0; i < numero_furgoni; i++)
    {
        if ( (Furgoni[i].capienza - Furgoni[i].consegne_mancanti) == efficienza_max )
        {
            cout << "[ID]--->" << Furgoni[i].id << endl;
            cout << "[CONSEGNE MANCANTI]--->" << Furgoni[i].consegne_mancanti << endl;
            cout << "[CAPIENZA]--->" << Furgoni[i].capienza << endl;
            cout << "[INCASSO GIORNALIERO STIMATO]--->" << Furgoni[i].incasso_consegne << endl;
            cout << "[EFFICIENZA]--->" << efficienza_max << endl;
            cout << endl;
        }
    }

}

void eliminazione_furgoni_vuoti (Furgone Furgoni[], int& numero_furgoni) {
    //ELIMINAZIONE DAL VETTORE DEI FURGONI CON CONSEGNE MANCANTI EFFETTUATE
    for (int i = 0; i < numero_furgoni; i++)
    {
        if (Furgoni[i].consegne_mancanti == 0)
        {
            numero_furgoni--;
            for (int j = i; j < numero_furgoni; j++)
            {
                Furgoni[j] = Furgoni[j+1];
            }
            i--;
        }
    }
    
}
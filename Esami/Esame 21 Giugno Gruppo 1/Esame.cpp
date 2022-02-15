#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Immagine {
    float x_lenght;
    float y_height;
    long dim_byte;
};
typedef Immagine* PImg;

//PROTOTIPI
void lettura_immagini (PImg&, int&);
void display_immagini (PImg, int);
void ricerca_immagini (PImg, int);
void individuazione_immagini_min_dens (PImg, PImg&, int, int&);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    PImg Immagini = NULL, Immagini_min_dens = NULL;
    int numero_immagini = 0, numero_immagini_min_dens = 0;

    //CHIAMATE FUNZIONI
    lettura_immagini(Immagini, numero_immagini);
    cout << "[INFO]Immagini disponibili in galleria:" << endl;
    display_immagini(Immagini, numero_immagini);

    ricerca_immagini(Immagini, numero_immagini);

    individuazione_immagini_min_dens(Immagini, Immagini_min_dens, numero_immagini, numero_immagini_min_dens);
    cout << "[INFO]Immagini in galleria a minore densità:" << endl;
    display_immagini(Immagini_min_dens, numero_immagini_min_dens);
}

void lettura_immagini (PImg& Immagini, int& numero_immagini) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //CONTEGGIO NUMERO IMMAGINI
    file.open("immagini.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile trovare il file contenente l'elenco delle immagini. Terminazione del programma." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_immagini++;
        file.ignore(100, '\n');
    }
    file.close();

    //CREAZIONE E RIEMPIMENTO DEL VETTORE DI IMMAGINI
    Immagini = new Immagine[numero_immagini];
    numero_immagini = 0;
    file.open("immagini.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile trovare il file contenente l'elenco delle immagini. Terminazione del programma." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> (*(Immagini + numero_immagini)).x_lenght;
        file >> (*(Immagini + numero_immagini)).y_height;
        file >> (*(Immagini + numero_immagini)).dim_byte;
        numero_immagini++;
    }
    file.close();
    
}

void display_immagini (PImg Immagini, int numero_immagini) {
    //STAMPA VETTORE DI IMMAGINI
    for (int i = 0; i < numero_immagini; i++, cout << endl)
    {
        cout << "Immagine " << i+1 << ":" << endl;
        cout << "[X_LENGHT]--->" << (*(Immagini + i)).x_lenght << endl;
        cout << "[Y_LENGHT]--->" << (*(Immagini + i)).y_height << endl;
        cout << "[DIMENSIONI]--->" << (*(Immagini + i)).dim_byte << "B" << endl;
    }
}

void ricerca_immagini (PImg Immagini, int numero_immagini) {
    //DICHIARAZIONI UTILI
    float lunghezza_inserita = 0;
    int pos_prime_immagini_ricercate[2] = {0};
    int numero_immagini_trovate = 0;

    //INSERIMENTO LUNGHEZZA DA TASTIERA
    do
    {
        cout << "[INFO]Inserisci la lunghezza delle immagini da ricercare: ";
        cin >> lunghezza_inserita;
        if (lunghezza_inserita <= 0)
        {
            cout << "[WARNING]Lunghezza inserita non consentita. Riprovare." << endl;
        }
        
    } while (lunghezza_inserita <= 0);

    //INDIVIDUAZIONE E CONTEGGIO IMMAGINI TROVATE
    for (int i = 0; i < numero_immagini; i++)
    {
        if ((*(Immagini + i)).x_lenght == lunghezza_inserita && numero_immagini_trovate < 2)
        {
            *(pos_prime_immagini_ricercate + numero_immagini_trovate) = i;
            numero_immagini_trovate++;
        }
    }

    //PRESENTAZIONE RISULTATI RICERCA
    switch (numero_immagini_trovate)
    {
    case 0:
        cout << "[ERRORE]Nessun immagine trovata dalla lunghezza inserita." << endl;
        break;
    
    case 1:
        cout << "[WARNING]Un'unica immagine è stata trovata dalla lunghezza inserita:" << endl;

        cout << "[X_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).x_lenght << endl;
        cout << "[Y_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).y_height << endl;
        cout << "[DIMENSIONI]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).dim_byte << "B" << endl;
        break;
    
    default:
        cout << "[INFO]Prime due immagini disponibili dalla lunghezza indicata:" << endl;

        cout << "[X_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate + 1))).x_lenght << endl;
        cout << "[Y_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate + 1))).y_height << endl;
        cout << "[DIMENSIONI]--->" << (*(Immagini + *(pos_prime_immagini_ricercate + 1))).dim_byte << "B" << endl;

        cout << endl;

        cout << "[X_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).x_lenght << endl;
        cout << "[Y_LENGHT]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).y_height << endl;
        cout << "[DIMENSIONI]--->" << (*(Immagini + *(pos_prime_immagini_ricercate))).dim_byte << "B" << endl;
        break;
    }

}

void individuazione_immagini_min_dens (PImg Immagini, PImg& Immagini_min_dens, int numero_immagini, int& numero_immagini_min_dens) {
    //DICHIARAZIONI VARIABILI UTILI
    float medium_density = 0.0;

    //DETERMINAZIONE DENSITA' MEDIA
    for (int i = 0; i < numero_immagini; i++)
    {
        medium_density += (*(Immagini + i)).dim_byte / ((((*(Immagini + i)).x_lenght * (*(Immagini + i)).y_height))/2);
    }
    medium_density /= numero_immagini;

    //CONTEGGIO IMMAGINI A MINORE DENSITA'
    for (int i = 0; i < numero_immagini; i++)
    {
        if ( (*(Immagini + i)).dim_byte / ((((*(Immagini + i)).x_lenght * (*(Immagini + i)).y_height))/2) <= medium_density )
        {
            numero_immagini_min_dens++;
        }
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI IMMAGINI A MINORE DENSITA'
    Immagini_min_dens = new Immagine[numero_immagini_min_dens];
    numero_immagini_min_dens = 0;
    for (int i = 0; i < numero_immagini; i++)
    {
        if ( (*(Immagini + i)).dim_byte / ((((*(Immagini + i)).x_lenght * (*(Immagini + i)).y_height))/2) <= medium_density )
        {
            *(Immagini_min_dens + numero_immagini_min_dens) = *(Immagini + i);
            numero_immagini_min_dens++;
        }
    }
    
}
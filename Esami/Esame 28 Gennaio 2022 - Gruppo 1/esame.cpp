#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Rettangolo {
    int base;
    int altezza;
};
typedef Rettangolo* PRet;

//PROTOTIPI
void generazione_vettore_rettangoli(PRet&, int&);
void stampa_rettangoli(PRet, int);
void rotazione_rettangolo_speciale(PRet&, int);
void aggiunta_rettangoli_temporanei(PRet&, PRet, int&, int);

int main() {
    PRet Rettangoli = NULL;
    int numero_rettangoli = 0;
    PRet Vettore_Aggiornato = NULL;
    int elementi_vettore_aggiornato = 0;

    generazione_vettore_rettangoli(Rettangoli, numero_rettangoli);
    cout << "[INFO]Vettore dei rettangoli:" << endl;
    stampa_rettangoli(Rettangoli, numero_rettangoli); 
    
    rotazione_rettangolo_speciale(Rettangoli, numero_rettangoli);
    cout << "[INFO]Vettore dei rettangoli (POST ROTAZIONE RETTANGOLO SPECIALE):" << endl;
    stampa_rettangoli(Rettangoli, numero_rettangoli); //POST ROTAZIONE RETTANGOLO A MASSIMO RAPPORTO B/A

    cout << "[INFO]Vettore dei rettangoli aggiornato(POST AGGIUNTA RETTANGOLI TEMPORANEI):" << endl;
    aggiunta_rettangoli_temporanei(Vettore_Aggiornato, Rettangoli, elementi_vettore_aggiornato, numero_rettangoli);
    stampa_rettangoli(Vettore_Aggiornato, elementi_vettore_aggiornato); //POST AGGIUNTA RETTANGOLI TEMPORANEI
}

void generazione_vettore_rettangoli(PRet& Rettangoli, int& numero_rettangoli) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //LETTURA NUMERO DI RETTANGOLI
    file.open("rettangoli.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile aprire il file \"rettangoli.txt\". Terminazione del programma." << endl;
        exit(1);
    }
    file >> numero_rettangoli; //LA PRIMA RIGA DEL FILE CONTIENE IL NUMERO DI RETTANGOLI
    file.close();
    if (numero_rettangoli > 30 || numero_rettangoli == 0)
    {
        cout << "[ERRORE]Numero di rettangoli presenti non trattabile. Terminazione del programma." << endl;
        exit(1);
    }
    

    //ALLOCAZIONE E RIEMPIMENTO VETTORE
    Rettangoli = new Rettangolo[numero_rettangoli];
    if (Rettangoli == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione. Terminazione del programma" << endl;
        exit(1);
    }
    for (int i = 0; i < numero_rettangoli; i++)
    {
        file >> (*(Rettangoli + i)).base;
        file >> (*(Rettangoli + i)).altezza;
    }
    
}

void stampa_rettangoli(PRet Rettangoli, int numero_rettangoli) {
    
    //STAMPA VETTORE
    for (int i = 0; i < numero_rettangoli; i++, cout << endl)
    {
        cout << "[*]Rettangolo numero " << i+1 << ":" << endl;
        cout << "Base--->" << (*(Rettangoli + i)).base << endl;
        cout << "Altezza--->" << (*(Rettangoli + i)).altezza << endl;
    }
    
}

void rotazione_rettangolo_speciale(PRet& Rettangoli, int numero_rettangoli) {
    //DICHIARAZIONI VARIABILI UTILI
    float max_rapporto = ((*(Rettangoli)).base)/((*(Rettangoli)).altezza); //MASSIMO RAPPORTO B/A DI DEFAULT
    int pos_rettangolo_spec = 0; //INDICE DI DEFAULT DEL RETTANGOLO DAL MASSIMO RAPPORTO B/A

    //RICERCA MASSIMO RAPPORTO B/A
    for (int i = 0; i < numero_rettangoli; i++)
    {
        if ( ((*(Rettangoli + i)).base)/((*(Rettangoli + i)).altezza) > max_rapporto )
        {
            pos_rettangolo_spec = i;
            max_rapporto = ((*(Rettangoli + i)).base)/((*(Rettangoli + i)).altezza);
        }
    }
    int temp = (*(Rettangoli + pos_rettangolo_spec)).altezza;
    (*(Rettangoli + pos_rettangolo_spec)).altezza = (*(Rettangoli + pos_rettangolo_spec)).base;
    (*(Rettangoli + pos_rettangolo_spec)).base = temp;

}

void aggiunta_rettangoli_temporanei(PRet& Vettore_Aggiornato, PRet Rettangoli, int &elementi_vettore_aggiornato , int numero_rettangoli) {
    //DICHIARAZIONI VARIABILI UTILI
    int numero_quadrati = 0;

    //CONTEGGIO QUADRATI
    for (int i = 0; i < numero_rettangoli; i++)
    {
        if ( (*(Rettangoli + i)).base == (*(Rettangoli + i)).altezza )
        {
            numero_quadrati++;
        }
    }
    elementi_vettore_aggiornato = numero_rettangoli + numero_quadrati;

    //CREAZIONE NUOVO VETTORE CON RETTANGOLI TEMPORANEI
    Vettore_Aggiornato = new Rettangolo[elementi_vettore_aggiornato];
    if (Vettore_Aggiornato == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione. Terminazione del programma" << endl;
        exit(1);
    }

    //RIEMPIMENTO NUOVO VETTORE CON RETTANGOLI NORMALI
    for (int i = 0; i < numero_rettangoli; i++)
    {
        *(Vettore_Aggiornato + i) = *(Rettangoli + i);
    }

    //AGGIUNTA AL NUOVO VETTORE DEI RETTANGOLI TEMPORANEI
    for (int i = 0; i < (elementi_vettore_aggiornato); i++)
    {
        if ( ((*(Vettore_Aggiornato + i)).base == (*(Vettore_Aggiornato + i)).altezza) && ((*(Vettore_Aggiornato + i)).base != -1) )
        {
            numero_rettangoli++;
            for (int j = numero_rettangoli - 1; j > (i+1); j--)
            {
                *(Vettore_Aggiornato + j) = *(Vettore_Aggiornato + (j-1));
            }
            (*(Vettore_Aggiornato + (i+1))).altezza = -1;
            (*(Vettore_Aggiornato + (i+1))).base = -1;
        }
    }

}
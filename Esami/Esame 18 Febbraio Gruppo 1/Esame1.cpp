#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
typedef char Stringa[16];
struct Pietanza {
    Stringa nome;
    float prezzo;
};
typedef Pietanza* PPiet;

//PROTOTIPI
void lettura_menu(PPiet&, int&);
void display_menu(PPiet, int);
void ordinamento_alfabetico_menu(PPiet&, int);
void generazione_vettori_pietanze (PPiet, int, PPiet&, int&, PPiet&, int&);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    PPiet Pietanze = NULL, Pietanze_A_D = NULL, Pietanze_M_P = NULL;
    int numero_pietanze = 0, numero_pietanze_A_D = 0, numero_pietanze_M_P = 0;

    //CHIAMATE FUNZIONI
    lettura_menu(Pietanze, numero_pietanze);
    cout << "[INFO]Pietanze nel menu giornaliero:" << endl;
    display_menu(Pietanze, numero_pietanze);

    ordinamento_alfabetico_menu(Pietanze, numero_pietanze);
    cout << "[INFO]Pietanze nel menu giornaliero (ORDINAMENTO ALFABETICO):" << endl;
    display_menu(Pietanze, numero_pietanze);
    
    generazione_vettori_pietanze(Pietanze, numero_pietanze, Pietanze_A_D, numero_pietanze_A_D, Pietanze_M_P, numero_pietanze_M_P);
    if (numero_pietanze_A_D != 0)
    {
        cout << "[INFO]Pietanze nel menu giornaliero dalla \"A\" alla \"D\":" << endl;
        display_menu(Pietanze_A_D, numero_pietanze_A_D);
    }
    if (numero_pietanze_M_P != 0)
    {
        cout << "[INFO]Pietanze nel menu giornaliero dalla \"M\" alla \"P\":" << endl;
        display_menu(Pietanze_M_P, numero_pietanze_M_P);
    }

}

void lettura_menu(PPiet& Pietanze, int& numero_pietanze) {
    //DICHIARAZIONI VARIABILI UTILI
    ifstream file;

    //CONTEGGIO PIETANZE NEL MENU
    file.open("menu.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere il menu del giorno. Consultare personalmente i camerieri per le pietanze." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_pietanze++;
        file.ignore(100, '\n');
    }
    file.close();

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI PIETANZE
    Pietanze = new Pietanza[numero_pietanze];
    numero_pietanze = 0;
    file.open("menu.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile leggere il menu del giorno. Consultare personalmente i camerieri per le pietanze." << endl;
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

void display_menu(PPiet Pietanze, int numero_pietanze) {
    //STAMPA VETTORE DI PIETANZE
    for (int i = 0; i < numero_pietanze; i++, cout << endl)
    {
        cout << "[*]Pietanza numero " << i+1 << ":" << endl;
        cout << "[NOME]--->" << (*(Pietanze + i)).nome << endl;
        cout << "[PREZZO]--->" << (*(Pietanze + i)).prezzo << "Euro" << endl;
    }
    
}

void ordinamento_alfabetico_menu(PPiet& Pietanze, int numero_pietanze) {
    //DICHIARAZIONI VARIABILI UTILI
    Pietanza temp;
    int pos_min_alfabetico = 0;
    Stringa min_alfabetico = "";

    //ORDINAMENTO VETTORE
    for (int i = 0; i < numero_pietanze - 1; i++)
    {
        pos_min_alfabetico = i;
        strcpy(min_alfabetico, (*(Pietanze + i)).nome);
        for (int j = i+1; j < numero_pietanze; j++)
        {
            if (strcmp( (*(Pietanze + j)).nome, min_alfabetico ) > 0)
            {
                pos_min_alfabetico = j;
                strcpy(min_alfabetico, (*(Pietanze + j)).nome);
            }
        }
        temp = *(Pietanze + pos_min_alfabetico);
        *(Pietanze + pos_min_alfabetico) = *(Pietanze + i);
        *(Pietanze + i) = temp;
    }
}

void generazione_vettori_pietanze (PPiet Pietanze, int numero_pietanze, PPiet& Pietanze_A_D, int& numero_pietanze_A_D, PPiet& Pietanze_M_P, int& numero_pietanze_M_P) {
    //CONTEGGIO PIETANZE NELL'INTERVALLO "A-D" E NELL'INTERVALLO "M-P"
    for (int i = 0; i < numero_pietanze; i++)
    {
        if ( (*(Pietanze + i)).nome[0] >= 97 && (*(Pietanze + i)).nome[0] <= 100 )
        {
            numero_pietanze_A_D++;
        }
        if ( (*(Pietanze + i)).nome[0] >= 109 && (*(Pietanze + i)).nome[0] <= 112 )
        {
            numero_pietanze_M_P++;
        } 
    }

    //ALLOCAZIONE E RIEMPIMENTO VETTORI
    Pietanze_A_D = new Pietanza[numero_pietanze_A_D];
    Pietanze_M_P = new Pietanza[numero_pietanze_M_P];
    numero_pietanze_A_D = 0;
    numero_pietanze_M_P = 0;
    for (int i = 0; i < numero_pietanze; i++)
    {
        if ( (*(Pietanze + i)).nome[0] >= 97 && (*(Pietanze + i)).nome[0] <= 100 )
        {
            *(Pietanze_A_D + numero_pietanze_A_D) = *(Pietanze + i);
            (*(Pietanze_A_D + numero_pietanze_A_D)).nome[0] -= 32;
            numero_pietanze_A_D++;
        }
        if ( (*(Pietanze + i)).nome[0] >= 109 && (*(Pietanze + i)).nome[0] <= 112 )
        {
            *(Pietanze_M_P + numero_pietanze_M_P) = *(Pietanze + i);
            (*(Pietanze_M_P + numero_pietanze_M_P)).nome[0] -= 32;
            numero_pietanze_M_P++;
        } 
    }
    
}
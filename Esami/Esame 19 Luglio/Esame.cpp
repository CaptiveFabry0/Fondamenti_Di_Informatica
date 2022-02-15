#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Traliccio {
    int id;
    float consumo;
    bool status;
};
typedef Traliccio* PTral;

//PROTOTIPI
void lettura_tralicci (PTral&, int&);
void display_tralicci(PTral, int);
void analisi_tralicci (PTral, int, PTral&, int&, PTral&, int&);
void ricerca_tralicci_attivi(PTral, int, PTral&);

int main() {
    PTral Tralicci = NULL, Tralicci_Ottimali = NULL, Tralicci_Non_Ottimali = NULL, Tralicci_Attivi = NULL;
    int numero_tralicci = 0, numero_tralicci_ottimali = 0, numero_tralicci_non_ottimali = 0;

    lettura_tralicci(Tralicci, numero_tralicci);
    if (numero_tralicci != 0)
    {
        cout << "[INFO]Elenco Tralicci:" << endl;
        display_tralicci(Tralicci, numero_tralicci);

        analisi_tralicci(Tralicci, numero_tralicci, Tralicci_Ottimali, numero_tralicci_ottimali, Tralicci_Non_Ottimali, numero_tralicci_non_ottimali);
        if (numero_tralicci_ottimali != 0 && numero_tralicci_non_ottimali != 0)
        {
            cout << "[INFO]Elenco Tralicci Ottimali:" << endl;
            display_tralicci(Tralicci_Ottimali, numero_tralicci_ottimali);
            cout << "[INFO]Elenco Tralicci Non Otttimali:" << endl;
            display_tralicci(Tralicci_Non_Ottimali, numero_tralicci_non_ottimali);
        }

        ricerca_tralicci_attivi(Tralicci, numero_tralicci, Tralicci_Attivi);
        if (Tralicci_Attivi != NULL) //IL NUMERO DI TRALICCI ATTIVI E' >= 4 ---> L'ARRAY DEI TRALICCI ATTIVI E' STATO ORDINATO DECRESCENTEMENTE
        {
            cout << "[INFO]Primi 3 Tralicci Peggiori:" << endl;
            display_tralicci(Tralicci_Attivi, 3);
        }
        
    }  
}

void lettura_tralicci (PTral& Tralicci, int& numero_tralicci) {
    //DICHIRAZIONI VARIABILI UTILI
    ifstream file;

    //CONTEGGIO NUMERO TRALICCI
    file.open("tralicci.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'elenco dei tralicci. Contattare l'amministrazione." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        numero_tralicci++;
        file.ignore(100, '\n');
    }
    file.close();

    //ALLOCAZIONE E RIEMPIMENTO VETTORE DI TRALICCI
    Tralicci = new Traliccio[numero_tralicci];
    numero_tralicci = 0;
    if (Tralicci == NULL)
    {
        cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma." << endl;
        exit(1);
    }
    file.open("tralicci.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile accedere all'elenco dei tralicci. Contattare l'amministrazione." << endl;
        exit(1);
    }
    while (!file.eof())
    {
        file >> (*(Tralicci + numero_tralicci)).id;
        file >> (*(Tralicci + numero_tralicci)).consumo;
        file >> (*(Tralicci + numero_tralicci)).status;
        numero_tralicci++;
    }
    file.close();
    
}

void display_tralicci(PTral Tralicci, int numero_tralicci) {
    
    //STAMPA VETTORE
    for (int i = 0; i < numero_tralicci; i++, cout << endl)
    {
        cout << "[ID] " << (*(Tralicci + i)).id << endl;
        cout << "[CONSUMO] " << (*(Tralicci + i)).consumo << " kW" << endl;
        switch ((*(Tralicci + i)).status)
        {
        case 1:
            cout << "[STATUS] ATTIVO" << endl;
            break;

        case 0:
            cout << "[STATUS] NON FUNZIONANTE" << endl;
            break;
        }
    }
    
}

void analisi_tralicci (PTral Tralicci, int numero_tralicci, PTral& Tralicci_Ottimali, int& numero_tralicci_ottimali, PTral& Tralicci_Non_Ottimali, int& numero_tralicci_non_ottimali) {
    //DICHIARAZIONI VARIABILI UTILI
    int consumo_medio = 0;
    int numero_tralicci_attivi = 0;

    //DETERMINAZIONE CONSUMO MEDIO;
    for (int i = 0; i < numero_tralicci; i++)
    {
        if ((*(Tralicci + i)).status == 1)
        {
            consumo_medio += (*(Tralicci + i)).consumo;
            numero_tralicci_attivi++;
        }
    }

    if (numero_tralicci_attivi==0)
    {
        cout << "[WARNING]Nessun traliccio attivo." << endl;
    } else
    {
        consumo_medio /= numero_tralicci_attivi;
        if (numero_tralicci_attivi==1)
        {
            for (int i = 0; i < numero_tralicci; i++)
            {
                if (((*(Tralicci + i)).consumo == consumo_medio) && ((*(Tralicci + i)).status == 1))
                {
                    cout << "[WARNING]Unico traliccio attivo trovato: " << endl;
                    cout << "[ID] " << (*(Tralicci + i)).id << endl;
                    cout << "[CONSUMO] " << (*(Tralicci + i)).consumo << " kW" << endl;
                    cout << "[STATUS] ATTIVO" << endl << endl;
                } 
            }
        } else
        {
            //DETERMINAZIONE NUMERO TRALICCI OTTIMALI E NON OTTIMALI
            for (int i = 0; i < numero_tralicci; i++)
            {
                if (((*(Tralicci + i)).consumo > consumo_medio) && ((*(Tralicci + i)).status == 1))
                {
                    numero_tralicci_non_ottimali++;
                }
                if (((*(Tralicci + i)).consumo < consumo_medio) && ((*(Tralicci + i)).status == 1))
                {
                    numero_tralicci_ottimali++;
                } 
            }

            //ALLOCAZIONE E RIEMPIMENTO VETTORI
            Tralicci_Ottimali = new Traliccio[numero_tralicci_ottimali];
            Tralicci_Non_Ottimali = new Traliccio[numero_tralicci_non_ottimali];
            if ((Tralicci_Ottimali == NULL) || (Tralicci_Non_Ottimali == NULL))
            {
                cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma." << endl;
                exit(1);
            }
            numero_tralicci_ottimali = 0;
            numero_tralicci_non_ottimali = 0;
            for (int i = 0; i < numero_tralicci; i++)
            {
                if (((*(Tralicci + i)).consumo > consumo_medio) && ((*(Tralicci + i)).status == 1))
                {
                    *(Tralicci_Non_Ottimali + numero_tralicci_non_ottimali) = *(Tralicci + i);
                    numero_tralicci_non_ottimali++;
                }
                if (((*(Tralicci + i)).consumo < consumo_medio) && ((*(Tralicci + i)).status == 1))
                {
                    *(Tralicci_Ottimali + numero_tralicci_ottimali) = *(Tralicci + i);
                    numero_tralicci_ottimali++;
                } 
            }

        }
    }
    
}

void ricerca_tralicci_attivi(PTral Tralicci, int numero_tralicci, PTral& Tralicci_Attivi) {
    //DICHIARAZIONI DI VARIABILI UTILI
    int numero_tralicci_attivi = 0;

    //DETERMINAZIONE NUMERO TRALICCI ATTIVI
    for (int i = 0; i < numero_tralicci; i++)
    {
        if ((*(Tralicci + i)).status == 1)
        {
            numero_tralicci_attivi++;
        }
    }

    //CREAZIONE VETTORE TRALICCI ATTIVI
    switch (numero_tralicci_attivi)
    {
    case 0:
        cout << "[WARNING]Nessun traliccio attivo." << endl;
        break;

    case 1:
        cout << "[WARNING]Unico traliccio attivo trovato:" << endl;
        for (int i = 0; i < numero_tralicci; i++)
        {
            if ((*(Tralicci + i)).status == 1)
            {
                cout << "[ID] " << (*(Tralicci + i)).id << endl;
                cout << "[CONSUMO] " << (*(Tralicci + i)).consumo << " kW" << endl;
                cout << "[STATUS] ATTIVO" << endl << endl;
            }
        }
        break;

    case 2:
        cout << "[WARNING]Due tralicci attivi trovati." << endl;
        for (int i = 0; i < numero_tralicci; i++)
        {
            if ((*(Tralicci + i)).status == 1)
            {
                cout << "[ID] " << (*(Tralicci + i)).id << endl;
                cout << "[CONSUMO] " << (*(Tralicci + i)).consumo << " kW" << endl;
                cout << "[STATUS] ATTIVO" << endl << endl;
            }
        }
        break;

    case 3:
        cout << "[WARNING]Tre tralicci attivi trovati." << endl;
        for (int i = 0; i < numero_tralicci; i++)
        {
            if ((*(Tralicci + i)).status == 1)
            {
                cout << "[ID] " << (*(Tralicci + i)).id << endl;
                cout << "[CONSUMO] " << (*(Tralicci + i)).consumo << " kW" << endl;
                cout << "[STATUS] ATTIVO" << endl << endl;
            }
        }
        break;
    
    default: //QUALORA SIA PRESENTE UN NUMERO >= 4 DI TRALICCI ATTIVI BISOGNA ORDINARLI PER DETERMINARE I TRE CHE CONSUMANO MAGGIORMENTE
        
        //ALLOCAZIONE E RIEMPIMENTO ARRAY DI TRALICCI ATTIVI
        Tralicci_Attivi = new Traliccio[numero_tralicci_attivi];
        if (Tralicci_Attivi == NULL)
        {
            cout << "[ERRORE]Memoria insufficiente per una corretta esecuzione del programma." << endl;
            exit(1);
        }
        numero_tralicci_attivi = 0;
        for (int i = 0; i < numero_tralicci; i++, cout << endl)
        {
            if ((*(Tralicci + i)).status == 1)
            {
                *(Tralicci_Attivi + numero_tralicci_attivi) = *(Tralicci + i);
                numero_tralicci_attivi++;
            }
        }

        //ORDINAMENTO VETTORE DI TRALICCI ATTIVI
        int pos_max;
        Traliccio temp;
        for (int i = 0; i < numero_tralicci_attivi - 1; i++)
        {
            pos_max = i;
            for (int j = i+1; j < numero_tralicci_attivi; j++)
            {
                if ((*(Tralicci_Attivi + j)).consumo > (*(Tralicci_Attivi + pos_max)).consumo)
                {
                    pos_max = j;
                }
                temp = *(Tralicci_Attivi + pos_max);
                *(Tralicci_Attivi + pos_max) = *(Tralicci_Attivi + i);
                *(Tralicci_Attivi + i) = temp;
            }
        }
        
        break;
    }

}
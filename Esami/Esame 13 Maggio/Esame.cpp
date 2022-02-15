#include <iostream>
#include <fstream>
using namespace std;

//TIPI ED ALIAS UTILI
struct Triangolo{
    float l1;
    float l2;
    float l3;
};
typedef Triangolo* PTrian;

//PROTOTIPI
void creazione_vettore_triangoli(PTrian&, int&);
void stampa_vettore_triangoli(PTrian, int);
void conteggio_tipologie_triangoli (PTrian, int);
void ordinamento_vettore_triangoli(PTrian&, const int&);

int main() {
    //DICHIARAZIONI VARIABILI UTILI
    PTrian Triangoli = NULL;
    int numero_triangoli = 0;

    //CHIAMATE FUNZIONI
    creazione_vettore_triangoli(Triangoli, numero_triangoli);
    cout << "[INFO]Elenco dei triangoli nel file:" << endl;
    stampa_vettore_triangoli(Triangoli, numero_triangoli);

    conteggio_tipologie_triangoli(Triangoli, numero_triangoli);

    ordinamento_vettore_triangoli(Triangoli, numero_triangoli);
    cout << "[INFO]Elenco dei triangoli ordinati per perimetro crescente:" << endl;
    stampa_vettore_triangoli(Triangoli, numero_triangoli);
}

void creazione_vettore_triangoli(PTrian& Triangoli, int& numero_triangoli) {
    //DICHIARAZIONI VARAIBILI UTILI
    ifstream file;

    //CONTEGGIO NUMERO DEI TRIANGOLI
    file.open("triangoli.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile aprire il file contenente l'elenco dei triangoli. Terminazione del programma";
    }
    while (!file.eof())
    {
        numero_triangoli++;
        file.ignore(100, '\n');
    }
    file.close();

    //ALLOCAZIONE E RIEMPIMENTO VETTORE
    Triangoli = new Triangolo[numero_triangoli];
    numero_triangoli = 0;
    file.open("triangoli.txt", ios::in);
    if (!file)
    {
        cout << "[ERRORE]Impossibile aprire il file contenente l'elenco dei triangoli. Terminazione del programma";
    }
    while (!file.eof())
    {
        file >> (*(Triangoli + numero_triangoli)).l1;
        file >> (*(Triangoli + numero_triangoli)).l2;
        file >> (*(Triangoli + numero_triangoli)).l3;
        numero_triangoli++;
    }
    file.close();

}

void stampa_vettore_triangoli(PTrian Triangoli, int numero_triangoli) {
    //STAMPA VETTORE
    for (int i = 0; i < numero_triangoli; i++, cout << endl)
    {
        cout << "Triangolo " << i+1 << ":" << endl;
        cout << "[LATO 1]--->" << (*(Triangoli + i)).l1 << endl;
        cout << "[LATO 2]--->" << (*(Triangoli + i)).l2 << endl;
        cout << "[LATO 3]--->" << (*(Triangoli + i)).l3 << endl;
    }
    
}

void conteggio_tipologie_triangoli (PTrian Triangoli, int numero_triangoli) {
    //DICHIARAZIONI VARIABILI UTILI
    int numero_equilateri = 0, numero_isosceli = 0, numero_scaleni = 0, numero_rettangoli = 0, numero_rettangoli_isosceli = 0;
    float l1 = 0.0, l2 = 0.0, l3 = 0.0; 

    //CONTEGGIO TIPOLOGIE
    for (int i = 0; i < numero_triangoli; i++)
    {
        l1 = (*(Triangoli + i)).l1;
        l2 = (*(Triangoli + i)).l2;
        l3 = (*(Triangoli + i)).l3;
        
        if ( l1 != l2 && l2 != l3 && l3 != l1) //SCALENO
        {
            numero_scaleni++;
            if ( ( (l1*l1 + l2*l2) == l3*l3 ) ||  ( (l2*l2 + l3*l3) == l1*l1 ) ||  ( (l3*l3 + l1*l1) == l2*l2 ) ) //RETTANGOLO 
            {
                numero_rettangoli++;
            }
            
        } else //SCALENO
        {
            if (l1 == l2 && l2 == l3 && l3 == l1) //EQUILATERO
            {
                numero_equilateri++;
            } else // NON SCALENO, NON EQUILATERO ---> ISOSCELE
            {
                numero_isosceli++;
                if ( ( (l1*l1 + l2*l2) == l3*l3 ) ||  ( (l2*l2 + l3*l3) == l1*l1 ) ||  ( (l3*l3 + l1*l1) == l2*l2 ) ) //RETTANGOLO, ISOSCELE --> RETTANGOLO ISOSCELE
                {
                    numero_rettangoli_isosceli++;
                }
            }
        }  
    }

    //STAMPA RISULTATI CONTEGGIO
    cout << "[EQUILATERI]Nel file sono elencati " << numero_equilateri << " triangoli equilateri." << endl;
    cout << "[ISOSCELI]Nel file sono elencati " << numero_isosceli << " triangoli isosceli." << endl;
    cout << "[SCALENI]Nel file sono elencati " << numero_scaleni << " triangoli scaleni." << endl;
    cout << "[RETTANGOLI]Nel file sono elencati " << numero_rettangoli << " triangoli rettangoli." << endl;
    cout << "[RETTANGOLI ISOSCELI]Nel file sono elencati " << numero_rettangoli_isosceli << " triangoli rettangoli isosceli." << endl << endl;
    
}

void ordinamento_vettore_triangoli(PTrian& Triangoli, const int& numero_triangoli) {
    //DICHIARAZIONI VARIABILI UTILI
    int pos_min = 0;
    float perimetro_min = 0.0, perimetro = 0.0;
    Triangolo temp;;

    //ORDINAMENTO
    for (int i = 0; i < numero_triangoli - 1; i++)
    {
        pos_min = i;
        perimetro_min = (*(Triangoli + i)).l1 + (*(Triangoli + i)).l2 + (*(Triangoli + i)).l3;
        for (int j = i + 1; j < numero_triangoli; j++)
        {
            perimetro = (*(Triangoli + j)).l1 + (*(Triangoli + j)).l2 + (*(Triangoli + j)).l3;
            if (perimetro < perimetro_min)
            {
                pos_min = j;
                perimetro_min = perimetro;
            }
        }
        temp = *(Triangoli + pos_min);
        *(Triangoli + pos_min) = *(Triangoli + i);
        *(Triangoli + i) = temp;
    }
    
}
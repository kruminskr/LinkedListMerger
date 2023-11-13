/***************************************************************************************
G16. Uzrakstīt funkciju, kas iesprauž sarakstā aiz n-tā elementa
citu sarakstu. Darbības rezultātā nedrīkst izmainīties kopējais atmiņā
glabātais sarakstu elementu skaits. (Jābūt iespējai izveidot 2 sarakstus.)
******************************************************************************************/
///Kristiāns Krūmiņš kk22111
///Programma izstrādāta: 06.04.2023

#include <iostream>
#include<list>
using namespace std;

class Node {
public:
    int num;
    Node *next;

    Node (int n)
    {
        num = n;       //Konstruktors, lai inicializētu node ar datiem
        next = NULL;
    };
};

class List
{
public:
    Node *first, *last, *current;      // Norāda uz pirmo, pēdējo un pašreizējo node sarakstā

    List ()
    {
        first = last = current = NULL;         // Konstruktors, lai inicializētu sarakstu ar NULL rādītājiem
    };
    void add_element (int n);                 // Funkcija, lai saraksta beigās pievienotu elementu

    void delete_element ();                    // Funkcija pašreizējā elementa dzēšanai no saraksta

    bool is_empty (){
        return (first == NULL);                 // Funkcija, lai pārbaudītu, vai saraksts ir tukšs
    };
    void start (){
        current = first;                              // Funkcija, lai iestatītu pašreizējā node rādītāju uz pirmo node
    };
    bool end (){
        return (current == NULL);             // Funkcija, lai pārbaudītu, vai pašreizējā node rādītājs ir NULL
    };
    void next(){
        if (!end())current = current -> next;           // Funkcija, lai pārvietotu pašreizējā node rādītāju uz nākamo node
    };
    void insert_list(int z,Node *pirmais, Node *&pedejais);          // Funkcija ievietot jaunu sarakstu norādītajā vietā
};
/***********************************************************
int main()
Funkcija main
Pieprasa lietotājam ievadīt pirmā,otrā saraksta vērtības
un n-to elementu, aiz kura iespraust otro sarakstu
***********************************************************/
int main() {
    int ok;
    List saraksts1;
    List saraksts2;                      //Deklērē abus sarakstus un visus mainīgos
    int elem, part;
    int gar1 = 1;
    int gar2 = 1;

    do {
        cout << "Ievadiet pirmā saraksta " << gar1 << " elementu: ";
        cin >> elem;
        if (elem == 0) {
            cout << "Ievadiet vismaz vienu vērtību, kura ir lielāka par 0" << endl;
        }
    } while (elem == 0);
    do {                                                                                                                                  //Prasa lietotājam ievadīt pirmā saraksta elementus
        saraksts1.add_element(elem);                                                                                        //un paziņo par kļūdu ievadē
        cout << "Ievadiet pirmā saraksta " << gar1 + 1 << " elementu (0 lai pārtrauktu ievadi): ";
        cin >> elem;
        ++gar1;
    } while (elem != 0);

    do {
        cout << "Ievadiet otrā saraksta " << gar2 << " elementu: ";
        cin >> elem;
        if (elem == 0) {
            cout << "Ievadiet vismaz vienu vērtību, kura ir lielāka par 0" << endl;
        }
    } while (elem == 0);                                                                                                           //Prasa lietotājam ievadīt otrā saraksta elementus
    do {                                                                                                                                  //un paziņo par kļūdu ievadē
        saraksts2.add_element(elem);
        cout << "Ievadiet otrā saraksta " << gar2 + 1 << " elementu (0 lai pārtrauktu ievadi): ";
        cin >> elem;
        gar2++;
    } while (elem != 0);

    do {
        cout << "Ievadiet elementa numuru, aiz kura iespraust otro sarakstu : ";
        cin >> part;                                                                                                            //Prasa lietotājam ievadīt elementu aiz kura
        if (part <= 0 || part > gar1 - 1)                                                                                  //Iespraust otro sarakstu un paziņo par kļūdu ievadē
            cout << "Ievadiet vērtību, starp 0 un " << gar1 - 1 << endl;
    } while (part <= 0 || part > gar1 - 1);

        cout << endl;
    for (saraksts1.start(); !saraksts1.end(); saraksts1.next()) {     //Izvada sarakstu vērtības
        cout << saraksts1.current->num << ' ';
    }

        cout << endl;
    for (saraksts2.start(); !saraksts2.end(); saraksts2.next()) {     //Izvada sarakstu vērtības
        cout << saraksts2.current->num << ' ';
    }

    Node* p = saraksts2.first;              //piešķirt rādītāju p saraksts2 pirmajam node
    Node* pedejais_next = NULL;               // inicializē rādītāju pedejais_next uz NULL
    saraksts1.insert_list(part, p, pedejais_next);   //Nosūta datus uz funkciju inser_list
    if (pedejais_next) {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = pedejais_next;
    }

    cout << endl;
    for (saraksts1.start(); !saraksts1.end(); saraksts1.next()) {     //Izvada sarakstu vērtības
        cout << saraksts1.current->num << ' ';
    }

    while (!saraksts1.is_empty()) {         //izdzēš visas vērtības saraksts1
        saraksts1.delete_element();
    }
    while (!saraksts2.is_empty()) {         //izdzēš visas vērtības saraksts2
        saraksts2.delete_element();
    }
}

/*********************************************************
void List::add_element (int n)
Funkcija add_element
Pievieno sarakstam jaunu elementu
*********************************************************/
void List::add_element (int n){
    Node *p = new Node (n);
    if (first == NULL) first = last = p;
    else last = last -> next = p;
    current = p;
};
/*********************************************************
void List::delete_element(){
Funkcija delete_element
Izdzēš no saraksta elementu
*********************************************************/
void List::delete_element(){
    Node *p = first;
    if(!is_empty()){
        if (current == first) current = first-> next;
        first = first -> next;
        delete p;
        if(is_empty())last = NULL;
    };
};
/*********************************************************
void List::insert_list
Funkcija insert_list
Ievieto sarakstā aiz ievadītā n-tā elemnta jaunu elementu
*********************************************************/
void List::insert_list(int n, Node* p, Node*& pedejais_next) {
    current = first;
    if (n != 0) {
        for (int i = 0; i < n - 1; i++) {
            current = current->next;
        }
    }
    pedejais_next = current->next;
    current->next = p;
    current = p;
}
/****************************Testa Plāns*************************************
    Ievade                    Vēlamā atbilde                      Rezultāts
=================================================
1 2 3 4 0
5 6 7 8 0                     1 2 5 6 7 8 3 4                 1 2 5 6 7 8 3 4
2
=================================================
1 4 5 6 0
2 3 0              Tiks paziņots par kļūdu un prasīts           +
0                    lietotājam vēlreiz ievadīt vērtību
=================================================
0 99 54 1 0
101 0             Tiks paziņots par kļūdu un prasīts           +
1                    lietotājam vēlreiz ievadīt vērtību
*********************************************************************************/

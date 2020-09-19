#include <iostream>
#include <string>

using namespace std;

class Nod {
public:
    Nod() {
        info = "a";
        next = NULL;
        priority = 0;
    }

    Nod(string inf) : info(inf), next(nullptr) {};

    ~Nod() {

    };
    string info; // Am pus membru public din cauza functiei de supraincarcare a operatorului de afisare.
    friend class coada; // Pentru a putea folosi membr.ul privat next in metodele cerute.
    Nod *next;
    int priority;
};

class coada {
protected:
    Nod *first;
    Nod *last;
    int dim_maxima;
public:
    coada() : first(nullptr), last(nullptr), dim_maxima(0) {};

    /// Copy constructor
    coada(const coada &aux) {
        first = aux.first;
        last = aux.last;
    }

    int isempty() {
        if (first == nullptr) return 1;  // 1 daca stiva este goala.
        return 0;
    }

    // Functia Push pune un element in coada prin spate.
    virtual void push_back(string x) {
        if (isempty() == 1) {
            first = new Nod;
            first->info = x;
            first->next = last;
        } else if (last == nullptr) {
            last = new Nod;
            last->info = x;
            last->next = nullptr;
            first->next = last;
        } else {
            Nod *t = new Nod; // Pentru noul element adaugat in coada.
            t->info = x;
            t->next = nullptr;
            last->next = t;
            last = t;
        }
    }

    // Functia pop sterge primul element din coada
    virtual void pop_front() {
        if (isempty() == 1) return;
        if (first == last) { //1 singur element
            delete (first);
            first = nullptr;
            last = nullptr;
        } else {
            Nod *t = first;
            first = first->next;
            delete t;
        }
    }

    //Supraincarcare operatorului[] necesar la functionarea demoului
    /* char operator[](int i)
     {
         Nod *da=first;
         for(int aux=0;aux<=i;aux++)
             da = da->next;
         return da->next->info;
     }
 */
    void empty() {
        Nod *aux = first->next;
        while (this->isempty() != 1)
            this->pop_front();

    }

    // Supraincarcarea operatorului =
    coada &operator=(const coada &c1) {
        Nod *aux = c1.first; // Aux reprezinta un pointer la inceputul cozii folosit pentru a parcurge coada.
        while (aux != nullptr) {
            push_back(aux->info);
            aux = aux->next;
        }
    }


    virtual ~coada() {
        this->empty();
    }

    friend class Nod;

    friend ostream &operator<<(ostream &out, coada &z);

    friend istream &operator>>(istream &in, coada &z);
};

// Supraincarcarea operatorului <<
ostream &operator<<(ostream &out, coada &z) {
    Nod *aux = z.first;
    while (aux != NULL) {
        out << aux->info << " ";
        aux = aux->next;
    }
}

// Supraincarcarea operatorului >>
istream &operator>>(istream &in, coada &z) {
    string aux;
    in >> aux;
    z.push_back(aux);
}

class Deque : public coada {
public:
    Deque() {
        this->first = nullptr;
        this->last = nullptr;
    };

    Deque(const Deque &aux) {
        first = aux.first;
        last = aux.last;
    }

    virtual void pop_back() {
        if (isempty() == 1) return;
        if (first == last) { //1 singur element
            delete (first);
            first = nullptr;
            last = nullptr;
        } else {
            Nod *t = first;
            while (t->next != last)
                t = t->next;
            delete last;
            last = t;
        }
    }

    virtual void push_front(string x) {
        if (isempty() == 1) {
            first = new Nod;
            first->info = x;
            first->next = last;
        } else if (last == nullptr) {
            last = new Nod;
            last->info = first->info;
            last->next = nullptr;
            first->next = last;
            first->info = x;
        } else {
            Nod *t = new Nod; // Pentru noul element adaugat in coada.
            t->info = x;
            t->next = first;
            first = t;
        }
    }

    virtual string top() = 0;

    virtual ~Deque() {
        this->empty();
    };

};

class Deque_marcaj : public Deque {
public:
    Deque_marcaj() {
        this->first = nullptr;
        this->last = nullptr;
    }

    Deque_marcaj(const Deque_marcaj &aux) {
        first = aux.first;
        last = aux.last;
    }

    string top() {
        return first->info;
    }

    void insert(const string x, int prioritate) {
        if (this->isempty() == 1) {
            first = new Nod;
            first->info = x;
            first->priority = prioritate;
            first->next = last;
        } else if (last == nullptr) {
            last = new Nod;
            if (prioritate < first->priority) {
                last->info = first->info;
                last->priority = first->priority;
                last->next = nullptr;
                first->priority = prioritate;
                first->info = x;
                first->next = last;
            } else {
                last->info = x;
                last->next = nullptr;
                last->priority = prioritate;
            }
        } else {
            if (prioritate < first->priority) {
                Nod *aux = new Nod;
                aux->next = first;
                aux->info = x;
                aux->priority = prioritate;
                first = aux;

            } else if (prioritate > last->priority) {
                Nod *aux = new Nod;
                last->next = aux;
                aux->info = x;
                aux->priority = prioritate;
                aux->next = nullptr;
                last = aux;

            } else {
                Nod *t = first;
                while (prioritate > t->next->priority) {
                    t = t->next;

                }
                Nod *aux = new Nod;
                aux->info = x;
                aux->priority = prioritate;
                aux->next = t->next;
                t->next = aux;

            }
        }
    }

    ~Deque_marcaj() {
        this->empty();
    }


};

int main() {
    Deque_marcaj a;
    int alegere;
    cout << "Alegeti ce doriti sa faceti" << endl;
    cout << "1.Verificare daca coada este goala sau nu( *Afiseaza 1 daca da, 0 daca nu* )" << endl;
    cout << "2.Inserare" << endl;
    cout << "3.Golire coada( *Afiseara 1 daca s-a golit, 0 daca nu* )" << endl;
    cout << "4.Top" << endl;
    cout << "0.Exit" << endl;
    cin >> alegere;
    while (alegere >= 1 && alegere <= 4) {
        switch (alegere) {
            case 1: {

                if (a.isempty() == 1)cout << "lista este goala" << endl;
                else {
                    cout << "lista nu este goala" << endl;
                    cout << a;
                    cout << endl;
                }

                break;
            }
            case 2: {
                string cuv;
                int prioritate;
                cout << "Introduceti sirul de caractere dorit: ";
                cin >> cuv;
                cout << "Introduceti prioritatea dorita( *Numar mic -> prioritate mare *): ";
                cin >> prioritate;
                a.insert(cuv, prioritate);
                cout << a;
                cout << endl;

                break;
            }
            case 3: {
                a.empty();
                cout << a.isempty() << endl;
                break;
            }
            case 4: {
                if (a.isempty() == 1) cout << "lista este goala deci nu exista elementul top" << endl;
                else {
                    cout << a.top() << endl;
                    cout << a;
                    cout << endl;
                }
                break;
            }

        }

        cout << "Alegeti ce doriti sa faceti: " << endl;
        cout << "1.Verificare daca coada este goala sau nu" << endl;
        cout << "2.Inserare: " << endl;
        cout << "3.Golire coada( *Afiseara 1 daca s-a golit, 0 daca nu* ): " << endl;
        cout << "4.Top: " << endl;
        cout << "0.Exit";
        cout << endl;
        cin >> alegere;
    }

}

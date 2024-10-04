#include <iostream>

using namespace std;

struct nodo {
    nodo *eloa;
    string info;
    nodo *elop;
};

struct double_list {
    nodo *start;
    nodo *end;
    int size;
};

void clear_screen() {
    system("cls");
}

void wait() {
    system("pause");
}

void inicialization(double_list &dl) {
    dl.start = dl.end = NULL;
    dl.size = 0;
}

bool include_end(double_list &dl, string value) {
    nodo *novo;
    novo = new nodo;

    if (novo == NULL) {
        return false;
    }

    novo -> info = value;
    novo -> eloa = NULL;
    novo -> eloa = dl.end;

    if (dl.start == NULL) {
        dl.start = novo;
    } else {
        dl.end -> elop = novo;
    }

    dl.end = novo;
    dl.size++;
    return true;
}

bool include_beginning(double_list &dl, string value) {
    nodo *novo = new nodo;

    if (novo == NULL) {
        return false;
    }

    novo -> info = value;
    novo -> eloa = NULL;
    novo -> elop = dl.start;

    if (dl.start == NULL) {
        dl.end = novo;
    } else {
        dl.start -> eloa = novo;
    }

    dl.start = novo;
    dl.size++;
    return true;
}

bool include_before(double_list &dl, string target_value, string new_value) {
    if (dl.start == NULL) {
        return false; // Lista está vazia
    }

    nodo *novo = new nodo;
    if (novo == NULL) {
        return false; // Falha ao alocar memória
    }
    
    novo->info = new_value;

    nodo *current = dl.start;
    nodo *previous = NULL;

    // Procurar o valor na lista
    while (current != NULL && current->info != target_value) {
        previous = current;
        current = current->elop;
    }

    // Se o valor não foi encontrado
    if (current == NULL) {
        delete novo;
        return false;
    }

    // Se o valor foi encontrado, inserir antes dele
    novo->elop = current;
    novo->eloa = previous;

    if (previous == NULL) { // Inserção no início
        dl.start = novo;
    } else {
        previous->elop = novo;
    }

    current->eloa = novo;
    dl.size++;
    return true;
}

void show(double_list dl) {
    nodo *it = dl.start;

    cout << endl << endl;

    while (it != NULL) {
        cout << "- " << it -> info << endl;
        it = it -> elop;
    }
}

int main () {
    double_list dl;
    char option;
     string value, target_value;

    inicialization(dl);

    while (true) {
        cout << "---------- MENU ----------" << endl;
        cout << "I - Add to Beginning of List" << endl; 
        cout << "F - Add to End of List" << endl; 
        cout << "V - Include Before a Certain Value" << endl; 
        cout << "A - Show Full List" << endl;
        cout << "R - Remove a Value from the List" << endl;
        cout << "E - Empty the List" << endl;
        cout << "X - Exit" << endl;
        cout << endl;
        cout << "Enter your option: ";
        cin >> option;
        clear_screen();
  
        switch (option) {
            case 'I': 
            case 'i':
                cout << "Enter the value to be added to the beginning of the list: ";
                cin >> value;

                if (include_beginning(dl, value)) {
                    cout << "Inclusion at Beginning Made!" << endl;
                } else {
                    cout << "Error. Inclusion not carried out!" << endl;
                }
                wait();
                clear_screen();
                break;
           case 'F': 
           case 'f':
                cout << "Enter the value to be added to the list: ";
                cin >> value;

                if (include_end(dl, value)) {
                    cout << "Inclusion Made!" << endl;
                } else {
                    cout << "Error. Inclusion not carried out!" << endl;
                }
                wait();
                clear_screen();
                break;
            case 'V': 
            case 'v':
                cout << "Enter the value to insert before: ";
                cin >> target_value;
                cout << "Enter the new value to be inserted: ";
                cin >> value;

                if (include_before(dl, target_value, value)) {
                    cout << "Inclusion Made Before " << target_value << "!" << endl;
                } else {
                    cout << "Error. Inclusion not carried out!" << endl;
                }
                wait();
                clear_screen();
                break;
            case 'A': 
            case 'a':
                if (dl.start == NULL) {
                    cout << "Your list is empty!" << endl;
                    wait();
                    clear_screen();
                } else {
                    clear_screen();
                    show(dl);
                    wait();
                    clear_screen();
                }
                break;
           case 'R': 
           case 'r':
                cout << "Nothing to show for now" << endl;
                break;
            case 'E': 
            case 'e':
                cout << "Nothing to show for now" << endl;
                break;
            case 'X': 
            case 'x':
                cout << "Thank you for using the program!" << endl;
                cout << endl;
                wait();
                clear_screen();
                return 0;
            default:
                clear_screen();
                cout << "Invalid answer, please select an option from 1 to 7." << endl;
                cout << endl;
                wait();
                clear_screen();
                break;
        }
    }
    return 0;
}
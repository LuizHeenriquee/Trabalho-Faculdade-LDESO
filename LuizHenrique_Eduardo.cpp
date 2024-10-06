#include <iostream>

using namespace std;

struct nodo
{
    nodo *eloa;
    string info;
    nodo *elop;
};

struct double_list
{
    nodo *start;
    nodo *end;
    int size;
};

void clear_screen()
{
    system("cls");
}

void wait()
{
    system("pause");
}

void inicialization(double_list &dl)
{
    dl.start = dl.end = NULL;
    dl.size = 0;
}

bool include_end(double_list &dl, string value)
{
    nodo *novo = new nodo;

    if (novo == NULL)
    {
        return false;
    }

    novo->info = value;
    novo->eloa = dl.end;
    novo->elop = NULL;

    if (dl.start == NULL)
    {
        dl.start = novo;
    }
    else
    {
        dl.end->elop = novo;
    }

    dl.end = novo;
    dl.size++;
    return true;
}

bool include_beginning(double_list &dl, string value)
{
    nodo *novo = new nodo;

    if (novo == NULL)
    {
        return false;
    }

    novo->info = value;
    novo->eloa = NULL;
    novo->elop = dl.start;

    if (dl.start == NULL)
    {
        dl.end = novo;
    }
    else
    {
        dl.start->eloa = novo;
    }

    dl.start = novo;
    dl.size++;
    return true;
}

bool include_before(double_list &dl, string target_value, string new_value)
{
    if (dl.start == NULL)
    {
        return false;
    }

    nodo *novo = new nodo;
    if (novo == NULL)
    {
        return false;
    }

    novo->info = new_value;

    nodo *current = dl.start;
    nodo *previous = NULL;

    while (current != NULL && current->info != target_value)
    {
        previous = current;
        current = current->elop;
    }

    if (current == NULL)
    {
        delete novo;
        return false;
    }

    novo->elop = current;
    novo->eloa = previous;

    if (previous == NULL)
    {
        dl.start = novo;
    }
    else
    {
        previous->elop = novo;
    }

    current->eloa = novo;
    dl.size++;
    return true;
}

void show(double_list dl)
{
    nodo *it = dl.start;

    while (it != NULL)
    {
        cout << "- " << it->info << endl;
        it = it->elop;
    }
    cout << endl;
}

bool remove_value(double_list &dl, string value)
{
    nodo *it = dl.start;

    while (it != NULL && it->info != value)
    {
        it = it->elop;
    }

    if (it == NULL)
    {
        return false;
    }

    if (it->eloa != NULL)
    {
        it->eloa->elop = it->elop;
    }
    else
    {
        dl.start = it->elop;
    }

    if (it->elop != NULL)
    {
        it->elop->eloa = it->eloa;
    }
    else
    {
        dl.end = it->eloa;
    }

    delete it;
    dl.size--;
    return true;
}

void clear_list(double_list &dl)
{
    nodo *it = dl.start;

    while (it != NULL)
    {
        cout << "Removing: " << it->info << endl;
        nodo *next = it->elop;
        delete it;
        it = next;
        dl.size--;
    }

    dl.start = dl.end = NULL;
}

int main()
{
    double_list dl;
    char option;
    string value, target_value;

    inicialization(dl);

    while (true)
    {
        cout << "---------- MENU ----------" << endl;
        cout << "1 - Add to Beginning of List" << endl;
        cout << "2 - Add to End of List" << endl;
        cout << "3 - Include Before a Certain Value" << endl;
        cout << "4 - Show Full List" << endl;
        cout << "5 - Remove a Value from the List" << endl;
        cout << "6 - Empty the List" << endl;
        cout << "7 - Exit" << endl;
        cout << endl;
        cout << "Enter your option: ";
        cin >> option;
        clear_screen();

        switch (option)
        {
        case '1':
            cout << "Enter the value to be added to the list: ";
            cin >> value;

            if (include_beginning(dl, value))
            {
                cout << "Inclusion Made!" << endl;
            }
            else
            {
                cout << "Error. Inclusion not carried out!" << endl;
            }
            wait();
            clear_screen();
            break;
        case '2':
            cout << "Enter the value to be added to the list: ";
            cin >> value;

            if (include_end(dl, value))
            {
                cout << "Inclusion Made!" << endl;
            }
            else
            {
                cout << "Error. Inclusion not carried out!" << endl;
            }
            wait();
            clear_screen();
            break;
        case '3':
            if (dl.start == NULL)
            {
                cout << "The list is empty! No values to insert before." << endl;
            }
            else
            {
                cout << "Current list:" << endl;
                show(dl);

                cout << "Enter the value to insert before: ";
                cin >> target_value;
                cout << "Enter the new value to be inserted: ";
                cin >> value;

                if (include_before(dl, target_value, value))
                {
                    cout << "Inclusion Made Before '" << target_value << "'!" << endl;
                }
                else
                {
                    cout << "Error. Inclusion not carried out!" << endl;
                }
            }
            wait();
            clear_screen();
            break;

        case '4':
            if (dl.start == NULL)
            {
                cout << "Your list is empty!" << endl;
                wait();
                clear_screen();
            }
            else
            {
                clear_screen();
                show(dl);
                wait();
                clear_screen();
            }
            break;
        case '5':
            if (dl.start == NULL)
            {
                cout << "The list is empty, nothing to remove!" << endl;
            }
            else
            {
                cout << "Current list:" << endl;
                show(dl);

                bool removed = false;
                while (!removed)
                {
                    cout << "Enter the value to be removed: ";
                    cin >> value;

                    if (remove_value(dl, value))
                    {
                        cout << "Value removed!" << endl;
                        removed = true;
                    }
                    else
                    {
                        cout << "Value not found! Please try again." << endl;
                    }
                }
            }
            wait();
            clear_screen();
            break;
        case '6':
            if (dl.start == NULL)
            {
                cout << "The lis is already empty!" << endl;
            }
            else
            {
                clear_list(dl);
                cout << "List emptied!" << endl;
            }
            wait();
            clear_screen();
            break;
        case '7':
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
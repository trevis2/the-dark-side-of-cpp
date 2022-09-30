
#include <iostream>
using namespace std;

string *addItem(string item, string list[])
{
    string todolist[sizeof(list) + 1];
    for (int i = 0; i < sizeof(list); i++)
    {
        todolist[i] = list[i];
    }
    todolist[sizeof(list) + 1] = item;
    return todolist;
}

int main(int argc, char **argv)
{
    cout << "Questo Programma gestisce una todo list " << std::endl;
    cout << "Puoi aggiungere un oggetto o rimuoverlo selezionando + o - " << std::endl;

    string todolist[1] = {"vuoto"};
    cout << "La lista è:" << std::endl;
    for (int i = 0; i < sizeof(todolist); i++)
    {
        cout << i << " - " << todolist[i] << std::endl;
    }

    while (true)
    {
        std::cout << "Seleziona + o - " << std::endl;
        string i;
        cin >> i;
        if (i == "+" || i == "-")
        {
            break;
        }
    };
    return 0;
}


#include <iostream>
#include <vector>

void StampaListaInConsole(std::vector<std::string> lista)
{
    std::cout << "La Lista contiene " << lista.size() << " elementi" << std::endl;
    std::cout << "Lista:" << std::endl;
    for (int i = 0; i < lista.size(); i++)
    {
        std::cout << i << " - ";
        std::cout << lista[i] << std::endl;
    }
};

std::vector<std::string> InserisciElemento(std::vector<std::string> lista)
{
    std::cout << "digita l'elemento da inserire:" << std::endl;
    std::string item;
    std::cin >> item;
    lista.push_back(item);
    return lista;
};

std::vector<std::string> RimuoviElemento(std::vector<std::string> lista, int i)
{
    vector::iterator q = lista.begin();
    for (; q < i; q++)
    {
        // yes
    }

    vector::iterator p = vtr.erase(q);
};

int main(int argc, char **argv)
{
    std::cout << "Questo Programma gestisce una todo list. Puoi aggiungere un oggetto o rimuoverlo selezionando + o -, per uscire premi ESC " << std::endl;

    std::vector<std::string> todolist;
    while (true)
    {
        if (todolist.size() == 0)
        {
            std::cout << "La Lista è vuota! inserisci il primo elemento:" << std::endl;
            std::string item;
            std::cin >> item;
            todolist.push_back(item);
        }
        else
        {
            StampaListaInConsole(todolist);
            std::cout << "Inserisci '+' per aggiungere o '-' per rimuovere" << std::endl;
            std::string j;
            std::cin >> j;
            std::cout << "hai inserito: " << j << std::endl;
            if (j == "+")
            {
                todolist = InserisciElemento(todolist);
            }
            else if (j == "-")
            {
                std::cout << "seleziona la posizione dell'elemento che vuoi rimuovere:" << std::endl;
                int k;
                std::cin >> k;
                todolist = RimuoviElemento(todolist, k);
            }
        }
    }
}

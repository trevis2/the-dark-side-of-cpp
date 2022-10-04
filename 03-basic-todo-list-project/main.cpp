
#include <iostream>
#include <iterator>
#include <vector>

void StampaListaInConsole(std::vector<std::string> lista)
{
    std::cout << std::endl;
    if (lista.size() == 0)
    {
        std::cout << "--- La Lista è vuota! ---" << std::endl;
    }
    else if (lista.size() == 1)
    {
        std::cout << "--- La Lista contiene 1 elemento ---" << std::endl;
        std::cout << 0 << " - ";
        std::cout << lista[0] << std::endl;
    }
    else
    {

        std::cout << "--- La Lista contiene " << lista.size() << " elementi ---" << std::endl;
        std::cout << "Lista:" << std::endl;
        for (int i = 0; i < lista.size(); i++)
        {
            std::cout << i << " - ";
            std::cout << lista[i] << std::endl;
        }
    }
    std::cout << std::endl;
};

std::vector<std::string> InserisciElemento(std::vector<std::string> lista)
{
    std::cout << "*** MODE INSERIMENTO ***" << std::endl;
    std::cout << "digita il testo del task da inserire:" << std::endl;
    std::string item;
    std::getline(std::cin, item);
    lista.push_back(item);
    return lista;
};

std::vector<std::string> RimuoviElemento(std::vector<std::string> lista)
{
    using namespace std;
    cout << "*** MODE RIMOZIONE ***" << endl;
    cout << "seleziona la posizione dell'elemento che vuoi rimuovere:" << endl;
    int k;
    cin >> k;

    vector<string>::iterator q = lista.begin();
    advance(q, k);
    vector<string>::iterator p = lista.erase(q);
    return lista;
};

int main(int argc, char **argv)
{
    std::cout << "Questo Programma gestisce una todo list. Puoi aggiungere un oggetto o rimuoverlo selezionando + o -, per uscire premi ESC " << std::endl;

    std::vector<std::string> todolist;
    while (true)
    {
        StampaListaInConsole(todolist);
        std::cout << "Inserisci '+' per aggiungere o '-' per rimuovere un task, per uscire x" << std::endl;
        std::string j;
        std::getline(std::cin, j);
        if (j == "+")
        {
            todolist = InserisciElemento(todolist);
        }
        else if (j == "-")
        {
            todolist = RimuoviElemento(todolist);
        }
        else if (j == "x")
        {
            std::exit(0);
        }
    }
}

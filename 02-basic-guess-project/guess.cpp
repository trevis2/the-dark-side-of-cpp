#include <iostream>

using std::cin;
using std::cout;

void main()
{
    cout << "Ciao indovina i 3 numeri \n";
    int PrimoNum = 3;
    int SecondoNum = 9;
    int TerzoNum = 5;

    int SommaNum = PrimoNum + SecondoNum + TerzoNum;
    cout << "Indizio: \"la somma di tutti i numeri e'\" : " << PrimoNum + SecondoNum + TerzoNum << "\n";
    cout << "Regola Generale non provare ad inserire caratteri!! Solo numeri per favore :P \n";
    while (true)
    {
        int a, b, c;
        cout << "Inserisci il primo numero: \n";
        cin >> a;
        cout << "Inserisci il secondo numero: \n";
        cin >> b;
        cout << "Inserisci il terzo numero: \n";
        cin >> c;
        int somma = a + b + c;
        if (somma == SommaNum)
        {
            cout << "Accidenti sei forte!! bravo \n";
            cout << "La somma e' :" << somma << "\n";
            break;
        }
        else
        {
            cout << "Non ci siamo proprio riprova!!! \n";
        }
    }
    cout << "Alla Prossima!";
}
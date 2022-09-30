#include <iostream>
#include <limits>

using namespace std;

void getIntFromCin(int &value) {
  while((cin >> value) == false) {
  	cin.clear();
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cout << "Invalid input. Try again: ";
  }
}

int main()
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
	      getIntFromCin(a);
        cout << "Inserisci il secondo numero: \n";
        getIntFromCin(b);
        cout << "Inserisci il terzo numero: \n";
        getIntFromCin(c);
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
    return 0;
}

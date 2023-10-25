#include <iostream>

using namespace std;

int main()
{
    float prezzo;
    float sconto;
    cout << "Inserisci il prezzo dei tuoi totale dei tuoi acquisti: €";
    cin >> prezzo;

    if (prezzo < 50)
    {
        sconto = 10.0 / 100;
    }
    else if (prezzo > 50 && prezzo < 100)
    {
        sconto = 20.0 / 100;
    }
    else if (prezzo > 100)
    {
        sconto = 30.0 / 100;
    }
    prezzo -= (prezzo * sconto);
    cout << "Sul vostro acqiusto e' stato applicato uno sconto del " << sconto * 100 << "% Il prezzo scontato è: " << prezzo << "€" << endl;
}
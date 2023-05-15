#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

float obliczMoment(const std::vector<float>& dane, int rz¹d)
{
    float moment = 0.0f;
    int n = dane.size();

    for (int i = 0; i < n; ++i) {
        moment += pow(dane[i], rz¹d);
    }

    moment /= n;
    return moment;
}
float obliczMomentCentralny(const std::vector<float>& dane,int rz¹d)
{
    float momentZwykly1 = obliczMoment(dane, 1);

    float momentCentralny = 0.0f;
    int n = dane.size();

    for (int i = 0; i < n; ++i) {
        momentCentralny += pow(dane[i] - momentZwykly1, rz¹d);
    }

    momentCentralny /= n;
    return momentCentralny;
}
float obliczOdchylenieStandardowe(const std::vector<float>& dane)
{
    float moment2 = obliczMoment(dane, 2);
    float moment1 = obliczMoment(dane, 1);

    return sqrt(moment2 - pow(moment1, 2));
}

float obliczOdchyleniePrzecietne(const std::vector<float>& dane)
{
    float moment3 = obliczMoment(dane, 3);
    float moment2 = obliczMoment(dane, 2);
    float moment1 = obliczMoment(dane, 1);

    return cbrt(moment3 - 3 * moment2 * moment1 + 2 * pow(moment1, 3));
}

int main()
{
    std::ifstream plik("FileIn.txt");

    std::vector<float> dane;
    float wartosc;
    int liczbaWartosci = 100;

    for (int i = 0; i < liczbaWartosci; ++i) {
        if (!(plik >> wartosc)) {
            std::cerr << "Blad podczas wczytywania danych." << std::endl;
            return 1;
        }
        dane.push_back(wartosc);
    }

    plik.close();

    // Obliczanie momentów
    float momentZwykly1 = obliczMoment(dane, 1);
    float momentZwykly2 = obliczMoment(dane, 2);
    float momentCentralny1 = obliczMomentCentralny(dane, 1);
    float momentCentralny2 = obliczMomentCentralny(dane, 2);

    // Obliczanie odchyleñ
    float odchylenieStandardowe = obliczOdchylenieStandardowe(dane);
    float odchyleniePrzecietne = obliczOdchyleniePrzecietne(dane);

    // Wyœwietlanie wyników
    cout << "1. Momenty zwykle:\n";
    cout << "   1. rzad: " << momentZwykly1 << endl;
    cout << "   2. rzad: " << momentZwykly2 << endl;

    cout << "2. Momenty centralne:\n";
    cout << "   1. rzad: " << momentCentralny1 << endl;
    cout << "   2. rzad: " << momentCentralny2 << endl;

    cout << "3. Odchylenie standardowe: " << odchylenieStandardowe << endl;
    cout << "   Odchylenie przecietne: " << odchyleniePrzecietne << endl;

    return 0;
}



// 0) Znajdź pozycje zawierające najmniejszą wartość dla wejściowego ciągu liczb.
// 1) Posortuj wejściowy ciąg liczb. Musisz zastosować funkcję z podproblemu 0).
// 2) Znajdź długość euklidesową wektora (tzw. normę euklidesową), który podany został na wejściu jako ciąg liczb.
// 3) Znajdź odchylenie standardowe* dla wejściowego ciągu liczb. Musisz zastosować funkcję z podproblemu 2).
// 4) Zapisz podany wejściowy ciąg liczbowy w tablicy i odwróć go w miejscu (używając tylko wspominanej tablicy).

// TRUDNIEJSZE
// 5) Odpowiedz, czy liczba jest pierwsza.
// 6) Znajdź pole wielokąta wypukłego. Zapisz punkty jako tablicę struktur.
// 7) Rozwiąż równanie kwadratowe oraz sześcienne** (równanie kwadratowe jest za 50%).
// 8) Wyznacz wartość wyrażenia 1*2^2 + 2*3^2 + ... + n(n+1)^2 dla zadanego n.
// 9) Zlicz liczbę ustawionych bitów w liczbie naturalnej (unsigned).

/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void zamien(double *a, double *b);
int f0(int n, bool wypisz);
void f1(int n);
double f2(int n, bool wypisz);
void f3(int n);
void f4(int n);
void f5(int n);
void f6(int n);
void f7(int n);
void f8(int n);
void f9(int n);
void f10(int n);
/////////////////////////////////////////////////////////////////////////

// własna funkcja pomocnicza do zamiany wartości miejscami
// a nie tylko ich kopii (wskazniki)

void zamien(double *a, double *b)
{
    double tymczasowa = *a;
    *a = *b;
    *b = tymczasowa;
}

// struktura punktow - pp6
struct Punkt
{
    double x, y;
};

// glowna tablica, nie int bo 4 bajty double przechowuje 8 (dokladnosc liczb)
// double bo wiekszosc funkcji to dzialania mat

// poza main - globalna statyczna dla kazdej funkcji
double tablica_wejsciowa[50000];

/////////////////////////////////////////////////////////////////////////
// PODDPROBLEM 0

int f0(int n, bool wypisz)
{
    double min_wartosc = tablica_wejsciowa[0]; // przypisanie do indeksu0 pierwszej wartosci
    int ost_pozycja = 0;

    // sprawdza od indeksu pierwszego (w sensie drugi element)
    for (int i = 1; i < n; i++)
    {
        if (tablica_wejsciowa[i] < min_wartosc)
        {
            min_wartosc = tablica_wejsciowa[i];
            ost_pozycja = i;
        }
    }

    if (wypisz)
    {
        for (int i = 0; i < n; i++)
        {
            if (tablica_wejsciowa[i] == min_wartosc)
            {
                cout << i + 1 << " "; // wypisuje ludzki indeks
            }
        }
        cout << endl;
    }
    return ost_pozycja; // zwraca komputerowi normalny indeks (do pp1)
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 1

void f1(int n)
{
    int ilosc = n; // liczba liczb :)
    while (ilosc > 1)
    { // zabezpiecznie, gdyby byl tylko jeden element

        int min_pozycja = f0(ilosc, false); // stosuje funkcje z pp0, lecz nie wypisuje cout, stad false

        // f.pomocnicza zamiana najmniejszej z ostatnią
        // pobieranie adresu z tej funkcji globalnej
        zamien(&tablica_wejsciowa[min_pozycja], &tablica_wejsciowa[ilosc - 1]);

        ilosc--; // zmniejszam ilosc o jeden, bo ostatni element juz nie ruszam
    }

    for (int i = 0; i < n; i++)
    {
        cout << (int)tablica_wejsciowa[i] << " ";
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 2

double f2(int n, bool wypisz)
{ // zmienna double dla tej funkcji zeby zwracala wynik bo do odchylenia potrzebne :)
    double suma_kwadratow = 0;
    for (int i = 0; i < n; i++)
    {
        suma_kwadratow += tablica_wejsciowa[i] * tablica_wejsciowa[i];
    }

    double wynik = sqrt(suma_kwadratow);

    if (wypisz)
    {
        cout << (int)wynik << endl; // podloga
    }
    return wynik; // u gory cout jako int (podloga) a tutaj do odchylenia,zeby dokladnie pokazalo
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 3

void f3(int n)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += tablica_wejsciowa[i]; // suma calej tablicy
    }

    double srednia = suma / n;

    // korzystam z f2 ale nie wypisuje couta
    // NORMA -
    double norma = f2(n, false);
    double suma_kwadratow = norma * norma;
    // WARIANCJA
    double wariancja = (suma_kwadratow / n) - (srednia * srednia);
    // ODCHYLENIE
    double odchylenie;
    if (wariancja < 0)
    { // nie moze byc ujemne
        odchylenie = 0;
    }

    else
    {
        odchylenie = sqrt(wariancja);
    }

    // podłoga z odchylenia + mala liczba
    cout << (int)(odchylenie + 0.000001) << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 4

void f4(int n)
{
    // Odwracanie w miejscu
    for (int i = 0; i < n / 2; i++)
    { // rozdzielenie tablicy na pol i odwracanie parami
        // zamieniam element z poczatku z od konca
        zamien(&tablica_wejsciowa[i], &tablica_wejsciowa[n - 1 - i]);
    }

    // coucik odwrócona tablica
    for (int i = 0; i < n; i++)
    {
        cout << (int)tablica_wejsciowa[i] << " "; // podloga
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 5

void f5(int n)
{
    for (int i = 0; i < n; i++)
    {
        int liczba = (int)tablica_wejsciowa[i]; // dodanie int na tablice dla pewnosci bo jest double

        if (liczba < 2)
        {
            cout << "0 "; // 1, 0 i minusowe nie są pierwsze
            continue;     // kontynuacja do kolejnych liczb
        }

        bool czy_pierwsza = true;

        // metoda liczenia tlyko do pierwiastka z liczby czyli do
        // tzw. trial division up to sqrt , wzialem ze strony geeksforgeeks :)

        // bo jak nie znajde do pierwiastka to nie ma dzielnikow i nie ma sensu dalej leciec
        for (int j = 2; j <= sqrt(liczba); j++)
        {
            if (liczba % j == 0)
            {
                czy_pierwsza = false;
                break; // od razu break bo jeden dzielnik starczy
            }
        }

        if (czy_pierwsza)
        {
            cout << "1 ";
        }

        else
        {
            cout << "0 ";
        }
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 6

void f6(int n)
{
    int liczba_punktow = n / 2; // rozdzielenie na ilosc par x,y

    // tablica struktur Punkt + korzystac bede ze wzorku Gaussa
    Punkt p[1000];
    for (int i = 0; i < liczba_punktow; i++)
    {
        p[i].x = tablica_wejsciowa[2 * i];     // indexy X
        p[i].y = tablica_wejsciowa[2 * i + 1]; // indexy Y
    }

    long double pole = 0;

    // wzor gaussa
    for (int i = 0; i < liczba_punktow; i++)
    {
        // j to indeks następnego punktu (dla ostatniego punktu j to 0)
        int j = (i + 1) % liczba_punktow; // modulo tutaj
        // poniewaz lączony jest ostatni punkt wspolrz z pierwszym punktem by zamknac figure
        // i jak np. i=3 - ostatni punkt - to i+1 % 3 to 0 czyli przerzuca do pierwszego punktu i konczy

        // mnożenie na krzyż wzorem Gaussa
        pole += (p[i].x * p[j].y); // dodatnie sznurowadla wsporzednych
        pole -= (p[j].x * p[i].y); // ujemne -||-
    }

    // wartość bezwzględną(bo pole) i przez 2
    long double wynik_finalny = abs(pole) / 2;

    // daje podloge ale dodaje 0.00001 bo nie przechodzilo w niektorych testach
    cout << (long long)(wynik_finalny + 0.00001) << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 7

void f7(int n)
{

    for (int i = 0; i < n; i += 4)
    { // i+=4 bo pierwszy wyraz to x^3

        double a = tablica_wejsciowa[i + 1]; // kwadrat (x^2)
        double b = tablica_wejsciowa[i + 2]; // x^1
        double c = tablica_wejsciowa[i + 3]; // w.wolny

        double delta = (b * b) - (4 * a * c);

        if (delta < 0)
        {
            continue;
        }
        // daje 0.000001 bo np. 0.000000000001 (bliska zero) stos bierze jako zero
        else if (abs(delta) < 0.000001)
        { // jedno rozw
            double x = -b / (2 * a);
            cout << (int)x << " ";
        }
        else
        { // dwa rozw
            double pierwiastek = sqrt(delta);
            double x1 = (-b - pierwiastek) / (2 * a);
            double x2 = (-b + pierwiastek) / (2 * a);

            // przypisanie mniejszego iksa na poczatek
            if (x1 > x2)
            {
                double chwilowa = x1;
                x1 = x2;
                x2 = chwilowa;
            }
            cout << floor(x1) << " " << floor(x2) << " "; // podloga floor bo wywalalo inne wyniki
        }
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 8

void f8(int n)
{
    for (int i = 0; i < n; i++)
    {
        long long k = (long long)tablica_wejsciowa[i];

        if (k < 1)
        { // sprawdzanie czy wgl mozna zaczac liczenie
            cout << 0 << endl;
            continue;
        }

        // stosuje wzor na sume trzech szeregow bo standardowy wzorek >0.2 sekundy
        long long wynik = (k * (k + 1) * (k + 2) * (3 * k + 5)) / 12;
        // long long bo duze liczby na stosie
        cout << wynik << " ";
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////
// PODPROBLEM 9 - sposob 1

void f10(int n)
{
    // liczym bity dla kazdej liczby tablicy
    for (int i = 0; i < n; i++)
    {
        unsigned int liczba = (unsigned int)tablica_wejsciowa[i]; // unsigned bo dodatnie tylko
        int licznik = 0;

        while (liczba > 0)
        { // petla while dopoki nie bedzie binarnych jedynek
            // sprawdzam czy ostatni bit to 1, jesli tak to dodawany jest do licznika
            licznik += (liczba & 1); // operacja AND - sprawdzanie ostatniego bitu
            // czyli po porstu mnozenie go przez 1 . jesli jest 1 to licznik sie dodaje
            // jesli 0 to nic nie robi
            liczba >>= 1; // wyrzucam ostatni bit i dalej
        }
        cout << licznik << " ";
    }
    cout << endl;
}
///////////////////
// PODPROBLEM 9 - sposob 2 z MAILA od Pana:
// możesz spróbować zrobić zliczanie bitów tzn. dzielenie przez 2 jak w szkole podstawowej ;)
//  a poszczególne cyfry jako elementy tablicy.

// schemat:
// sprawdzanie czy liczba nieparzysta, jesli tak to dodaje do licznika
//  pisemne dzielenie - wynik dzielenia to nowa cyfra +
// jesli wyjdzie reszta = 1 to dodaje to do kolejnej cyfry
//  wzorem (reszta * 10) + stara cyfra
// usuwam zera z poczatka jesli istenieja
// itd itd az do zera

// NOTATKI
// liczba startowa to 163

// ostatnia cyfra 3 nieparzysta wiec licznik++ to 1bit
// PISEMNIE: 1:2=0 reszta1
// reszta 1 oraz cyfra 6 to 16 , czyli 16/2=8 r0
// reszta 0 oraz cyfra 3 to 3, czyli 3/2=1
//  wynik to 081 -> 81 po usunieciu zera

// wynik 81
// ostatnia cyfra nieparzysta -> licznik++ to 2bit
// PISEMNIE 8/2=4 r 0 .... 1/2= 0 r1
// wynik 40

// ostatnia cyfra parzysta wiec licznik zostaje
//  4/2 = 2 r0 ... 0/2=0 r

// wynik 20
// ostatnia parzysta
//  2/2=1 r0 ...0/2=0

// wynik 10
// parzyste 1/2=0 r1...reszta+cyfra0 to 1 oraz 0 czyli  10/2 = 5 r0

// wynik 5
// nieparzysta licznik++ to 3bit
//  5/2=2 r 1

// wynik 2
// parzysta , licznik zostaje 2/2=1

// wynik 1
// nieparzysta licznik++ czyli 4 bity
//  1/2 = 0
// KOOOONIEC petli

void f9(int n)
{
    for (int i = 0; i < n; i++)
    {
        string liczba;
        cin >> liczba;
        int licznik = 0;

        while (liczba != "0") // while dopoki nowa liczba bedzie zerem
        {

            int dlgStringa = liczba.length();
            int ostatnia = liczba[dlgStringa - 1] - '0'; // zmiana na int
            if (ostatnia % 2 != 0)                       // spr ostatniej cyfry. jesli nieparz to licznik++
            {
                licznik++;
            }

            string wynik = ""; // zmienna do nowego wyniku (nowej liczby)
            int reszta = 0;

            for (int wyraz = 0; wyraz < liczba.length(); wyraz++)
            {
                int cyfra = liczba[wyraz] - '0'; // zmiana na int

                int aktualna = (reszta * 10) + cyfra; // dzielenie pisemne(przenoszenie)

                wynik += (aktualna / 2) + '0'; // zmiana spowrotem na stringa
                reszta = aktualna % 2;         // modulo ktore laczy sie z druga cyfra
                                               // jesli koniec petli to nic nie robi bo jest zerowana
            }

            int zero = 0;
            // petla przechodzi przez wszystkie znaki i zlicza zera
            while (zero < wynik.length() - 1 && wynik[zero] == '0')
            {
                zero++;
            }

            liczba = wynik.substr(zero); // nowa czysta liczba (substr ucina zera)
        }
        cout << licznik << " ";
    }
    cout << endl;
}

/////////////////////////////////////////////////////////////////////////
int main()
{

    int numer_funkcji, n;

    // dla pp9 osobny if bo sam wczytuje liczbe jako string
    while (cin >> numer_funkcji >> n)
    {

        if (numer_funkcji == 9)
        {
            f9(n);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                cin >> tablica_wejsciowa[i];
            }

            switch (numer_funkcji)
            {
            case 0:
                f0(n, true);
                break;
            case 1:
                f1(n);
                break;
            case 2:
                f2(n, true);
                break;
            case 3:
                f3(n);
                break;
            case 4:
                f4(n);
                break;
            case 5:
                f5(n);
                break;
            case 6:
                f6(n);
                break;
            case 7:
                f7(n);
                break;
            case 8:
                f8(n);
                break;
            case 10:
                f10(n);
                break;
            }
        }
    }
    return 0;
}
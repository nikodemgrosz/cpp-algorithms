// Nikodem Grosz 210881 - Tarzan,
// - Programista wszedł pod prysznic z instrukcją na szamponie.
// - „Nałóż, spłucz, powtórz” i utknął w pętli.
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

// Struktura do opisywania wiosek (x, y)
struct Village
{
    int x, y;
};
// Funckja do szybkiego wczytywania liczb
// pomija ona znaki ktore nie sa [0-9] lub minusikiem

// bede uzywac do wszyskiego bo cin wolny
inline void readAndChange(int &realNumber)
{
    int isChar = getchar();
    int sign = 1;
    // operacje na znakach ASCII (najszybsza metoda, po prostu usuwa niepotrzebne znaki)
    while ((isChar < '0' || isChar > '9') && isChar != '-')
    {
        isChar = getchar();
    }

    if (isChar == '-')
    {
        sign = -1;
        isChar = getchar();
    }

    realNumber = 0;
    while (isChar >= '0' && isChar <= '9')
    {
        realNumber = realNumber * 10 + (isChar - '0'); // zamienia na cyfre dziesietna, zero tutaj to znak ASCII
        isChar = getchar();
    }
    realNumber *= sign;
}
// funkcja zwraca odleglosc od wioski do wioski
double getDistance(Village a, Village b)
{
    double cordX = (double)a.x - b.x;
    double cordY = (double)a.y - b.y;
    double euklides = sqrt(cordX * cordX + cordY * cordY);

    if (euklides < 1000.0)
    {
        return euklides; // < 1000 zwykly euklides
    }
    // wyjątki!!!
    if (a.y == b.y)
    {
        if (a.x >= 0 && b.x >= 0 && b.x < a.x)
            return euklides;
        if (a.x <= 0 && b.x <= 0 && b.x > a.x)
            return euklides;
    }

    return abs(a.x) + abs(b.x) + abs(a.y - b.y);
}

void mainFun()
{
    int villagesNumber;
    readAndChange(villagesNumber);

    vector<Village> villages; // wektor - tablica wiosek, na poczatku pusta
    // struktura jednowymiarowa, ktora ma w sobie {x,y} dla danej wioski
    for (int i = 0; i < villagesNumber; i++)
    // wczytywanie wiosek + potem sprawdzenie czy sie nie powtarzaja, jesli tak to nie dodajemy
    {
        int checkX, checkY;
        readAndChange(checkX);
        readAndChange(checkY);

        bool notExists = false;

        for (int j = 0; j < int(villages.size()); j++)
        {

            if (villages[j].x == checkX && villages[j].y == checkY)
            {
                notExists = true;
                break;
            }
        }
        if (!notExists)
        {
            villages.push_back({checkX, checkY});
        }
    }

    int n = villages.size(); // realna ilosc wiosek po sprawdzeniu duplikatow

    if (n <= 1)
    {
        printf("0\n");
        return;
    }
    // Macierz odleglosci, ktora jest szybsza niz liczenie sqrt, bo zapisujemy je w vektorze
    // dist[i][j] to odleglosc miedzy wioska i a wioska j
    // tworzymy tabele ktora jest zalezna od n czyli nxn
    // na start jest zerami ale potem wypelniona dystansem
    vector<double> singleRow(n, 0.0);
    // najpierw same wiersze, potem tworzymy macierz z tych wierszy
    vector<vector<double>> dist(n, singleRow);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = getDistance(villages[i], villages[j]);
        }
    }

    // Maska bitowa, bo permutacje nie daja rady, np. dla 10 wiosek to 10!, czyli ponad 3 mln mozliwosci
    // maxComb to 2^n- czyli maxymalna liczba kombinacji
    // bo przesuwamy bity binarnie
    int maxComb = 1 << n;
    vector<double> rowOfInfinities(n, 1e9); // porownuje potem najlepsze dystanse, wiec na start duza
    vector<vector<double>> bestDistance(maxComb, rowOfInfinities);
    // podroz startowa
    bestDistance[1][0] = 0.0;

    for (int combination = 1; combination < maxComb; combination++) // przechodzimy przez wszystkie kombinacje wiosek
    {
        for (int a = 0; a < n; a++) // a to aktualna wioska
        {
            if (bestDistance[combination][a] > 1e8) // na wszelki wypadek, jesli dystans jest duzy to pomijamy
                continue;

            for (int next = 0; next < n; next++) //
            {
                if (!(combination & (1 << next))) // pomijamy jesli next juz odwiedzone
                {
                    int nextCombination = combination | (1 << next);
                    if (bestDistance[nextCombination][next] > bestDistance[combination][a] + dist[a][next])
                    {
                        bestDistance[nextCombination][next] = bestDistance[combination][a] + dist[a][next];
                    }
                }
            }
        }
    }

    double minDistance = 1e9; // duza liczba, zeby potem mozna bylo porownywac
    int allCombination = maxComb - 1;

    for (int i = 1; i < n; i++)
    {
        double theEnd = bestDistance[allCombination][i] + dist[i][0]; // wracamy do punktu startowego
        if (theEnd < minDistance)
        {
            minDistance = theEnd;
        }
    }

    printf("%lld\n", (long long)floor(minDistance + 1e-9));
}

int main()
{
    int options;
    readAndChange(options);
    while (options--)
    {
        mainFun();
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int sizeOfmemory = 4096;
const int max_wierzcholki = 1000;

char memoryArray[sizeOfmemory];
// globalny bool, zeby nie musiec tworzyc go w kazdej instancji, bo to jest duza tablica
bool wspolna_sciana[max_wierzcholki][max_wierzcholki];

int sign = 0;
int fullChar = 0;

// funkcja wlasna getChar(), ktora bazuje na fread
// fread wczytuje do memoryArray i tam przechowuje
// wczytuje cale bloki danych naraz

inline char getChar()
{
    // jesli wykorzystano fullChar znakow, to trzeba wczytac nastepna porcja znakow do memoryArray
    if (sign >= fullChar)
    {
        fullChar = fread(memoryArray, 1, sizeOfmemory, stdin);
        sign = 0;

        if (fullChar == 0)
            return 0;
    }

    return memoryArray[sign++];
}

inline void readAndChange(int &realNumber)
{
    int isChar = getChar();
    int znakMinus = 1;

    while ((isChar < '0' || isChar > '9') && isChar != '-')
    {
        isChar = getChar();
    }

    if (isChar == '-')
    {
        znakMinus = -1;
        isChar = getChar();
    }

    realNumber = 0;

    while (isChar >= '0' && isChar <= '9')
    {
        realNumber = realNumber * 10 + (isChar - '0');
        isChar = getChar();
    }

    realNumber *= znakMinus;
}

int main()
{
    int instancje;
    readAndChange(instancje);

    while (instancje > 0)
    {
        int wierzcholki, sciany;

        readAndChange(wierzcholki);
        readAndChange(sciany);
        // false na wstepie(po poprzednim), na razie zadne
        // wierzcholki nie maja wspolnej sciany
        for (int i = 0; i < wierzcholki; i++)
        {
            for (int j = 0; j < wierzcholki; j++)
            {
                wspolna_sciana[i][j] = false;
            }
        }

        // od razu ustawienie zeby nie liczyc np. z punktu 1 do 1
        for (int i = 0; i < wierzcholki; i++)
        {
            wspolna_sciana[i][i] = true;
        }

        for (int i = 0; i < sciany; i++)
        {
            int liczba_punktow;
            readAndChange(liczba_punktow);

            // punkty sciany to tablica
            // ktora zapisuje jakie punkty leza na tej scianie
            vector<int> punkty_sciany(liczba_punktow);

            for (int j = 0; j < liczba_punktow; j++)
            {
                readAndChange(punkty_sciany[j]);
            }

            // te punkty ktore leza na tej samej scianie
            // ustawiamy na true we wspolna_sciana
            for (int a = 0; a < liczba_punktow; a++)
            {
                int u = punkty_sciany[a];

                for (int b = a; b < liczba_punktow; b++)
                {
                    int v = punkty_sciany[b];
                    // symetrycznie (oszczedzamy polowe petli)
                    wspolna_sciana[u][v] = true;
                    wspolna_sciana[v][u] = true;
                }
            }
        }

        ////////////////RYSOWANIE GRAFU PRZEKATNYCH////////////////

        // graf przekatnych przestrzeni, gdzie krawedz istnieje
        // miedzy dwoma wierzcholkami,
        // jesli nie maja wspolnej sciany

        vector<vector<int>> czerwony_graf(wierzcholki);

        for (int i = 0; i < wierzcholki; i++)
        {
            // rezerwacja miejsca (optymalizacja)
            // zmniejszanie realokacji wektora
            // pomaga wektorowi nie zacinac sie przy dodawaniu
            czerwony_graf[i].reserve(wierzcholki);

            for (int j = 0; j < wierzcholki; j++)
            {
                // jesli sa jakies punkty ktore nie leza na tej samej scianie
                // to znaczy, ze i i j nie maja wspolnej sciany,
                // wiec dorzucamy czerwony_graf[i]

                if (wspolna_sciana[i][j] == false)
                {
                    czerwony_graf[i].push_back(j);
                }
            }
        }

        long long wszystkie_cykle = 0;

        //////////// Liczenie kwadratow, czyli cykli o dlugosci 4//////////////

        for (int i = 0; i < wierzcholki; i++)
        {
            // j=i+1 zeby nie liczyc tego samego cyklu dwa razy

            for (int j = i + 1; j < wierzcholki; j++)
            {
                long long wspolni_sasiedzi = 0;
                // przechodzenie po wszystkich elementach czerwonego grafu
                // kazdy element zapisany do zmiennej sasiad
                for (int sasiad : czerwony_graf[i])
                {
                    if (sasiad != j)
                    {
                        // spr czy jest krawedz miedzy sasiad a j
                        // jesli false to jest czerwona linia

                        if (wspolna_sciana[j][sasiad] == false)
                        {
                            wspolni_sasiedzi++;
                        }
                    }
                }

                // kombinatoryka n*(n-1)/2

                wszystkie_cykle +=
                    (wspolni_sasiedzi * (wspolni_sasiedzi - 1)) / 2;
            }
        }

        // trzeba podzielic przez 2 bo kazdy kwadracik
        // jest liczony dwa razy (dwie przekatne)

        cout << wszystkie_cykle / 2 << "\n";

        instancje--;
    }

    return 0;
}
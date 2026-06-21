#include <iostream>
#include <cstdio>

using namespace std;

const int sizeOfmemory = 4096;
char memoryArray[sizeOfmemory];
int sign = 0;
int fullChar = 0;

inline char getChar()
{
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
    while ((isChar < '0' || isChar > '9') && isChar != '-' && isChar != 0)
    {
        isChar = getChar();
    }
    if (isChar == 0)
        return;

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

/// zadanko przedstawione jako stolik okragly
// gracz zna 3 osoby, polaczenie 2 rece i 1 kijek
int polaczenia[20000]; // ile kontakow ma gracz
int graf[20000][3];    // numery znajomych konkretnego gracza
int typ[20000][3];     // 1 to rece, 2 to kijki

// sprawdza czy gracz a zna gracza b
bool czy_znaja(int a, int b)
{
    for (int i = 0; i < 3; i++)
    {
        if (graf[a][i] == b)
        {
            return true;
        }
    }
    return false;
}

void spr()
{
    int gracze;
    readAndChange(gracze);

    // sprawdzenie czy gracz zna trzech innych
    bool poprawne = true;
    for (int i = 0; i < gracze; i++)
    {
        readAndChange(polaczenia[i]);
        if (polaczenia[i] != 3)
        {
            poprawne = false;
        }
    }

    // zapis do graf kto z kim jest polaczony
    for (int i = 0; i < gracze; i++)
    {
        for (int j = 0; j < polaczenia[i]; j++)
        {
            int znajomy;
            readAndChange(znajomy);
            if (j < 3)
            {
                graf[i][j] = znajomy;
            }
        }
    }

    // jesli nie zna trzech, gracze czyli n=2p ponizej wymaganej lub
    // nieparzysta liczba graczy to false
    if (!poprawne || gracze < 6 || gracze % 2 != 0)
    {
        cout << "False\n";
        return;
    }

    // sprawdza po kolei trzy polaczenia dla danwgo gracza
    for (int gracz = 0; gracz < gracze; gracz++)
    {
        for (int i = 0; i < 3; i++)
        {
            int znajomy = graf[gracz][i];
            int wspolni = 0;

            for (int j = 0; j < 3; j++)
            {
                int x = graf[gracz][j];
                if (x == znajomy)
                {
                    continue; // skip samemgo siebie
                }

                for (int k = 0; k < 3; k++)
                {
                    int y = graf[znajomy][k];
                    if (y == gracz)
                        continue;

                    if (czy_znaja(x, y))
                    {
                        wspolni++;
                    }
                }
            }
            typ[gracz][i] = wspolni;
        }
    }

    bool czy_pasuje = true;
    //  jesli 6 graczy to krzyzowanie
    if (gracze == 6)
    {
        for (int i = 0; i < gracze; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (typ[i][j] != 2)
                {
                    czy_pasuje = false;
                }
            }
        }
    }
    else // jesli 8 lub wiecej
    {
        for (int i = 0; i < gracze; i++)
        {
            int rece = 0;
            int kijki = 0;
            for (int j = 0; j < 3; j++) // zliczanie z tablicy typ co trzyma
            {
                if (typ[i][j] == 1)
                    rece++;
                if (typ[i][j] == 2)
                    kijki++;
            }

            // jesli nie ma 2 rak zalapane oraz kijka to nie jest mobiius
            if (rece != 2 || kijki != 1)
            {
                czy_pasuje = false;
            }
        }
    }

    // weryfikacja czy to jeden stół, a nie dwa osobne
    if (czy_pasuje && gracze > 6)
    {
        bool odwiedzony[20000] = {false};
        int obecny = 0;
        int odwiedzonych_graczy = 0;

        for (int krok = 0; krok < gracze; krok++)
        {
            odwiedzony[obecny] = true;
            odwiedzonych_graczy++;
            int nastepny = -1;

            for (int j = 0; j < 3; j++)
            {
                if (typ[obecny][j] == 1)
                {
                    int sasiad = graf[obecny][j];
                    if (!odwiedzony[sasiad])
                    {
                        nastepny = sasiad;
                        break;
                    }
                }
            }

            if (nastepny == -1 && odwiedzonych_graczy < gracze)
            {
                czy_pasuje = false;
                break;
            }
            obecny = nastepny;
        }
    }

    if (czy_pasuje)
    {
        cout << "True\n";
    }
    else
    {
        cout << "False\n";
    }
}

int main()
{
    int testy = 0;
    readAndChange(testy);
    if (testy == 0)
        return 0;

    while (testy > 0)
    {
        spr();
        testy--;
    }

    return 0;
}

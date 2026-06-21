#include <iostream>
#include <vector>

using namespace std;
// szybkie wczytywanie danych
inline void readAndChange(int &realNumber)
{
    int isChar = getchar();
    int sign = 1;

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
        realNumber = realNumber * 10 + (isChar - '0');
        isChar = getchar();
    }
    realNumber *= sign;
}
// globalna
int max_profit = 0;

//
void checking(int currentIndex, int currentProfit, int currentWeight, int itemsTaken, int n, int capacityOfcar, const vector<int> &Price, const vector<int> &Weight, const vector<int> &maxFutureProfit)
{

    // zapisuje ile max kasy zostalo do zebrania od momentu currentIndex do konca
    // wyrzuca sprawdzanie wag ktore nie przyniosa wiekszego profitu
    if (currentIndex < n)
    {
        int potentialProfit = currentProfit + maxFutureProfit[currentIndex];

        if (itemsTaken == 0)
        {
            potentialProfit -= 20;
        }

        if (potentialProfit <= max_profit)
        {
            return;
        }
    }

    // jesli dojdzie do konca to odejmuje 20 zl i zapisuje aktualny naj profit
    if (currentIndex == n)
    {
        int finalGain = currentProfit;
        if (itemsTaken > 0)
        {
            finalGain -= 20;
        }

        if (finalGain > max_profit)
        {
            max_profit = finalGain;
        }
        // wraca do NIEBIORE
        return;
    }
    // currentIndex=0
    // 0kg + 211kg <= 1766
    // funkcja w funkcji checking(1,583,211,1,...
    // BIORE BO MIESCI SIE
    if (currentWeight + Weight[currentIndex] <= capacityOfcar)
    {
        checking(currentIndex + 1, currentProfit + Price[currentIndex], currentWeight + Weight[currentIndex], itemsTaken + 1, n, capacityOfcar, Price, Weight, maxFutureProfit);
    }

    // NIEBIORE
    checking(currentIndex + 1, currentProfit, currentWeight, itemsTaken, n, capacityOfcar, Price, Weight, maxFutureProfit);
}

int main()
{
    int options;
    readAndChange(options);

    while (options > 0)
    {
        int n;
        readAndChange(n);
        // tablica z cenami
        vector<int> Price(n);
        for (int i = 0; i < n; i++)
        {
            readAndChange(Price[i]);
        }
        // tablica z waga przedmiotow
        vector<int> Weight(n);
        for (int i = 0; i < n; i++)
        {
            readAndChange(Weight[i]);
            // od razu >100kg odjac 5 zl
            if (Weight[i] > 100)
            {
                Price[i] -= 5;
            }
        }
        // tablica z sumowaniem zyskow od konca
        vector<int> maxFutureProfit(n, 0);
        int currentMaxFuture = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (Price[i] > 0)
            {
                currentMaxFuture += Price[i];
            }
            maxFutureProfit[i] = currentMaxFuture;
        }
        // ile kg ma auto
        int capacityOfcar;
        readAndChange(capacityOfcar);

        // po wykonaniu jednej opcji profit=0
        max_profit = 0;
        // na start zera indeksie,cenie,wadze,przedmioty wziete
        checking(0, 0, 0, 0, n, capacityOfcar, Price, Weight, maxFutureProfit);

        // cout na zmienna globalna
        cout << max_profit << "\n";
        options--;
    }

    return 0;
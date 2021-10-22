//Расчётная работа 121701 Чвилёв.И.А.


#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream in("File.txt");

/*bool sravn(int* a, int* b, int n) //Сравнивание массивов (строчек списка)
{
    for (int i = 0; i < n; i++) 
    {
        if (b[i] != a[i])
        {
            return false;
        }
    }

    return true;
}*/

void vvod(int* strdlina, int** spisok, int n) //Ввод списка
{
    char buff;
    for (int i = 0; i < n; i++)
    {
        cout << "----------------------------------------------------------------\n";
        strdlina[i] = n;
        char buff;
        for (int j = 0; j < n; j++)
        {
            in >> spisok[i][j];
            buff = in.get();
            if (buff != ' ')
            {
                strdlina[i] = j;
                break;
            }
        }
    }
}

bool prov(int* strdlina, int** spisok, int n) //Проверка на валидность
{
    int* zap = new int[n]; //Массив для первых элементов строчек списка
    int* tzap = new int[n]; //Массив для элементов в одной строчке

    for (int i = 0; i < n; i++)
    {
        if (find(zap, zap + i, spisok[i][0]) != zap + i) //Проверяем на повторение в постоянном массиве zap
        {
            cout << "Введённый граф невалиден\n";
            return false;
        }

        zap[i] = spisok[i][0]; //Присваиваем первый элемент текущей строки массиву zap

        for (int j = 0; j < strdlina[i]; j++)
        {
            tzap[j] = spisok[i][j]; // Присваиваем текущий элемент текущей строки массиву tzap
            tzap[0] = 0;
            if (find(tzap, tzap + j, spisok[i][j]) != tzap + j) //Проверяем на повторение в временном массиве tzap
            {
                cout << "Введённый граф невалиден\n";
                return false;
            }
        }
    }

    delete[] zap; 
    delete[] tzap;
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    bool self = false;
    cout << "Введите количество вершин в вашем графе\n";
    in >> n;
    int** spisok = new int*[n];
    bool* right = new bool[n + 1]{false};
    int rightamount, leftamount;

    for (int i = 0; i < n; i++)
    {
        spisok[i] = new int[n];
    }

    int* strdlina = new int[n];
    vvod(strdlina, spisok, n); //Вызов ввода

    if (!prov(strdlina, spisok, n))
    {
        return 0;
    }  

    rightamount = strdlina[0];
    leftamount = n - rightamount;

    for (int j = 1; j <= strdlina[0]; j++)
    {
        right[spisok[0][j]] = true;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= strdlina[i]; j++)
        {
            if (right[spisok[i][j]] == right[spisok[i][0]])
            {
                cout << "Граф не двудольный!\n";
                return 0;
            }

            if ((right[spisok[i][0]] == 0 && strdlina[i] == rightamount) || (right[spisok[i][0]] == 1 && strdlina[i] == leftamount))
            {
                continue;
            }
            else 
            {
                cout << "Граф не двудольный!\n";
                return 0;
            }
        }
    }
    cout << "Граф двудольный!!!!!!\n";
}



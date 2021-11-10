#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

/*
    Автор: Ахметзянов Дамир Альбертович, гр. 1309
    Версия: 3.0
    Начало: 26.10.2021
    Конец: -
    Задание: 13
*/

typedef long double ld;
typedef long long ll;

const int N = 100;


int main() {
    ofstream out("../out.txt");

    cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 3.0"
         << endl << "Начало: 10.10.2021"
         << endl << "Конец: -"
         << endl << "Задание: 13\n";
    out << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 3.0"
         << endl << "Начало: 10.10.2021"
         << endl << "Конец: -"
         << endl << "Задание: 13\n";

    ifstream fin("../in.txt");
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл";
        out << "Не удалось открыть файл";
        return 0;
    }

    int n;
    fin >> n;
    n = max(min(n, N), 0);

    double arr[N];

    for (int i = 0; i < n; i++) {
        fin >> arr[i];
        if (fin.eof()) {
            n = i + 1;
            break;
        }
    }

    double m = 1;

    for (int i = 0; i < n; i++) {
        if (m == 1) m = arr[i];
        else if (arr[i] < 0) m = max(m, arr[i]);
    }

    cout << "Наибольшее отрицательное число из " << n << " чисел: " << m << endl;
    out << "Наибольшее отрицательное число из " << n << " чисел: " << m << endl;

    cout << "Обработанный массив: ";
    out << "Обработанный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ", ";
        out << arr[i] << ", ";
    }

    fin.close();
    out.close();

    return 0;
}
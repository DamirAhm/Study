#include <iostream>
#include <cmath>

using namespace std;

/*
    Автор: Ахметзянов Дамир Альбертович, гр. 1309
    Версия: 2.0
    Начало: 25.09.2021
    Конец: -
    Рисунок: 5.3 - б

    Тестовые значения:

*/

typedef long double ld;

ld a, b;

ld f(ld x) {
    if (b > 0) {
        return abs(b / a * x - 2 * b) - b;
    } else {
        return -abs(b / a * x - 2 * b) - b;
    }
}

int main() {
    cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 2.0"
         << endl << "Начало: 25.09.2021"
         << endl << "Конец: -"
         << endl << "Рисунок: 5.3 - б\n";

    cout << "Введите значения а и b: ";
    cin >> a >> b;

    int n;
    cout << "Введите количество точек для проверки: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        ld x, y;
        cout << "Введите координаты точки x" << i << " y" << i << ": ";
        cin >> x >> y;
        bool belongs;

        if (a == 0) {
            belongs = abs(y) <= abs(b);
        } else if (b == 0) {
            belongs = y == 0;
        } else {
            long double cutX = x - 4L * a * floor(x / (4L * a));
            ld val = f(cutX);

            int sec = floor((cutX+a) / a);

            if (sec == 1 || sec == 4) {
                belongs = b > 0 ? y <= val && y >= 0 : y >= val && y <= 0;
            } else {
                belongs = b > 0 ? y >= val && y <= 0 : y <= val && y >= 0;
            }
        }

        if (belongs) {
            printf("Точка %d (%.1Lf %.1Lf) принадлежит указанной области\n", i, x, y);
        } else {
            printf("Точка %d (%.1Lf %.1Lf) не принадлежит указанной области\n", i, x, y);
        }
    }

    return 0;
}
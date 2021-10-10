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
double a, b;

double f(double x) {
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

    double x, y;
    cout << "Введите координаты точки x(0 < |x|, |y| < 2^31): ";
    cin >> x >> y;
    bool belongs;

    if (a == 0) {
        belongs = abs(y) <= abs(b);
    } else if (b == 0) {
        belongs = y == 0;
    } else {
        double cutX = x - 4 * a * floor(x / (4 * a));
        double val = f(cutX);

        int sec = floor((cutX + a) / a);

        if (sec == 1 || sec == 4) {
            belongs = b > 0 ? y <= val && y >= 0 : y >= val && y <= 0;
        } else {
            belongs = b > 0 ? y >= val && y <= 0 : y <= val && y >= 0;
        }
    }

    if (belongs) {
        printf("Точка (%.2f %.2f) принадлежит указанной области\n", x, y);
    } else {
        printf("Точка (%.2f %.2f) не принадлежит указанной области\n", x, y);
    }


    return 0;
}
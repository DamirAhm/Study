#include <iostream>
#include <iomanip>

using namespace std;

/*
    Автор: Ахметзянов Дамир Альбертович, гр. 1309
    Версия: 1.0
    Начало: 15.09.2021
    Конец: -
    Полиномы:
    2. x^8 + x^2 - x + 1
    60. 333,3x^36 + 11,11x^20 + 88,8x^4
*/

typedef long double ld;

const ld A = 333.3;
const ld B = 11.11;
const ld C = 88.8;

ld pow(ld number, int power) {
    ld result = 1;

    for (int i = 0; i < power; i++) result *= number;

    return result;
}

ld count1(ld x) {
    ld result2 = ((pow(x, 6) + 1) * x - 1) * x + 1;
    cout << "Результат 2го полинома: " << result2 << endl;

    ld result60 = ((A * pow(x, 16) + B) * pow(x, 16) + C) * pow(x, 4);
    cout << "Результат 60го полинома: " << result60 << endl;

    return result2 * result60;
}

ld count2(ld x) {
    ld P1_2 = pow(x, 6) + 1;
    cout << "На шаге 1, 2го полинома P1: " << P1_2 << endl;
    ld P2_2 = P1_2 * x - 1;
    cout << "На шаге 2, 2го полинома P2: " << P2_2 << endl;
    ld P3_2 = P2_2 * x + 1;
    cout << "Результат 2го полинома:" << P3_2 << endl;

    ld P1_60 = A * pow(x, 16) + B;
    cout << "На шаге 1, 60го полинома P1: " << P1_60 << endl;
    ld P2_60 = P1_60 * pow(x, 16) + C;
    cout << "На шаге 2, 60го полинома P2: " << P2_60 << endl;
    ld P3_60 = P2_60 * pow(x, 4);
    cout << "Результат 60го полинома: " << P3_60 << endl;

    return P3_2 * P3_60;
}

ld count3(ld x) {
    ld P1_2 = pow(x, 6) + 1;
    printf("На шаге 1, 2го полинома P1: %Lf\n", P1_2);
    ld P2_2 = P1_2 * x - 1;
    printf("На шаге 2, 2го полинома P2: %Lf\n", P2_2);
    ld P3_2 = P2_2 * x + 1;
    printf("Результат 2го полинома: %Lf\n", P3_2);

    ld P1_60 = A * pow(x, 16) + B;
    printf("На шаге 1, 60го полинома P1: %Lf\n", P1_60);
    ld P2_60 = P1_60 * pow(x, 16) + C;
    printf("На шаге 2, 60го полинома P2: %Lf\n", P2_60);
    ld P3_60 = P2_60 * pow(x, 4);
    printf("Результат 60го полинома: %Lf\n", P3_60);

    return P3_2 * P3_60;
}

int main() {
    ld x;

    cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 1.0"
         << endl << "Начало: 15.09.2021"
         << endl << "Конец: -"
         << endl << "Полиномы:"
         << endl << "2. x^8 + x^2 - x + 1"
         << endl << "60. 333,3x^36 + 11,11x^20 + 88,8x^4";
    cout << endl << "Введите x( 1 < |x| < 3): ";

    cin >> x;

    cout << endl << fixed << setprecision(4);

    ld res = count3(x);
    printf("Для х = %Lf, результат умножения полиномов равен: %Lf", x, res);

    return 0;
}

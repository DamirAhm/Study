#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

/*
    Автор: Ахметзянов Дамир Альбертович, гр. 1309
    Версия: 3.0
    Начало: 10.10.2021
    Конец: -
    Формула: 9.10

    n    i
    __  2 * i!     i
    \  ________ * x
    /_   i^i
    i=1

    Тестовые значения:

*/

typedef long double ld;
typedef long long ll;

const ld max_eps = 1e-30;
const ld min_M = 1e10;

ofstream fout("../out.txt");

ld x;

ld power(ld num, ll deg) {
    ld result = 1;
    while (deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        } else {
            deg--;
            result *= num;
        }
    }

    return result;
}

ld fn(ld prev, int i) {
    return prev * (2.0L * x) * (ld) power((i - 1.0L) / i, i - 1);
}

struct table_row {
    int i;
    ld Fi;
    ld sum;
};

int main() {
    cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 3.0"
         << endl << "Начало: 10.10.2021"
         << endl << "Конец: -"
         << endl << "Формула: 9.10"
         << endl << "n    i\n"
                    "__  2 * i!     i\n"
                    "\\  ________ * x\n"
                    "/_   i^i\n"
                    "i=1\n";
    fout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир Альбертович, группа 1309"
         << endl << "Версия: 3.0"
         << endl << "Начало: 10.10.2021"
         << endl << "Конец: -"
         << endl << "Формула: 9.10"
         << endl << "n    i\n"
                    "__  2 * i!     i\n"
                    "\\  ________ * x\n"
                    "/_   i^i\n"
                    "i=1\n";

    cout << "Введите х (x > 0): ";
    cin >> x;
    fout << "X: " << x << endl;

    ld eps;
    ld M;
    int t = 1;

    if (x < 1.35) {
        cout << "Введите эпсилон(1e-308 <= eps <= 1e-30): ";
        cin >> eps;
        while (eps > max_eps && t <= 3) {
            cout << "Слишком большой эпсилон\n";
            cin >> eps;
            t++;
        }
    } else {
        cout << "Введите M(1e10 <= M <= 1e308): ";
        cin >> M;
        while (M < min_M && t <= 3) {
            cout << "Слишком маленькое M\n";
            cin >> M;
            t++;
        }
    }

    if (x < 1.36 ? eps > max_eps : M < min_M) return 0;
    fout << (x < 1.36 ? "eps:" : "M: ") << (x < 1.35 ? eps : M) << endl;


    //Значение для i = 1
    ld prev = 2 * x;
    //Значение для i = 2
    ld next = prev;

    ld sum = prev;

    vector<table_row> arr;
    arr.push_back({1, prev, sum});

    int i = 2;

    while (x < 1.36 ? abs(next) >= eps : abs(next) <= M) {
        ld temp = next;
        next = fn(prev, i);
        prev = temp;
        sum += next;
        if ( x < 1.36 ? next >= eps : next <= M ) {
            arr.push_back({i, next, sum});
        }
        i++;
    }


    cout << "n = " << i - 1 << endl;
    fout << "n = " << i - 1 << endl;
    cout << "An = " << prev << endl;
    fout << "An = " << prev << endl;
    cout << "Сумма = " << setprecision(9) << sum << endl;
    fout << "Сумма = " << setprecision(9) << sum << endl;

    cout << setw(19) << "i |  " << setw(18) << "Fi |  " << setw(17) << "S | " << endl;
    cout << "_____________________________________________________" << endl;
    fout << setw(18) << "i | " << setw(18) << "Fi | " << setw(17) << "S |" << endl;
    fout << "_____________________________________________________" << endl;
    for (table_row row : arr) {
        cout << setw(15) << row.i << " | " << setw(15) << row.Fi << " | " << setw(15) << row.sum << " | " << endl;
        fout << setw(15) << row.i << " | " << setw(15) << row.Fi << " | " << setw(15) << row.sum << " | " << endl;
    }

    fout.close();
    return 0;
}
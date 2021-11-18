#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const int PRES = 1;
const int MAX_N = 100;

void out(fstream &file, string text) {
    cout << text;
    file << text;
}

void out(fstream &file, double n) {
    cout << fixed << setprecision(PRES) << setw(5) << n << " ";
    file << fixed << setprecision(PRES) << setw(5) << n << " ";
}

void print_array(fstream &file, double **arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            out(file, *(*(arr + i) + j));
        }
        out(file, "\n");
    }
}

void read_array(fstream &in, double **arr, int &N) {
    int read_rows = 0;
    for (int i = 0; i < N; i++, read_rows++) {
        if (in.eof()) {
            N = 0;
            break;
        }
        auto *row = new double[N];
        int j = 0;

        bool changed_line = false;

        for (j; j < N; j++) {
            double t;

            in >> setiosflags(ios::skipws) >> t;
            *(row + j) = t;

            if (in.eof()) {
                N = min(j + 1, i + 1);
                break;
            }

            char s;
            in >> resetiosflags(ios::skipws) >> s;
            while (s == ' ') {
                in >> resetiosflags(ios::skipws) >> s;
            }
            if (s == '\r') {
                changed_line = true;
                if (j != 0) {
                    N = j + 1;
                }
            } else {
                if (in.eof()) {
                    N = j + 1;
                    break;
                }
                in.seekg(-1, ios::cur);
            }

        }

        if (!changed_line) {
            char s;
            in >> resetiosflags(ios::skipws) >> s;
            while (s != '\r' && !in.eof()) {
                in >> resetiosflags(ios::skipws) >> s;
            }
        }

        if (j != 0) {
            *(arr + i) = row;
        }
    }
    N = min(N, read_rows);
}

double parse_array(double **arr, int N, int m, int k) {
    int curX = 0;
    int curY = k - 1;

    double mx = **arr;

    for (int i = 0; i < k; i++) {
        while (curX < N && curY < N) {
            mx = max(mx, *(*(arr + curY) + curX));
            mx = max(mx, *(*(arr + N - curY - 1) + curX));
            curX++;
            curY++;
        }
        curX = 0;
        curY = k - i - 2;
    }
    curX = 0;
    curY = 0;
    for (int i = 0; i < m; i++) {
        while (curX < N && curY < N) {
            mx = max(mx, *(*(arr + curY) + curX));
            mx = max(mx, *(*(arr + N - curY - 1) + curX));
            curX++;
            curY++;
        }
        curX = i - 1;
        curY = 0;
    }

    return mx;
}

int main() {
    fstream in("../good.txt");
    fstream file("../out.txt");

    if (!in.is_open()) {
        cout << "Невозможно открыть файл для чтения";
        return 0;
    } else if (!file.is_open()) {
        cout << "Невозможно открыть файл для записи";
        return 0;
    }

    int m, k;
    out(file, "Введите m: ");
    cin >> m;
    out(file, "Введите k: ");
    cin >> k;

    int N;
    in >> N;
    N = max(min(N, MAX_N), 0);
    m = min(m, (N + 1) / 2);
    k = min(k, (N + 1) / 2);

    auto **arr = new double *[N];

    for (int i = 0; i < N; i++) {
        auto *t = new double[N];
        *(arr + i) = t;
    }

    read_array(in, arr, N);
    cout << N;
    double res = parse_array(arr, N, m, k);

    out(file, "Результат: ");
    out(file, res);
    out(file, "\nОбработанная матрица порядка ");
    out(file, N);
    out(file, "\n");
    print_array(file, arr, N);

    return 0;
}

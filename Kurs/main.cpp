#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>
#include <algorithm>
#include <iomanip>

using namespace std;

const int PRES = 5;
const int MAX = 100;

void log(fstream &file, string text) {
    cout << text;
    file << text;
}

void log(fstream &file, double n) {
    cout << fixed << setprecision(PRES) << setw(5) << n << " ";
    file << fixed << setprecision(PRES) << setw(5) << n << " ";
}

double dlin(double *a, double *b) {
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

double vproisv(double *a, double *b) {
    return b[0] * a[1] - a[0] * b[1];
}

bool is_90(double *a, double *b, double *c) {
    double vec1[2] = {b[0] - a[0], b[1] - a[1]};
    double vec2[2] = {c[0] - b[0], c[1] - b[1]};

    double scalar = vec1[0] * vec2[0] + vec1[1] * vec2[1];

    return scalar == 0 && !((vec1[0] == 0 && vec1[1] == 0) || (vec2[0] == 0 && vec2[1] == 0));
}

double *to_vector(double *a, double *b) {
    auto *vector = new double[2];
    vector[0] = b[0] - a[0];
    vector[1] = b[1] - a[1];

    return vector;
}

int *sort_dots(int *rectangle_dots, double **dots) {
    auto *sorted_dots = new int[4];

    int max_x = 0;
    int min_x = 1;
    int max_y = 0;
    int min_y = 1;

    for (int i = 0; i < 4; i++) {
        if (dots[rectangle_dots[i]][0] > dots[rectangle_dots[max_x]][0]) max_x = i;
        if (dots[rectangle_dots[i]][0] < dots[rectangle_dots[min_x]][0]) min_x = i;
        if (dots[rectangle_dots[i]][1] > dots[rectangle_dots[max_y]][1]) max_y = i;
        if (dots[rectangle_dots[i]][1] < dots[rectangle_dots[min_y]][1]) min_y = i;
    };

    int c = 0;
    for (int i = 1; i < 4; i++) {
        if (dots[rectangle_dots[i]][0] == dots[rectangle_dots[0]][0] ||
            dots[rectangle_dots[i]][1] == dots[rectangle_dots[0]][1])
            c++;
    }
    bool flat = c == 2;

    if (flat) {
        for (int i = 0; i < 4; i++) {
            if (dots[rectangle_dots[i]][0] == dots[rectangle_dots[min_x]][0] &&
                dots[rectangle_dots[i]][1] == dots[rectangle_dots[max_y]][1]) {
                sorted_dots[0] = rectangle_dots[i];
            } else if (dots[rectangle_dots[i]][0] == dots[rectangle_dots[max_x]][0] &&
                       dots[rectangle_dots[i]][1] == dots[rectangle_dots[max_y]][1]) {
                sorted_dots[1] = rectangle_dots[i];
            } else if (dots[rectangle_dots[i]][0] == dots[rectangle_dots[max_x]][0] &&
                       dots[rectangle_dots[i]][1] == dots[rectangle_dots[min_y]][1]) {
                sorted_dots[2] = rectangle_dots[i];
            } else if (dots[rectangle_dots[i]][0] == dots[rectangle_dots[min_x]][0] &&
                       dots[rectangle_dots[i]][1] == dots[rectangle_dots[min_y]][1]) {
                sorted_dots[3] = rectangle_dots[i];
            }
        }

        return sorted_dots;
    } else {
        sorted_dots[0] = rectangle_dots[max_y];
        sorted_dots[1] = rectangle_dots[max_x];
        sorted_dots[2] = rectangle_dots[min_y];
        sorted_dots[3] = rectangle_dots[min_x];
    }

    return sorted_dots;
}

bool is_in(double *dot, int *figure, double **dots, int n) {
    bool is_same_sign = true;

    for (int i = 1; i < n - 1; i++) {
        double first_prod = vproisv(to_vector(dot, dots[figure[i - 1]]), to_vector(dots[figure[i - 1]], dots[figure[i]]));
        double second_prod = vproisv(to_vector(dot, dots[figure[i]]), to_vector(dots[figure[i]], dots[figure[i + 1]]));

        if (first_prod * second_prod < 0) return false;
    }

    double first_prod = vproisv(to_vector(dot, dots[figure[n - 2]]), to_vector(dots[figure[n - 2]], dots[figure[n - 1]]));
    double second_prod = vproisv(to_vector(dot, dots[figure[n - 1]]), to_vector(dots[figure[n - 1]], dots[figure[0]]));

    return first_prod * second_prod >= 0;
}

void read_dots(double **dots, int &N, fstream &in, fstream &f) {
    int line = 2;
    for (int i = 0; i < N; i++, line++) {
        char c = ' ';
        bool skipped = false;
        while (true) {
            in >> resetiosflags(ios::skipws) >> c;

            if (c != '\n' && !in.eof()) {
                if (c == ' ') continue;
                else {
                    in.seekg(-1, ios::cur);
                    break;
                }
            } else {
                i--;
                log(f, "Строка " + to_string(line) + " пропущена так как пуста \n");
                if (in.eof()) {
                    N = i + 1;
                    return;
                }
                skipped = true;
            }
        }
        if (skipped) {
            continue;
        }

        in >> setiosflags(ios::skipws) >> dots[i][0];
        while (true) {
            in >> resetiosflags(ios::skipws) >> c;

            if (c != '\n' && !in.eof()) {
                if (c == ' ') continue;
                else {
                    in.seekg(-1, ios::cur);
                    break;
                }
            } else {
                i--;
                log(f, "Строка " + to_string(line) + " пропущена так как отсутствует у координата \n");
                skipped = true;
            }
        }
        if (skipped) continue;

        in >> setiosflags(ios::skipws) >> dots[i][1];
        while (true) {
            in >> resetiosflags(ios::skipws) >> c;
            if (c == '\n' || in.eof()) break;
        }
        if (in.eof()) {
            N = i + 1;
            break;
        }
    }
}

bool same(int *rect1, int *rect2) {
    return rect1[0] == rect2[0] && rect1[1] == rect2[1] && rect1[2] == rect2[2] && rect1[3] == rect2[3];
}

void find_rectangles(double **dots, int **&rectangles, int N, int &f_rects, int cur_size) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (i != j && j != k && k != i) {
                    if (is_90(dots[i], dots[j], dots[k])) {
                        double new_dot_x = dots[i][0] + (dots[k][0] - dots[j][0]);
                        double new_dot_y = dots[i][1] + (dots[k][1] - dots[j][1]);
                        auto *new_dot = new double[2];
                        new_dot[0] = new_dot_x;
                        new_dot[1] = new_dot_y;

                        int *possible_4th = new int[100];
                        int n_possibles = 0;
                        for (int o = 0; o < N; o++) {
                            if (dots[o][0] == new_dot_x && dots[o][1] == new_dot_y && o != i && o != j && o != k) {
                                possible_4th[n_possibles] = o;
                                n_possibles++;
                                break;
                            }
                        }

                        for (int o = 0; o < n_possibles; o++) {
                            auto *rectangle = new int[4];
                            rectangle[0] = i;
                            rectangle[1] = j;
                            rectangle[2] = k;
                            rectangle[3] = possible_4th[o];

                            rectangle = sort_dots(rectangle, dots);

                            bool exists = false;
                            for (int m = 0; m < f_rects; m++) {
                                if (same(rectangles[m], rectangle)) {
                                    exists = true;
                                    break;
                                }
                            }

                            if (!exists) {
                                if (f_rects == cur_size) {
                                    auto **new_arr = new int *[2 * cur_size];
                                    memcpy(new_arr, rectangles, cur_size * sizeof(int *));
                                    rectangles = new_arr;
                                    cur_size *= 2;
                                }

                                rectangles[f_rects] = rectangle;
                                f_rects++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void find_pentagons(double **dots, int **rectangles, int **&pentagons, int N, int &f_pents, int f_rects, int cur_size, fstream &f) {
    for (int i = 0; i < f_rects; i++) {
        auto rect = rectangles[i];
        for (int j = 0; j < N; j++) {
            auto dot = dots[j];

            for (int k = 0; k < 3; k++) {
                if (dlin(dot, dots[rect[k]]) == dlin(dot, dots[rect[k + 1]])) {
                    auto len1 = dlin(dot, dots[rect[k]]);
                    auto len2 = dlin(dot, dots[rect[(k + 2) % 4]]);
                    if (len1 > len2) continue;
                    if (!is_in(dot, rect, dots, 4)) {
                        log(f,
                            "Прямоугольник " + to_string(i + 1) + " образует домик с точкой " + to_string(j + 1) + "\n");
                        int *pent = new int[5];

                        for (int o = 0; o <= k; o++) {
                            pent[o] = rect[o];
                        }
                        pent[k + 1] = j;
                        for (int o = k + 2; o < 5; o++) {
                            pent[o] = rect[o - 1];
                        }

                        if (f_pents == cur_size) {
                            auto **new_arr = new int *[2 * cur_size];
                            memcpy(new_arr, pentagons, cur_size * sizeof(int *));
                            pentagons = new_arr;
                            cur_size *= 2;
                        }

                        pentagons[f_pents] = pent;
                        f_pents++;
                    }
                }
            }
        }
    }
}

void print_figure(int *pent, double **dots, fstream &f, int n) {
    for (int i = 0; i < n; i++) {
        log(f, dots[pent[i]][0]);
        log(f, " ");
        log(f, dots[pent[i]][1]);
        log(f, " (" + to_string(pent[i]) + ") | ");
    }
}

void print_pentagons(int **pentagons, int f_pents, double **dots, fstream &f) {
    for (int i = 0; i < f_pents; i++) {
        log(f, to_string(i + 1) + " | ");
        print_figure(pentagons[i], dots, f, 5);
        log(f, "\n");
    }
}

int main() {
    fstream in("../in.txt");
    fstream f("../out.txt", ios::out);
    fstream protocol("../protocol.txt", ios::out);

    if (!f.is_open()) {
        cout << "Не получилось открыть файл для записи";
        return 0;
    } else if (!in.is_open()) {
        log(f, "Не получилось открыть файл для чтения");
        return 0;
    } else if (!protocol.is_open()) {
        log(f, "Не получилось открыть файл для записи протокола");
        return 0;
    }

    log(f, "Здравствуйте, данную лабораторную работу выполнил Герасимов Артемий Михайлович, группа 1309\nЗадание: 7з\n");

    int N;
    in >> N;
    char c = ' ';
    while (true) {
        in >> resetiosflags(ios::skipws) >> c;
        if (c == '\n' || in.eof()) break;
    }
    N = max(min(N, MAX), 0);

    auto **dots = new double *[N];
    auto **rectangles = new int *[2];
    int f_rects = 0;

    for (int i = 0; i < N; i++) dots[i] = new double[2];

    read_dots(dots, N, in, protocol);

    log(protocol, "В файле найдено " + to_string(N) + " точек \n");
    for (int i = 0; i < N; i++) {
        log(protocol, to_string(i + 1) + " | ");
        log(protocol, dots[i][0]);
        log(protocol, " | ");
        log(protocol, dots[i][1]);
        log(protocol, "\n");
    }

    find_rectangles(dots, rectangles, N, f_rects, 2);

    log(protocol, "В файле найдено " + to_string(f_rects) + " прямоугольников \n");
    for (int i = 0; i < f_rects; i++) {
        log(protocol, to_string(i + 1) + " | ");
        print_figure(rectangles[i], dots, protocol, 4);
        log(protocol, "\n");
    }

    auto **pentagons = new int *[2];
    int f_pents = 0;

    find_pentagons(dots, rectangles, pentagons, N, f_pents, f_rects, 2, protocol);

    log(protocol, "В файле найдено " + to_string(f_pents) + " домиков \n");
    print_pentagons(pentagons, f_pents, dots, protocol );

    int max_n = 0;
    int** max_pents = new int* [f_pents];
    int max_pents_n = 0;

    for (int i = 0; i < f_pents; i++) {
        int c = 0;
        int *pent_dots = new int[N];

        for (int j = 0; j < N; j++) {
            if (is_in(dots[j], pentagons[i], dots, 5)) {
                pent_dots[c] = j;
                c++;
            }
        }

        c -= 5;
        log(protocol, "В пятиугольнике " + to_string(i + 1) + " - " + to_string(c) + " точек: \n");

        for (int j = 1; j <= c; j++) {
            log(protocol, to_string(j) + ": ");
            log(protocol, dots[j][0]);
            log(protocol, " | ");
            log(protocol, dots[j][1]);
            log(protocol, "\n");
        }

        if (c > max_n) {
            max_n = c;
            max_pents[0] = pentagons[i];
            max_pents_n = 1;
        } else if (c == max_n){
            max_pents[max_pents_n] = pentagons[i];
            max_pents_n++;
        }
    }

    if (max_n == 0) {
        log(f, "Не найдено ни одного домика в котором бы содержались точки");
        return 0;
    }
    log(f, "Максимум точек в домике: " + to_string(max_n) + '\n');
    log(f, (max_pents_n == 1 ? "Домик" : "Домики"));
    log(f, " с максимальным количеством точек: \n");
    for (int i = 0; i < max_pents_n; i++) {
        log(f, to_string(i + 1) + ". ");
        print_figure(pentagons[i], dots, f, 5);
        log(f, "\n");
    }

    return 0;
}

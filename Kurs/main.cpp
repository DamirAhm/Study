#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

const int PRES = 5;
const int MAX_N = 100;

void out(fstream &file, string text) {
    cout << text;
    file << text;
}

void out(fstream &file, double n) {
    cout << fixed << setprecision(PRES) << setw(5) << n << " ";
    file << fixed << setprecision(PRES) << setw(5) << n << " ";
}

//каждый массив длинны 2
double len(double *a, double *b) {
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

//точки прямоугольника отсортированы
double rect_area(int *rect, double **dots) {
    return len(dots[rect[0]], dots[rect[1]]) * len(dots[rect[1]], dots[rect[2]]);
}

double dist(double *dot, double *line1, double *line2) {
    double A = line2[1] - line1[1];
    double B = line1[0] - line2[0];
    double C = line1[1] * line2[0] - line2[1] * line1[0];

    return abs(A * dot[0] + B * dot[1] + C) / sqrt(pow(A, 2) + pow(B, 2));
}

//каждый массив длинны 2
bool is_90(double *a, double *b, double *c) {
    double vec1[2] = {b[0] - a[0], b[1] - a[1]};
    double vec2[2] = {c[0] - b[0], c[1] - b[1]};

    double scalar = vec1[0] * vec2[0] + vec1[1] * vec2[1];

    return scalar == 0;
}

double *vec(double *a, double *b) {
    auto *vector = new double[2];
    vector[0] = b[0] - a[0];
    vector[1] = b[1] - a[1];

    return vector;
}

bool is_parallel_rects(int *rect_1, int *rect_2, double **dots) {
    auto v1 = vec(dots[rect_1[0]], dots[rect_1[1]]);
    auto v2 = vec(dots[rect_2[0]], dots[rect_2[1]]);

    return v1[1] * v2[0] == v2[1] * v1[0] || v1[1] * v2[1] == -1 * v1[0] * v2[0];
}

//матрица 4х2
int *sort_rectangle_dots(int *rectangle_dots, double **dots) {
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

    bool flat = (max_x + min_x + max_y + min_y) != 6;

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

bool is_rectangle(double *dot1, double *dot2, double *dot3, double *dot4) {
    return
            is_90(dot1, dot2, dot3) &&
            is_90(dot2, dot3, dot4) &&
            is_90(dot3, dot4, dot1) &&
            is_90(dot4, dot1, dot2);
}

//точки прямоугольника отсортированы
bool is_in_rectangle(double *dot, int *rect, double **dots) {
    return dot[0] >= dots[rect[0]][0] && dot[0] <= dots[rect[1]][0] && dot[1] <= dots[rect[0]][1] &&
           dot[1] >= dots[rect[2]][1];
}

bool have_crossing_area(int *rect1, int *rect2, double **dots) {
    for (int i = 0; i < 4; i++) {
        if (is_in_rectangle(dots[rect1[i]], rect2, dots)) return true;
    }
    return false;
}

//имеют как минимум одну внутреннюю точку
double find_crossing_area(int *rect1, int *rect2, double **dots) {
    int inner_points_amt = 0;
    bool inner_points[4];

    for (int i = 0; i < 4; i++) {
        inner_points[i] = false;
        if (is_in_rectangle(dots[rect1[i]], rect2, dots)) {
            inner_points_amt++;
            inner_points[i] = true;
        }
    }
    assert(inner_points_amt > 0 && (inner_points[0] || inner_points[1] || inner_points[2] || inner_points[3]));

    if (inner_points_amt >= 3) {
        return rect_area(rect1, dots);
    } else if (inner_points_amt == 2) {
        if (inner_points[0] && inner_points[1]) {
            return len(dots[rect1[0]], dots[rect1[1]]) * dist(dots[rect1[0]], dots[rect2[2]], dots[rect2[3]]);
        } else if (inner_points[1] && inner_points[2]) {
            return len(dots[rect1[1]], dots[rect1[2]]) * dist(dots[rect1[1]], dots[rect2[3]], dots[rect2[0]]);
        } else if (inner_points[2] && inner_points[3]) {
            return len(dots[rect1[2]], dots[rect1[3]]) * dist(dots[rect1[2]], dots[rect2[0]], dots[rect2[1]]);
        } else if (inner_points[3] && inner_points[0]) {
            return len(dots[rect1[3]], dots[rect1[0]]) * dist(dots[rect1[0]], dots[rect2[1]], dots[rect2[2]]);
        } else {
            assert(false);
        }
        //inner_points_amt == 1
    } else {
        if (inner_points[0]) {
            return dist(dots[rect1[0]], dots[rect2[1]], dots[rect2[2]]) *
                   dist(dots[rect1[0]], dots[rect2[2]], dots[rect2[3]]);
        } else if (inner_points[1]) {
            return dist(dots[rect1[1]], dots[rect2[2]], dots[rect2[3]]) *
                   dist(dots[rect1[1]], dots[rect2[3]], dots[rect2[0]]);
        } else if (inner_points[2]) {
            return dist(dots[rect1[2]], dots[rect2[3]], dots[rect2[0]]) *
                   dist(dots[rect1[2]], dots[rect2[0]], dots[rect2[1]]);
        } else {
            return dist(dots[rect1[3]], dots[rect2[0]], dots[rect2[1]]) *
                   dist(dots[rect1[3]], dots[rect2[1]], dots[rect2[2]]);
        }
    }
}

void read_dots(double **dots, int &N, fstream &in) {
    for (int i = 0; i < N; i++) {
        in >> setiosflags(ios::skipws) >> dots[i][0] >> dots[i][1];
        char c = ' ';
        while (true) {
            in >> resetiosflags(ios::skipws) >> c;
            if (c == '\r' || in.eof()) break;
        }
        if (in.eof()) {
            N = i + 1;
            break;
        }
    }
}

bool is_same_rects(int *rect1, int *rect2) {
    return rect1[0] == rect2[0] && rect1[1] == rect2[1] && rect1[2] == rect2[2] && rect1[3] == rect2[3];
}

void find_rectangles(double **dots, int **&rectangles, int N, int &f_rects, int &cur_size) {
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

                        assert(is_rectangle(dots[i], dots[j], dots[k], new_dot) == true);

                        int found = -1;
                        for (int o = 0; o < N; o++) {
                            if (dots[o][0] == new_dot_x && dots[o][1] == new_dot_y) {
                                found = o;
                                break;
                            }
                        }

                        if (found == -1 || found == i || found == j || found == k) continue;

                        auto *rectangle = new int[4];
                        rectangle[0] = i;
                        rectangle[1] = j;
                        rectangle[2] = k;
                        rectangle[3] = found;

                        rectangle = sort_rectangle_dots(rectangle, dots);

                        bool exists = false;
                        for (int o = 0; o < f_rects; o++) {
                            if (is_same_rects(rectangles[o], rectangle)) exists = true;
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

void print_rectangles(int **rectangles, int f_rects, double **dots) {
    for (int i = 0; i < f_rects; i++) {
        cout << i << " | ";
        for (int j = 0; j < 4; j++) {
            cout << dots[rectangles[i][j]][0] << " " << dots[rectangles[i][j]][1] << " | ";
        }
        cout << endl;
    }
}

bool have_common_dots(int *rect_1, int *rect_2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rect_1[i] == rect_2[j]) return true;
        }
    }
    return false;
}

int main() {
    fstream in("../in.txt");

    int N;
    in >> N;
    N = max(min(N, MAX_N), 0);

    auto **dots = new double *[N];
    auto **rectangles = new int *[2];
    int cur_size = 2;
    int f_rects = 0;

    for (int i = 0; i < N; i++) dots[i] = new double[2];

    read_dots(dots, N, in);
    find_rectangles(dots, rectangles, N, f_rects, cur_size);

    print_rectangles(rectangles, f_rects, dots);

    auto **crossing_areas = new double *[f_rects];
    for (int i = 0; i < f_rects; i++) crossing_areas[i] = new double[f_rects];

    for (int i = 0; i < f_rects; i++) {
        for (int j = 0; j < f_rects; j++) {
            if (i != j) {
                if (!is_same_rects(rectangles[i], rectangles[j]) && !have_common_dots(rectangles[i], rectangles[j])) {
                    if (is_parallel_rects(rectangles[i], rectangles[j], dots)) {
                        if (have_crossing_area(rectangles[i], rectangles[j], dots)) {
                            crossing_areas[i][j] = find_crossing_area(rectangles[i], rectangles[j], dots);
                        } else {
                            crossing_areas[i][j] = 0;
                        }
                    } else {
                        crossing_areas[i][j] = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < f_rects; i++) {
        for (int j = 0; j < f_rects; j++) {
            if (crossing_areas[i][j] != 0) {
                cout << i << " " << j << " " << crossing_areas[i][j] << endl;
            }
        }
    }

    return 0;
}

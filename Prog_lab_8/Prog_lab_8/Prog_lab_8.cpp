#include <fstream>
#include <iostream>
#include <algorithm>
#include "list.h"
#include "read_list.h"
#include "print_list.h"
#include "double_list.h"
#include "double_list_item.h"
#include "ALL.h"
#include "task.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ofstream out("out.txt", ios::out);
    ifstream L1("L1.txt");
    ifstream L2("L2.txt");
    {
        char x;
        L1 >> x >> x >> x;
        L2 >> x >> x >> x;
    }

    cout << "Здравствуйте, данную лабораторную работу выполнил Герасимов Артемий "
        "Альбертович, группа 1309"
        << endl
        << "Версия: 1.0" << endl
        << "Начало: 14.04.2022" << endl
        << "Конец: -" << endl
        << "Задание: 6в\n";
    out << "Здравствуйте, данную лабораторную работу выполнил Герасимов Артемий "
        "Альбертович, группа 1309"
        << endl
        << "Версия: 1.0" << endl
        << "Начало: 14.04.2022" << endl
        << "Конец: -" << endl
        << "Задание: 6в\n";

    double_list* L1_list = read_list(L1);
    cout << "Считанный L1: \n";
    out << "Считанный L1: \n";
    print_text(L1_list, out);
    cout << endl << endl;
    out << endl << endl;

    double_list* L2_list = read_list(L2);
    cout << "Считанный L2: \n";
    out << "Считанный L2: \n";
    print_text(L2_list, out);
    cout << endl;
    out << endl;

    strm* s = new strm();
    list_item* li = new list_item(s);
    list* l = new list(li);
    double_list_item* ni = new double_list_item(l);
    double_list* res = new double_list(ni);
    ALL all = { res, L1_list, L2_list };

    task(all);

    cout << endl;

    cout << "Результат: \n";
    out << "Результат: \n";
    print_line(res->h->el, out);
    cout << endl;
    out << endl;

    while (res->c != nullptr) {
        auto t = res->c;
        res->go_next();

        delete t;
    }
    delete res;
    while (L1_list->c != nullptr) {
        auto t = L1_list->c;
        L1_list->go_next();

        delete t;
    }
    delete L1_list;
    while (L2_list->c != nullptr) {
        auto t = L2_list->c;
        L2_list->go_next();

        delete t;
    }
    delete L2_list;

    return 0;
}


#include <fstream>
#include <iostream>
#include <algorithm>
#include "list.h"
#include "read_list.h"
#include "print_list.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ofstream out("out.txt", ios::out);
    ifstream in("in.txt");


    if (!in.is_open()) {
        cout << "Не получилось открыть файл" << endl;
    }

    cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир "
        "Альбертович, группа 1309"
        << endl
        << "Версия: 7.0" << endl
        << "Начало: 14.03.2022" << endl
        << "Конец: -" << endl
        << "Задание: 3.5.6\n";
    out << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир "
        "Альбертович, группа 1309"
        << endl
        << "Версия: 7.0" << endl
        << "Начало: 14.03.2022" << endl
        << "Конец: -" << endl
        << "Задание: 3.5.6\n";

    list* text = read_list(in);

    cout << "Считанный текст: \n";
    out << "Считанный текст: \n";
    print_list(text, out);
    cout << endl;
    out << endl;

    cout << "Задайте значение элемента (должно оканчиваться на !): ";
    strm* value = new strm('!');
    int len = 0;
    char c;
    cin >> c;

    while (c != value->mark) { 
        value->str[min(len++, N - 1)] = c; 
        cin >> c; 
    };
    value->mark = ' ';
    value->str[len] = ' ';

    list_item* item = nullptr;

    do {
        if (value->is_eq(text->c->b)) {
            item = text->c;
            break;
        }
        text->go_next();
    } while (text->c != nullptr);

    if (item == nullptr) {
        cout << "Элемента с таким значением не найдено";
        out << "Элемента с таким значением не найдено";

        return 0;
    }

    cout << "Задайте количество элементов: ";
    int n;
    cin >> n;

    list_item* prev = item;
    for (int i = 0; i < n; i++) {
        strm* strm_to_ins = new strm(' ');

        int x = 0;
        do { strm_to_ins->str[x] = value->str[x]; } while (value->str[x++] != value->mark);

        list_item* to_insert = new list_item(value);
        prev->insert_after(to_insert);
        prev = to_insert;
    }

    text->go_to_start();

    cout << "Получившийся текст: \n";
    out << "Получившийся текст: \n";
    print_list(text, out);

    //Второй список
    //очистка списка

    return 0;
}


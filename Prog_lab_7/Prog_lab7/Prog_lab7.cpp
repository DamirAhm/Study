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
    ifstream in2("in2.txt");


    if (!in.is_open()) {
        cout << "Не получилось открыть файл" << endl;
        return 0;
    } else if (!in2.is_open()) {
        cout << "Не получилось открыть второй файл" << endl;
        return 0;
    }
    {
        char x;
        in2 >> x >> x >> x;
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
    list* elements_to_add = read_list(in2);

    cout << "Считанный текст: \n";
    out << "Считанный текст: \n";
    print_list(text, out);
    cout << endl;
    out << endl;
    
    cout << "Считанныe элементы: \n";
    out << "Считанные элементы: \n";
    print_list(elements_to_add, out);
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
    for (int i = 0; i < n && elements_to_add->c != nullptr; i++) {
        auto element = elements_to_add->c;
        elements_to_add->go_next();
        list_item* to_insert = new list_item(element->b);

        prev->insert_after(to_insert);
        prev = to_insert;
    }

    if (elements_to_add->c == nullptr) {
        cout << "Во втором списке не хватило элементов" << endl;
        out << "Во втором списке не хватило элементов" << endl;
    }

    text->go_to_start();

    cout << "Получившийся текст: \n";
    out << "Получившийся текст: \n";
    print_list(text, out);



    text->go_to_start();
    elements_to_add->go_to_start();

    while (text->c != nullptr) {
        auto to_delete = text->c;
        text->go_next();

        delete to_delete->b;
        delete to_delete;
    }
    while (elements_to_add->c != nullptr) {
        auto to_delete = elements_to_add->c;
        elements_to_add->go_next();

        delete to_delete;
    }

    delete text;
    delete elements_to_add;

    return 0;
}


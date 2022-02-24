#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string replace_space_groups(string str, int len, ofstream &out) {
  bool last_was_space = false;

  string new_string = "";
  bool group_logged = false;

  for (int i = 0; i < len; i++) {
    if (str[i] == ' ') {
      if (!last_was_space) {
        new_string += str[i];
        last_was_space = true;
      } else if (!group_logged) {
        cout << "Найдена группа пробелов на позиции: " << i + 1 << endl;
        out << "Найдена группа пробелов на позиции: " << i + 1 << endl;
        group_logged = true;
      }
    } else {
      new_string += str[i];
      last_was_space = false;
      group_logged = false;
    }
  }

  return new_string;
}

int main() {
  ifstream in("in.txt");
  ofstream out("out.txt", ios::out);

  cout << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир "
          "Альбертович, группа 1309"
       << endl
       << "Версия: 6.0" << endl
       << "Начало: 14.02.2022" << endl
       << "Конец: -" << endl
       << "Задание: 16.б\n";
  out << "Здравствуйте, данную лабораторную работу выполнил Ахметзянов Дамир "
         "Альбертович, группа 1309"
      << endl
      << "Версия: 6.0" << endl
      << "Начало: 14.02.2022" << endl
      << "Конец: -" << endl
      << "Задание: 16.б\n";

  int flag = 0;

  cout << "Введите 1 если хотите работать с 1 версией программы и 2 если хотите работать со 2 версией" << endl;
  cin >> flag;
  
  string str = "";
  int len = 0;
  int pos = 0;
  bool found_start = false;
  
  while (!in.eof()) {
    pos++;
    char c;
    in >> resetiosflags(ios::skipws) >> c;
    if (flag == 2) {
      if (found_start) {
        if (c == '#') {
          cout << "Найден маркер на позиции - " << pos << ", заканчивается запись строки" << endl;
          break;
        };
        str += c;
        len++;
      } else if (c == '#') {
        found_start = true;
        cout << "Найден маркер на позиции - " << pos << ", начинается запись строки" << endl;
      }
    } else {
      str += c;
      len++;
    }
  }

  cout << "Считанная строка: \n" << str << endl;
  out << "Считанная строка: \n" << str << endl;

  string changed_str = replace_space_groups(str, len, out);

  cout << "Строка с замененными группами пробелов: \n" << changed_str;
  out << "Строка с замененными группами пробелов: \n" << changed_str;

  return 0;
}

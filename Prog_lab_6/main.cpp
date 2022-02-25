#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int n = 300;

struct strm {
  char mark;
  char s[n + 1];
};

strm replace_space_groups(strm &text, int to_read, ofstream &out) {
  bool last_was_space = false;
  bool group_logged = false;

  int i = 0;

  while (text.s[i] == ' ') i++;

  do {
    if (text.s[i] == ' ') {
      int j = 1;
      while (text.s[i + j] == ' ') j++; 
      
      if (text.s[i + j] == text.mark) return text;
      j--;
      int p = 1;
      while (text.s[i + j + p - 1] != text.mark) {
        text.s[i + p] = text.s[i + j + p];
        p++;
      }
    }
    i++;
  } while (text.s[i] != text.mark && (to_read == -1 || i < max(to_read, 0)));
    
  return text;
}

void print_text(strm text, ofstream &out) {
  int i = -1;
  do {
    i++;
    cout << text.s[i];
    out << text.s[i];
  } while (text.s[i] != text.mark);
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
  int to_read = -1;
  char mark = '*';

  cout << "Введите 1 если хотите работать по длинне и 2 если хотите работать с маркерами" << endl;
  cin >> flag;

  if (flag == 1) {
    cout << "Введите количество считываемых символов: ";
    cin >> to_read;
  } else {
    cout << "Введите маркер: ";
    cin >> mark;
  }
  
  strm text;
  text.mark = mark;
  
  int len = 0;
  int pos = 0;
  bool found_start = false;
  
  while (!in.eof() && len <= to_read) {
    pos++;
    char c;
    in >> resetiosflags(ios::skipws) >> c;
    if (flag == 2) {
      if (found_start) {
        if (c == text.mark) {
          cout << "Найден маркер на позиции - " << pos << ", заканчивается запись строки" << endl;
          text.s[len] = c;
          len++;
          break;
        };
        text.s[len] = c;
        len++;
      } else if (c == text.mark) {
        found_start = true;
        cout << "Найден маркер на позиции - " << pos << ", начинается запись строки" << endl;
      }
    } else {
      text.s[len] = c;
      len++;
    }
  }

  if (flag == 1 && to_read > len) {
    text.s[len] = text.mark;
  }
  
  cout << "Считанная строка: \n";
  out << "Считанная строка: \n";
  print_text(text, out);
  cout << endl;
  out << endl;

  replace_space_groups(text, to_read, out);

  cout << "Строка с замененными группами пробелов: \n";
  out << "Строка с замененными группами пробелов: \n";
  print_text(text, out);

  return 0;
}


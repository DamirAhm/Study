#include <fstream>
#include <iostream>

#include "list.h";
#include "print_list.h"

using namespace std;


void print_strm(strm* s, ofstream& out) {
	int c = 0;
	cout << " | ";
	out << " | ";
	while (c < s->len && s->str[c] != '\n') {
		cout << s->str[c];
		out << s->str[c];
		c++;
	};
	cout << " | ";
	out << " | ";
}

void print_line(list* l, ofstream& out) {
	l->go_to_start();

	if (l->c->el->len == 0) {
		cout << "Пустая строка" << endl;
		out << "Пустая строка" << endl;
		return;
	}

	while (l->c != nullptr) {
		print_strm(l->c->el, out);

		if (l->c->get_next() == nullptr) {
			cout << "-> NULL";
			out << "- >NULL";
			cout << endl;
			out << endl;
		}
		else {
			cout << "->";
			out << "->";
		}

		l->go_next();
	}

	l->go_to_start();
}

void print_text(double_list* l, ofstream& out) {
	l->go_to_start();

	while (l->c != nullptr) {
		print_line(l->c->el, out);

		if (l->c->get_next() == nullptr) {
			cout << "  |\n  V\n NULL";
			out << "  |\n  V\n NULL";
		}
		else {
			cout << "  |\n  V\n";
			out << "  |\n  V\n";
		}

		l->go_next();
	}

	l->go_to_start();
}

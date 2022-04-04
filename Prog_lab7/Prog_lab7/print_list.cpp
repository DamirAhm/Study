#include <fstream>
#include <iostream>

#include "list.h";
#include "print_list.h"

using namespace std;


void print_strm(strm* s, ofstream& out) {
	int c = 0;

	do {
		cout << s->str[c];
		out << s->str[c];
		c++;
	} while (s->str[c] != s->mark);
}

void print_list(list* l, ofstream& out) {
	while (l->c != nullptr) {
		print_strm(l->c->b, out);
		
		if (l->c->get_next() == nullptr) {
			cout << '#';
			out << '#';
			cout << "->NULL";
			out << "->NULL";
		}
		else {
			cout << l->c->b->str[l->c->b->len()];
			out << l->c->b->str[l->c->b->len()];
			cout << "->";
			out << "->";
		}
		
		l->go_next();
	}

	l->go_to_start();
}
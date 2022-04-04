#include <fstream>
#include <iostream>
#include <iomanip>
#include "list_item.h"
#include "strm.h"
#include "list.h"

using namespace std;

#ifndef READ_TEXT
#define READ_TEXT
list* read_list(ifstream &file) {
	strm* first_strm = new strm(' ');
	list_item* first_item = new list_item(first_strm);
	
	list* text = new list(first_item);

	int cstr_len = 0;

	while (!file.eof()) {
		char new_symbol;
		file >> resetiosflags(ios::skipws) >> new_symbol;

		text->c->b->str[min(cstr_len, N - 1)] = new_symbol;
		cstr_len++;

		if (new_symbol == ' ') {
			strm* new_strm = new strm(' ');
			list_item* new_item = new list_item(new_strm);
			cstr_len = 0;

			text->c->set_next(new_item);
			text->go_next();
		}
		else if (new_symbol == '#') {
			text->c->b->str[min(cstr_len - 1, N - 1)] = ' ';
			text->go_to_start();
			return text;
		}
	}

	return text;
}
#endif
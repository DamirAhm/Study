#include <fstream>
#include <iostream>
#include <iomanip>
#include "list_item.h"
#include "strm.h"
#include "list.h"
#include "double_list.h"
#include "double_list_item.h"

using namespace std;

#ifndef READ_TEXT
#define READ_TEXT
double_list* read_list(ifstream& file) {
	strm* first_strm = new strm();
	list_item* first_item = new list_item(first_strm);

	list* first_line = new list(first_item);

	double_list_item* first_line_item = new double_list_item(first_line);

	double_list* text = new double_list(first_line_item);

	while (!file.eof()) {
		list* cur_line = text->c->el;
		strm* cur_block = cur_line->c->el;

		char new_symbol;
		file >> resetiosflags(ios::skipws) >> new_symbol;

		if (new_symbol == '\n') {
			if (text->c->el->c->el->len == 0) {
				text->c->el->go_to_start();
				while (text->c->el->c->get_next() != nullptr && text->c->el->c->get_next()->el->len != 0) text->c->el->go_next();

				text->c->el->c->set_next(nullptr);
			}

			strm* new_strm = new strm();
			list_item* new_item = new list_item(new_strm);
			list* new_line = new list(new_item);
			double_list_item* new_line_item = new double_list_item(new_line);

			text->c->set_next(new_line_item);
			text->go_next();
		}
		else {
			if (cur_block->len == N - 1) {
				strm* new_strm = new strm();
				list_item* new_item = new list_item(new_strm);

				cur_line->c->set_next(new_item);
				cur_line->go_next();
			}

			cur_block->str[cur_block->len] = new_symbol;
			cur_block->len++;
			
			if (file.eof()) {
				break;
			}
		}
	}

	auto last_el = text->c->el->c;
	text->c->el->go_to_start();
	while (text->c->el->c->get_next() != last_el) text->c->el->go_next();
	text->c->el->c->set_next(nullptr);

	return text;
}
#endif
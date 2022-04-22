#include "double_list_item.h"
#include "double_list.h"

double_list::double_list(double_list_item* h) {
	this->h = h;
	this->c = h;
}

void double_list::go_next() {
	this->c = this->c->get_next();
}

void double_list::go_to_start() {
	this->c = this->h;
}

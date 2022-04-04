#include "list_item.h"
#include "list.h"

list::list(list_item* h) {
	this->h = h;
	this->c = h;
}

void list::go_next() {
	this->c = this->c->get_next();
}

void list::go_to_start() {
	this->c = this->h;
}

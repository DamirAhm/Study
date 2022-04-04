#include "list_item.h"
list_item::list_item(strm* b)
{
	this->b = b;
	this->next = nullptr;
}

void list_item::go_to_start()
{
}

void list_item::set_next(list_item* next) {
	this->next = next;
}

list_item* list_item::get_next() {
	return this->next;
}

void list_item::insert_after(list_item* item) {
	list_item* next = this->get_next();

	this->set_next(item);
	item->set_next(next);
}

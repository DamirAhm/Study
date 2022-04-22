#include "double_list_item.h";

double_list_item::double_list_item(list* b)
{
	this->el = b;
	this->next = nullptr;
}

void double_list_item::set_next(double_list_item* next) {
	this->next = next;
}

double_list_item* double_list_item::get_next() {
	return this->next;
}

void double_list_item::insert_after(double_list_item* item) {
	double_list_item* next = this->get_next();

	this->set_next(item);
	item->set_next(next);
}

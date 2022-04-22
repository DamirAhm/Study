#pragma once

#ifndef double_listItemType
#define double_listItemType
#include "strm.h"
#include "list.h"

class double_list_item {
public:
	double_list_item(list* b);
	list* el;
	double_list_item* next;

	void set_next(double_list_item* next);
	double_list_item* get_next();
	void insert_after(double_list_item* item);
};
#endif
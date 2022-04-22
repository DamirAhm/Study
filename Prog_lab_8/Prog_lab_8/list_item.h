#pragma once

#ifndef TextType
#define TextType
#include "strm.h"

class list_item {
public:
	list_item(strm* b);
	strm* el;
	list_item* next;

	void set_next(list_item* next);
	list_item* get_next();
	void insert_after(list_item* item);
};
#endif
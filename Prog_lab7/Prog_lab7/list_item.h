#pragma once

#ifndef TextType
#define TextType
#include "strm.h"

const int M = 50;
class list_item {
public: 
	list_item(strm* b);
	strm* b;
	list_item* next;

	void go_to_start();
	void set_next(list_item* next);
	list_item* get_next();
	void insert_after(list_item* item);
};
#endif
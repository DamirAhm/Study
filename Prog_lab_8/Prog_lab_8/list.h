#pragma once
#ifndef LIST_TYPE
#define LIST_TYPE
#include "list_item.h"

class list {
public:
	list(list_item* h);
	list_item* h{ nullptr };
	list_item* c{ nullptr };

	void go_next();

	void go_to_start();

	bool includes(strm* item);
};
#endif
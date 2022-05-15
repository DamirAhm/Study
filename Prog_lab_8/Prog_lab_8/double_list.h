#pragma once
#ifndef double_list_TYPE
#define double_list_TYPE
#include "double_list_item.h"

class double_list {
public:
	double_list(double_list_item* h);
	double_list_item* h{ nullptr };
	double_list_item* c{ nullptr };

	void go_next();

	void go_to_start();

	bool includes(strm* item);
};
#endif
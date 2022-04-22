#pragma once
#include "strm.h";

bool strm::is_eq(strm* b) {
	if (this->len != b->len) return false;

	int c = 0;

	while (c != this->len) {
		if (this->str[c] != b->str[c]) return false;
		c++;
	}

	return true;
}
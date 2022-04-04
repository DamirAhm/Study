#include "strm.h"

strm::strm(char mark) {
	this->mark = mark;
}

bool strm::is_eq(strm* b) {
	if (this->len() != b->len()) return false;
		
	int c = 0;

	while (this->str[c] != this->mark && b->str[c] != b->mark) {
 		if (this->str[c] != b->str[c]) return false;
		c++;
	}

	return true;
}
int strm::len() {
	int len = -1;
	do {} while (this->str[++len] != this->mark);

	return len;
}
;
#pragma once

const int N = 200;

#ifndef LineType
#define LineType

class strm {
public:
	strm(char mark);
	char str[N] = {};
	char mark;

	bool is_eq(strm* b);
	int len();
};

#endif // !Line

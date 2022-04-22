#pragma once

const int N = 10;

#ifndef LineType
#define LineType

class strm {
public:
	char str[N] = {};

	int len = 0;

	bool is_eq(strm* b);
};

#endif // !Line

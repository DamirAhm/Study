#pragma once
#include <fstream>
#include "double_list.h"

using namespace std;

#ifndef PRINT_TEXT
#define PRINT_TEXT
void print_text(double_list* l, ofstream& out);
#endif

#ifndef PRINT_LINE
#define PRINT_LINE
void print_line(list* l, ofstream& out);
#endif

#ifndef PRINT_STRM
#define PRINT_STRM
void print_strm(strm* s, ofstream& out);
#endif
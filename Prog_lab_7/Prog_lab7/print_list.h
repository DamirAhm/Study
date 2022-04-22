#pragma once
#include <fstream>
#include "list.h"

using namespace std;

#ifndef PRINT_LIST
#define PRINT_LIST
void print_list(list* l, ofstream& out);
#endif

#ifndef PRINT_STRM
#define PRINT_STRM
void print_strm(strm* s, ofstream& out);
#endif
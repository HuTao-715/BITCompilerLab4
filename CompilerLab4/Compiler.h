#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <vector>
#include "Word.h"
using namespace std;

class Compiler;

class Compiler
{
public:
	char* path;//文件路径
	vector<Word> words;
	Compiler();
	Compiler(char* path);
	void compile();
};

#endif
#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include <iostream>
#include <vector>
#include "Word.h"

using namespace std;

class Word;

bool isNumber(char ch);
bool isLetter_small(char ch);
bool isLetter_big(char ch);
bool isLetter(char ch);
bool calFirst(int p1, int p2);
bool compareWord(Word w1, Word w2);
long long stringToLL(string s);
int getSize(string type);

template <typename T> T getPop(vector<T>& vec) {
	T temp = vec.back();
	vec.pop_back();
	return temp;
}

#endif
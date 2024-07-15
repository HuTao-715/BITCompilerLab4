#include "public.h"

bool isNumber(char ch) {
	if (ch < '0' || ch > '9') {
		return false;
	}
	return true;
}
bool isLetter_small(char ch) {
	if (ch < 'a' || ch > 'z') {
		return false;
	}
	return true;
}
bool isLetter_big(char ch) {
	if (ch < 'A' || ch > 'Z') {
		return false;
	}
	return true;
}
bool isLetter(char ch) {
	return isLetter_big(ch) || isLetter_small(ch);
}
bool calFirst(int p1, int p2) {//p1是否先于p2计算，p1在栈中，p2要入栈
	if (p1 < p2)
		return false;
	if (p1 == p2 && p1 == 6)
		return false;//单目运算右结合
	return true;
}

bool compareWord(Word w1, Word w2) {
	if (w1.priority != w2.priority) {
		return w1.priority < w2.priority;
	}
	return (w1.combine == "left");
}

long long stringToLL(string s) {
	int positive = 1;
	long long sum = 0;
	int i;
	if (s[0] == '-') {
		positive = -1;
		i = 1;
	}
	else {
		i = 0;
	}
	for (;i < s.size();i++) {
		if (s[i] > '9' || s[i] < '0') {
			//error;
		}
		else {
			sum = sum * 10 + s[i] - '0';
		}
	}
	return sum * positive;
}

int getSize(string type) {
	if (type == "int") {
		return 4;
	}
	cout << "error: type does not exist\n";
	return 0;
}
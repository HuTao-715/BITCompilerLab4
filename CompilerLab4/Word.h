#ifndef __WORD_H__
#define __WORD_H__

#include <iostream>
#include "FA.h"
#include "lab3FA.h"
// #include "Grammar.h"
#include "SynAnalyzer.h"

using namespace std;

class GrammarAnalyzer;
class SynAnalyzer;

class Word;
class WordAnalyzer;

class Word {
public:
	string type;
	string value;
	int priority;
	string combine;
	Word();
	Word(string type, string value, int priority = -1);
	void testPrint();
	void setPriority(int prio, string comb = "left");
};

class WordAnalyzer {
public:
	FA* fa;
	FANode* state;
	// GrammarAnalyzer* grammar_analyzer;
	SynAnalyzer* syn_analyzer;

	char word[2000];
	int t = 0;

	const int keyword_count = 8;
	string keyword[8] = { "int","return","void","if","else","while","break","continue" };

	WordAnalyzer();
	void analyze(char ch);
	void setSynAnalyzer(SynAnalyzer* a);
};

#endif
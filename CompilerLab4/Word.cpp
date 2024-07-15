#include "Word.h"
#include "public.h"

//Word单词类
Word::Word() : type(""), value(""), priority(-1) {}
Word::Word(string type, string value, int priority) :type(type), value(value), priority(priority) {}
void Word::testPrint() {
	cout << "Word<" << type << ", " << value << ">\n";
	// cout << "type: " << type << " , value: " << value << " , priority: " << priority << endl;
}
void Word::setPriority(int prio, string comb) {
	priority = prio;
	combine = comb;
}

//词法分析器
WordAnalyzer::WordAnalyzer() :syn_analyzer(), fa(new lab3FA()), state(fa->st) {}
void WordAnalyzer::analyze(char ch) {
	vector<FANode*> next = state->input(ch);

	// word[t] = '\0';
	// cout << state->id << "," << state->type << ":" << word;
	// cout << endl;
	// word[t] = ' ';

	if (next.size() == 0) {
		cout << "input is illegal" << ch << endl;
		t = 0;
		return;
	}
	state = next[0];
	if (state->type == "acc") {
		word[t] = '\0';
		//判断是否关键字
		bool notkey = true;
		if (state->info == "id") {
			for (int i = 0;i < keyword_count;i++) {
				if (string(word) == keyword[i]) {
					// Word(word, word).testPrint();
					// grammar_analyzer->analyze(Word(word, word));
					syn_analyzer->input(Word(word, word));
					notkey = false;
					break;
				}
			}
		}
		if (notkey) {
			// Word(state->info, word).testPrint();
			// grammar_analyzer->analyze(Word(state->info, word));
			syn_analyzer->input(Word(state->info, word));
		}
		//是否重新输入该字符
		bool backspace = state->backspace;
		state = fa->st;
		t = 0;
		if (backspace)
			analyze(ch);
	}
	else if (state->type == "err") {
		word[t] = '\0';
		cout << state->info << ":" << word << '\n';

		bool backspace = state->backspace;
		state = fa->st;
		t = 0;
		if (backspace)
			analyze(ch);
	}
	else if (state->type == "blank") {
		state = fa->st;
		t = 0;
		return;
	}
	else {
		word[t++] = ch;
	}
}

void WordAnalyzer::setSynAnalyzer(SynAnalyzer* a) {
	syn_analyzer = a;
}
#include "Compiler.h"

using namespace std;

int main(int argc, char* argv[]) {
	// char temp[] = "input.txt";
	// Compiler compiler(temp);

	// cout << argv[1] << endl;
	Compiler compiler(argv[1]);
	compiler.compile();

	//WordAnalyzer wordAnalyzer;
	//string s = ";";
	//Word word = wordAnalyzer.getWord(s);
	//cout << "type:" << word.type<<"; ";
	//cout << "value:" << word.value<<"; ";
	//cout << "priority:" << word.priority << ";\n";
}


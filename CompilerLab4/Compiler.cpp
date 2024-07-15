#include <fstream>
#include <cassert>

#include "public.h"
#include "Compiler.h"
// #include "Grammar.h"
#include "Syntax.h"
#include "SynAnalyzer.h"

using namespace std;

//Compiler 编译器
Compiler::Compiler() {
	path = NULL;
}
Compiler::Compiler(char* path) {
	this->path = path;
};
void Compiler::compile() {
	// 输入产生式
	// string s;
	// vector<Generator*> gens;
	// while (!cin.eof()) {
	// 	getline(cin, s);
	// 	if (s == "") {
	// 		continue;
	// 	}
	// 	gens.push_back(new Generator(s));
	// }
	// SynAnalyzer syn_analyzer(gens[0]->left, gens);
	SynAnalyzer syn_analyzer;
	//--------------------------------------------
	

	//test

	// syn_analyzer.printGotoAction();
	// cout << syn_analyzer.ACTION[2]["int"].first;
	// int no[5] = { 0,1,2,3 };
	// for (int i = 0;i < 4;i++) {
	// 	syn_analyzer.printItemSet(syn_analyzer.no_reverse[i]);
	// }
	// syn_analyzer.printDirectInitCode();
	// return;

	//test end

	//输出预定义内容
	cout << ".intel_syntax noprefix\n"
		<< ".global main\n"
		<< ".extern printf\n"
		<< ".data\n"
		<< "format_str:\n"
		<< "\t.asciz \"%d\\n\"\n"
		<< ".text\n\n";
	
	//打开文件
	ifstream iFile(path);
	assert(iFile.is_open());

	//读入文件划分单词
	WordAnalyzer word_analyzer;
	word_analyzer.setSynAnalyzer(&syn_analyzer);
	char ch;
	while (1) {
		ch = iFile.get();
		// cout << "\nchar:" << ch << '\n';
		word_analyzer.analyze(ch);
		if (ch == EOF) {//文件结尾
			syn_analyzer.input(Word("$", ""));
			iFile.close();//关闭文件
			break;
		}
	}
}
#ifndef __SYNTAX_H__
#define __SYNTAX_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "Word.h"

using namespace std;

class Word;

//非终结符
class NonTerminal {
public:
    string name;//名称
    NonTerminal(string name);
};

//终结符
class Terminal {
public:
    string name;
    string value;

    Terminal(string name);
    Terminal(string name, string value);
};
//语义动作
class Action {
public:
    string actions;
    Action(string actions);
};

//产生式
class GeneratorItem {
public:
    string type;
    NonTerminal* c_non;
    Terminal* c_ter;
    Action* c_act;

    GeneratorItem(NonTerminal* item);
    GeneratorItem(Terminal* item);
    GeneratorItem(Action* item);
};

class Generator {
public:
    NonTerminal* left;
    vector<GeneratorItem*> right;
    int len;//只计算终结符和非终结符

    Generator(string s);
    void print();
    void print(ofstream &ofile);
};

//LR项目
class LRItem {
public:
    Generator* gen;
    int point;
    set<string> look_forwards;

    LRItem(){};
    LRItem(Generator* gen, int point, set<string> look_forwards);
    void adjustPoint();//调整点至下一个终结符或非终结符

    void print();

    bool operator<(const LRItem& b) const {
        if (gen != b.gen)
            return gen < b.gen;
        if (point != b.point)
            return point < b.point;
        return look_forwards < b.look_forwards;
    }
    bool operator==(const LRItem& b)const {
        return gen == b.gen && point == b.point && look_forwards == b.look_forwards;
    }
};

//语法树
class SynTree {
public:
    string type, name;
    vector<SynTree*> sons;
    map<string, string> attrs;
};

#endif
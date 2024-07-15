#ifndef __SYNANALYZER_H__
#define __SYNANALYZER_H__

#include "Syntax.h"
#include "Dspace.h"
#include "public.h"

class Generator;
class NonTerminal;
class LRItem;
class SynTree;

//命令
class Command {
public:
    vector<string> args;
    Command(string s);
    void print();
};

//分析器
class SynAnalyzer {
public:
    //构造函数
    SynAnalyzer();
    SynAnalyzer(NonTerminal* start, vector<Generator*>& gens);

    //-------------------------------------------
    //文法部分
    //产生式、符号编号
    vector<Generator*> gens;
    map<Generator*, int> gens_no;
    set<string> ters, nons;
    NonTerminal* start;

    //FIRST FOLLOW
    map<string, set<string>> FirstSet;
    map<string, set<string>> FollowSet;
    //FIRST
    void initFirstSet(vector<Generator*>& gens);
    void printFirstSet();
    set<string> getFirst(Generator* gen, int s);//从gen.right[s]开始的串的First集
    //FOLLOW
    void initFollowSet(NonTerminal* start, vector<Generator*> gens);
    void printFollowSet();

    //----------------------------------------------------
    //文法分析部分
    //项目集、编号
    set<set<LRItem> > C;
    map<set<LRItem>, int> item_set_no;
    map<int, set<LRItem>> no_reverse;
    int item_set_count;
    //打印项目集
    void printItemSet(set<LRItem> items);

    //状态转换表
    vector<map<string, int> > GO;
    vector<map<string, pair<string, int> > > ACTION;
    vector<map<string, int> > GOTO;
    //closure、GO、构建LR表
    set<LRItem> closureLR1(set<LRItem> items);
    set<LRItem> GoLR1(set<LRItem> items, string input);
    void getLR1();
    void printGotoAction();//输出LR表
    
    //栈
    int stack_t = 0;
    static const int STACK_MAX = 10000;
    int stack_state[STACK_MAX];
    SynTree* stack_pointer[STACK_MAX];
    
    //接受输入
    void input(Word input);

    //--------------------------------------------------------
    //语义分析部分
    //定义域
    map<string, Dspace*> Dmap;
    int D_count = 0;
    //标签
    int L_count = 0;

    void scan(SynTree* root);//扫描语法树
    SynTree* getTarget(SynTree* root, string id);//语法树的id节点，id可以为-1代表根节点

    //---------------------------------------------------------
    //输出直接初始化代码
    void printDirectInitCode();
};

#endif
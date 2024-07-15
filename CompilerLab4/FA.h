#ifndef __FA_H__
#define __FA_H__

#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class FANode;
// class FA;

//FA结点
class FANode{
public:
    int id;
    string type;
    string info;//acc类型或者err提示
    bool backspace;//是否退还一个字符

    vector<FANode*> f[131];//转换函数 0-127:ASCII,128:EOF,129:空串,130:默认

    FANode();
    FANode(int id, string type);
    FANode(int id, string type, string info);
    FANode(int id, string type, vector<FANode*> f[130]);
    void add(char ch, FANode* node);
    void add(char l, char r, FANode* node);
    void addDefault(FANode* node);
    void acc(string info, bool backspace = true);
    void err(string info, bool backspace = true);
    void blank();
    vector<FANode*> input(char ch);
};

//FA图
class FA{
public:
    vector<FANode*> nodes;
    FANode* st;

    FA();
    void addNode(FANode* node);
};

#endif
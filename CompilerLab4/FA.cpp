#include "FA.h"

//FANode:FA结点
FANode::FANode() {}
FANode::FANode(int id, string type) : id(id), type(type) {}
FANode::FANode(int id, string type, string info) : id(id), type(type), info(info) {}
FANode::FANode(int id, string type, vector<FANode*> f[130]) :id(id), type(type) {
    for (int i = 0;i < 130;i++) {
        this->f[i] = f[i];
    }
}
void FANode::add(char ch, FANode* node) {
    if (ch == EOF)
        f[128].push_back(node);
    else
        f[ch].push_back(node);
}
void FANode::add(char l, char r, FANode* node) {
    for (char i = l;i <= r;i++) {
        f[i].push_back(node);
    }
}
void FANode::addDefault(FANode* node) {
    f[130].push_back(node);
}
void FANode::acc(string info, bool backspace) {
    type = "acc";
    this->info = info;
    this->backspace = backspace;
}
void FANode::err(string info, bool backspace) {
    type = "err";
    this->info = info;
    this->backspace = backspace;
}
void FANode::blank() {
    type = "blank";
}
vector<FANode*> FANode::input(char ch) {
    int id;
    if (ch == EOF) 
        id = 128;
    else
        id = ch;

    if (f[id].size() != 0) {
        return f[id];
    }
    return f[130];
}

//FA:FA图
FA::FA() {}
void FA::addNode(FANode* node) {
    nodes.push_back(node);
}
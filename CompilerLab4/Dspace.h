#ifndef __DSPACE_H__
#define __DSPACE_H__

#include <iostream>
#include <map>
using namespace std;

//变量信息
class VarInfo {
public:
    string type, name;
    int addr;
    VarInfo() {};
    VarInfo(string type, string name, int addr);
};
//函数信息
class FunInfo {
public:
    string type, name;
    string arg_size, var_size;
    FunInfo() {}
    FunInfo(string type, string name, string arg_size, string var_size);
    void print();
};
//定义域
class Dspace {
public:
    string name;
    Dspace* fa;//父表
    map<string, VarInfo> vars;//该级变量
    map<string, FunInfo> funs;//该级函数
    int addr_up = 8, addr_down = 0;//大端地址，0被ebp使用, 4返回地址，向上ebp+x可知，用完就加 x1 = x + this.size；向下ebp-x不可知，用next之前加，x1 = x + next.size 

    Dspace(Dspace* fa);
    
    void claimFun(string type, string name, string arg_size);
    string defFun(string name, string var_size);
    void createVar(string type, string name);
    void createArg(string type, string name);

    //获取变量
    bool get(string name, int& time, int& addr, string& type);
    string getVar(string name);
    string setVar(string name);
    string setVar(string name, string C);
    bool getFun(string name, FunInfo& info);
    string callFun(string name);
};

#endif
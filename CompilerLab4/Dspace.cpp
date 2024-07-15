#include "Dspace.h"
#include "public.h"

//VarInfo
VarInfo::VarInfo(string type, string name, int addr) :type(type), name(name), addr(addr) {}

//FunInfo
FunInfo::FunInfo(string type, string name, string arg_size, string var_size) :type(type), name(name), arg_size(arg_size), var_size(var_size) {}
void FunInfo::print() {
    cout << "fun: " << type << " " << name << "(" << arg_size << "){" << var_size << "}\n";
}

//Dspace
Dspace::Dspace(Dspace* fa) :fa(fa) {}

void Dspace::claimFun(string type, string name, string arg_size) {
    // cout << "arg_size: " << arg_size << endl;
    if (funs.count(name)) {
        cout << "error: function-redefined: " << name << endl;
        return;
    }
    funs[name] = FunInfo(type, name, arg_size, "");
    // cout << this->name << " create ";funs[name].print();
}
string Dspace::defFun(string name, string var_size) {
    if (!funs.count(name)) {
        cout << "error: function-unclaimed: " << name << endl;
        return "";
    }
    funs[name].var_size = var_size;
    return name + ":\npush ebp\nmov ebp, esp\nsub esp, " + var_size + "\n";//分配变量空间
}

void Dspace::createVar(string type, string name) {
    // cout << "test:arg-name: " << name << endl;
    if (vars.count(name)) {
        cout << "error:var-redefined: " << name << "\n";
        return;
    }
    addr_down += getSize(type);
    vars[name] = VarInfo(type, name, -addr_down);
}

void Dspace::createArg(string type, string name) {
    if (vars.count(name)) {
        cout << "error:arg-redefined\n";
        return;
    }
    vars[name] = VarInfo(type, name, addr_up);
    addr_up += getSize(type);
}

bool Dspace::get(string name, int& time, int& addr, string& type) {
    //如果当前表找不到：如果没有父表，则设为-1，返回false
    //否则交给父表处理，然后把 time+1
    if (!vars.count(name)) {
        if (fa == NULL) {
            time = addr = -1;
            return false;
        }
        bool finded = fa->get(name, time, addr, type);
        time++;
        return finded;
    }
    //如果当前表找得到，让time等于0，返回相对于当前表的地址
    else {
        time = 0;
        addr = vars[name].addr;
        type = vars[name].type;
        return true;
    }
}
string Dspace::getVar(string name) {
    int time, addr;
    string type;
    if (!get(name, time, addr, type)) {
        return "";
    }
    //先把基准值赋给eax，然后重复time次间接寻址，最后直接寻址
    //每次参数压栈时，把上一个ebp的值压在栈顶，然后esp变为新的ebp
    //这里eax等于ebp，所以eax就是栈顶的上一个ebp，并且取到新的eax等于上一个ebp，所以可以循环往上取
    string ans = "mov eax, ebp\n";
    for (int i = 0;i < time; i++) {
        ans += "mov eax, DWORD PTR [eax]\n";
    }
    if (addr < 0) {
        ans += "mov eax, DWORD PTR[eax" + to_string(addr) + "]\n" +
            "push eax\n";
    }
    else {
        ans += "mov eax, DWORD PTR[eax + " + to_string(addr) + "]\n" +
            "push eax\n";
    }
    return ans;
}

string Dspace::setVar(string name) {
    int time, addr;
    string type;
    if (!get(name, time, addr, type)) {
        return "";
    }
    //先把基准值赋给eax，然后重复time次间接寻址，最后直接寻址
    //每次参数压栈时，把上一个ebp的值压在栈顶，然后esp变为新的ebp
    //这里eax等于ebp，所以eax就是栈顶的上一个ebp，并且取到新的eax等于上一个ebp，所以可以循环往上取
    string ans = "mov eax, ebp\n";
    for (int i = 0;i < time; i++) {
        ans += "mov eax, DWORD PTR [eax]\n";
    }
    if (addr < 0) {
        ans += "pop DWORD PTR[eax" + to_string(addr) + "]\n" +
            "push DWORD PTR[eax" + to_string(addr) + "]\n";
    }
    else {
        ans += "pop DWORD PTR[eax + " + to_string(addr) + "]\n" +
            "push DWORD PTR[eax + " + to_string(addr) + "]\n";
    }
    return ans;
}

string Dspace::setVar(string name, string C) {
    int time, addr;
    string type;
    if (!get(name, time, addr, type)) {
        return "";
    }
    //先把基准值赋给eax，然后重复time次间接寻址，最后直接寻址
    //每次参数压栈时，把上一个ebp的值压在栈顶，然后esp变为新的ebp
    //这里eax等于ebp，所以eax+4就是栈顶的上一个ebp，并且取到新的eax等于上一个ebp，所以可以循环往上取
    string ans = "mov eax, ebp\n";
    for (int i = 0;i < time; i++) {
        ans += "mov eax, DWORD PTR [eax + 4]\n";
    }
    if (addr < 0) {
        ans += "mov DWORD PTR[eax" + to_string(addr) + "], " + C + "\npush " + C + "\n";
    }
    else {
        ans += "mov DWORD PTR[eax + " + to_string(addr) + "], " + C + "\npush " + C + "\n";
    }
    return ans;
}

bool Dspace::getFun(string name, FunInfo& info) {
    //如果当前表找不到：如果没有父表，则设为-1，返回false
    //否则交给父表处理
    if (!funs.count(name)) {
        if (fa == NULL) {
            return false;
        }
        bool finded = fa->getFun(name, info);
        return finded;
    }
    //如果当前表找得到，返回信息
    else {
        info = funs[name];
        return true;
    }
}

string Dspace::callFun(string name) {
    if (name == "println_int") {
        return "push offset format_str\ncall printf\nadd esp, 8\npush eax\n";
    }

    FunInfo info;
    if (!getFun(name, info)) {
        cout << "error: function undefined: " << name << endl;
        return "";
    }

    string ans = "call " + name + "\n";
    ans += "add esp, " + info.arg_size + "\npush eax\n";
    return ans;
}
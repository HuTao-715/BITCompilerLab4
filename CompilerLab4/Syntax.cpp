#include "Syntax.h"
#include "Word.h"
#include "public.h"

//NonTerminal
NonTerminal::NonTerminal(string name) :name(name) {}

//Terminal
Terminal::Terminal(string name) :name(name) {}
Terminal::Terminal(string name, string value) :name(name), value(value) {}

//Action
Action::Action(string actions) :actions(actions) {}

//GeneratorItem
GeneratorItem::GeneratorItem(NonTerminal* item) :c_non(item), type("non") {}
GeneratorItem::GeneratorItem(Terminal* item) :c_ter(item), type("ter") {}
GeneratorItem::GeneratorItem(Action* item) :c_act(item), type("act") {}

//Generator
Generator::Generator(string s) {
    int state = 0;
    char temp[2000];
    int id = 0;
    len = 0;
    while (id < s.size()) {
        if (s[id] == '[') {
            int t = 0;
            while (s[++id] != ']') {
                temp[t++] = s[id];
            }
            temp[t] = '\0';
            id++;

            if (state == 0) {
                left = new NonTerminal(temp);
            }
            else {
                right.push_back(new GeneratorItem(new NonTerminal(temp)));
                len++;
            }
        }
        else if (s[id] == '-' && s[id + 1] == '>') {
            state = 1;
            id += 2;
        }
        else if (s[id] == '<') {
            int t = 0;
            while (s[++id] != '>') {
                temp[t++] = s[id];
            }
            temp[t] = '\0';
            id++;
            right.push_back(new GeneratorItem(new Terminal(temp)));
            len++;
        }
        else if (s[id] == '{') {
            int t = 0;
            while (s[++id] != '}') {
                temp[t++] = s[id];
            }
            id++;
            temp[t] = '\0';
            right.push_back(new GeneratorItem(new Action(temp)));
        }
        else {
            id++;
        }
    }
}

void Generator::print() {
    cout << "[" << left->name << "] ->";
    for (GeneratorItem* item : right) {
        cout << " ";
        if (item->type == "ter") {
            cout << "<" << item->c_ter->name << ">";
        }
        else if (item->type == "non") {
            cout << "[" << item->c_non->name << "]";
        }
        else if (item->type == "act") {
            cout << "{" << item->c_act->actions << "}";
        }
    }
}

void Generator::print(ofstream& ofile) {
    ofile << "[" << left->name << "] ->";
    for (GeneratorItem* item : right) {
        ofile << " ";
        if (item->type == "ter") {
            ofile << "<" << item->c_ter->name << ">";
        }
        else if (item->type == "non") {
            ofile << "[" << item->c_non->name << "]";
        }
        else if (item->type == "act") {
            ofile << "{" << item->c_act->actions << "}";
        }
    }
}

//LRItem
LRItem::LRItem(Generator* gen, int point, set<string> look_forwards) :gen(gen), point(point), look_forwards(look_forwards) {
    adjustPoint();
}

void LRItem::adjustPoint() {
    while (point < gen->right.size()
        && gen->right[point]->type != "ter"
        && gen->right[point]->type != "non") {
        point++;
    }
}

void LRItem::print() {
    gen->print();
    cout << ", " << point << ", <";
    for (string s : look_forwards) {
        cout << s <<",";
    }
    cout << ">";
}




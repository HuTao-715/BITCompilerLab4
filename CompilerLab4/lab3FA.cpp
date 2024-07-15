#include "lab3FA.h"

lab3FA::lab3FA() : FA() {
    for (int i = 0; i < 102; i++) {
        addNode(new FANode(i, "normal"));
    }

    nodes[0]->type = "st";
    st = nodes[0];

    nodes[0]->add(' ', nodes[99]);
    nodes[0]->add('\t', nodes[99]);
    nodes[0]->add('\n', nodes[99]);
    nodes[0]->add(EOF, nodes[100]);
    nodes[99]->blank();

    //)
    nodes[0]->add(')', nodes[1]);
    nodes[1]->addDefault(nodes[2]);
    nodes[2]->acc(")");

    //(
    nodes[0]->add('(', nodes[3]);
    nodes[3]->addDefault(nodes[4]);
    nodes[4]->acc("(");

    //}
    nodes[0]->add('}', nodes[5]);
    nodes[5]->addDefault(nodes[6]);
    nodes[6]->acc("}");

    //{
    nodes[0]->add('{', nodes[7]);
    nodes[7]->addDefault(nodes[8]);
    nodes[8]->acc("{");

    //;
    nodes[0]->add(';', nodes[9]);
    nodes[9]->addDefault(nodes[10]);
    nodes[10]->acc(";");

    //^
    nodes[0]->add('^', nodes[11]);
    nodes[11]->addDefault(nodes[12]);
    nodes[12]->acc("^");

    //|、||
    nodes[0]->add('|', nodes[13]);
    nodes[13]->add('|', nodes[51]);
    nodes[13]->addDefault(nodes[14]);
    nodes[14]->acc("|");
    nodes[51]->addDefault(nodes[52]);
    nodes[52]->acc("||");

    //&、&&
    nodes[0]->add('&', nodes[15]);
    nodes[15]->add('&', nodes[53]);
    nodes[15]->addDefault(nodes[16]);
    nodes[16]->acc("&");
    nodes[53]->addDefault(nodes[54]);
    nodes[54]->acc("&&");

    //%
    nodes[0]->add('%', nodes[17]);
    nodes[17]->addDefault(nodes[18]);
    nodes[18]->acc("%");

    //*
    nodes[0]->add('*', nodes[19]);
    nodes[19]->addDefault(nodes[20]);
    nodes[20]->acc("*");

    // /
    nodes[0]->add('/', nodes[21]);
    nodes[21]->addDefault(nodes[22]);
    nodes[22]->acc("/");

    // +
    nodes[0]->add('+', nodes[23]);
    nodes[23]->addDefault(nodes[24]);
    nodes[24]->acc("+");

    //=、==
    nodes[0]->add('=', nodes[25]);
    nodes[25]->add('=', nodes[26]);
    nodes[25]->addDefault(nodes[27]);
    nodes[26]->addDefault(nodes[28]);
    nodes[27]->acc("=");
    nodes[28]->acc("==");

    //>,>=
    nodes[0]->add('>', nodes[29]);
    nodes[29]->add('=', nodes[30]);
    nodes[29]->addDefault(nodes[31]);
    nodes[30]->addDefault(nodes[32]);
    nodes[31]->acc("more");
    nodes[32]->acc("meq");

    //<,<=
    nodes[0]->add('<', nodes[33]);
    nodes[33]->add('=', nodes[34]);
    nodes[33]->addDefault(nodes[35]);
    nodes[34]->addDefault(nodes[36]);
    nodes[35]->acc("<");
    nodes[36]->acc("<=");

    //!=、!
    nodes[0]->add('!', nodes[45]);
    nodes[45]->add('=', nodes[46]);
    nodes[45]->addDefault(nodes[47]);
    nodes[46]->addDefault(nodes[48]);
    nodes[47]->acc("!");
    nodes[48]->acc("!=");


    //-
    nodes[0]->add('-', nodes[37]);
    nodes[37]->addDefault(nodes[39]);
    nodes[39]->acc("-");

    //int
    nodes[0]->add('0', '9', nodes[38]);
    nodes[38]->add('0', '9', nodes[38]);
    nodes[38]->addDefault(nodes[40]);
    nodes[40]->acc("const int");

    //id or key
    nodes[0]->add('_', nodes[41]);
    nodes[0]->add('a', 'z', nodes[41]);
    nodes[0]->add('A', 'Z', nodes[41]);
    nodes[41]->add('_', nodes[41]);
    nodes[41]->add('a', 'z', nodes[41]);
    nodes[41]->add('A', 'Z', nodes[41]);
    nodes[41]->add('0', '9', nodes[41]);
    nodes[41]->addDefault(nodes[42]);
    nodes[42]->acc("id");

    //,
    nodes[0]->add(',', nodes[43]);
    nodes[43]->addDefault(nodes[44]);
    nodes[44]->acc(",");

    //~
    nodes[0]->add('~', nodes[49]);
    nodes[49]->addDefault(nodes[50]);
    nodes[50]->acc("~");
}


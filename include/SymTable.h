#ifndef SYMTABLE_H
#define SYMTABLE_H

#ifndef INCLUDES_H
#include "Includes.h"
#endif // INCLUDES_H

class Sympol {

public:
    Sympol() {};
    Sympol(string val, bool isAbsl) : value{val}, isAbs{isAbsl} {}
    string value = "";
    bool isAbs = false;
};

class SymTable {
public:
    SymTable();

    void insert(string label, string locator, bool isAbs = false);

    void insert(string label, Sympol symp);

    // return -1 if not found
    string getLocator(string label);

    bool isAbsolute(string label);

    bool hasLabel(string label);

    unordered_map<string, Sympol> getSymtab() {
        return symTab;
    }

    string getRegister(string r);

private:
    unordered_map<string, Sympol> symTab;
    unordered_map<string, string> registers;
};

#endif // SYMTABLE_H

#ifndef SYMTABLE_H
#define SYMTABLE_H

#ifndef INCLUDES_H

#include "Includes.h"

#endif // INCLUDES_H

class SymTable {
public:
    SymTable();

    void insert(string label, string locator);

    // return -1 if not found
    string getLocator(string label);

    bool hasLabel(string label);

    map<string, string> getSymtab() {
        return symTab;
    }

private:
    map<string, string> symTab;
};

#endif // SYMTABLE_H
